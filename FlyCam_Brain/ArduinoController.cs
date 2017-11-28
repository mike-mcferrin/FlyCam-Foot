// *** ArduinoController ***

// This example expands the SendandReceiveArguments example. The PC will now sends commands to the Arduino when the trackbar 
// is pulled. Every TrackBarChanged events will queue a message to the Arduino to set the blink speed of the 
// internal / pin 13 LED
// 
// This example shows how to :
// - use in combination with WinForms
// - use in combination with ZedGraph
// - send queued commands
// - Use the CollapseCommandStrategy

using System;
using CommandMessenger;
using CommandMessenger.TransportLayer;

namespace ArduinoController
{
    enum Command
    {
        kAcknowledge,
        kError,
        kSetLed, // Command to request led to be set in specific state
        ControllerLeftAnalogX,
        ControllerLeftAnalogY,
        Log
    };

    public class ArduinoController
    {
   
        private SerialTransport   _serialTransport;
        private CmdMessenger      _cmdMessenger;
        private ControllerForm    _controllerForm;

        public delegate void CallOutHandler(ArduinoController a, float b, float c, EventArgs e);
        public event CallOutHandler CallOut;
        public delegate void LogHandler(ArduinoController a, String text);
        public event LogHandler Log;

        public void Setup(ControllerForm controllerForm)
        {
            _controllerForm = controllerForm;

            _serialTransport = new SerialTransport
            {
                CurrentSerialSettings = { PortName = "COM17", BaudRate = 115200, DtrEnable = false } 
            };

            // Initialize the command messenger with the Serial Port transport layer
            _cmdMessenger = new CmdMessenger(_serialTransport)
            {
                BoardType = BoardType.Bit16 // Set if it is communicating with a 16- or 32-bit Arduino board
            };

            // Tell CmdMessenger to "Invoke" commands on the thread running the WinForms UI
            _cmdMessenger.SetControlToInvokeOn(_controllerForm);

            // Attach the callbacks to the Command Messenger
            AttachCommandCallBacks();

            // Attach to NewLinesReceived for logging purposes
            _cmdMessenger.NewLineReceived += NewLineReceived;

            // Attach to NewLineSent for logging purposes
            _cmdMessenger.NewLineSent += NewLineSent;                       

            // Start listening
            _cmdMessenger.StartListening();

            StartupCommands();
        }

        private void StartupCommands()
        {
            //_controllerForm.SetFoot(1);
            //_controllerForm.SetMode(1);
        }
        private void AttachCommandCallBacks()
        {
            _cmdMessenger.Attach((int)Command.ControllerLeftAnalogX, OnSerialReceivedFrequency);
            _cmdMessenger.Attach((int)Command.ControllerLeftAnalogY, OnSerialReceived_ControllerLeftAnalogY);
            _cmdMessenger.Attach((int)Command.Log, OnSerialReceived_Log);

        }
        public void Exit()
        {
            // Stop listening
            _cmdMessenger.StopListening();

            // Dispose Command Messenger
            _cmdMessenger.Dispose();

            // Dispose Serial Port object
            _serialTransport.Dispose();
        }


        #region CALLBACKS

        // ------------------  CALLBACKS ---------------------

        // Called when a received command has no attached function.
        // In a WinForm application, console output gets routed to the output panel of your IDE
        void OnSerialReceivedFrequency(ReceivedCommand arguments)
        {
            var arg1 = arguments.ReadFloatArg();
            var arg2 = arguments.ReadFloatArg();
            Console.WriteLine($">> {arg1} {arg2}");

            EventArgs e = null;
            CallOut(this, arg1, arg2, e);

        }



        void OnSerialReceived_ControllerLeftAnalogY(ReceivedCommand arguments)
        {
            var arg1 = arguments.ReadFloatArg();
            var arg2 = arguments.ReadFloatArg();
            //Console.WriteLine($">> {arg1} {arg2}");

        }

        void OnSerialReceived_Log(ReceivedCommand arguments)
        {
            var arg1 = arguments.ReadStringArg();
            //Console.WriteLine($"LOG >> {arg1}");
            var d1 = arguments.ReadStringArg();
            var d2 = arguments.ReadStringArg();
            var d3 = arguments.ReadStringArg();
            Log(this, arg1 + " 1)" + d1+ " 2)" + d2 + " 3)" + d3);
        }


        #endregion

        #region Events 
        // Log received line to console
        private void NewLineReceived(object sender, NewLineEvent.NewLineArgs e)
        {
            //Console.WriteLine(@"Received > " + e.Command.CommandString());
        }

        // Log sent line to console
        private void NewLineSent(object sender, NewLineEvent.NewLineArgs e)
        {
            //Console.WriteLine(@"Sent > " + e.Command.CommandString());
        }

        #endregion

        #region Commands 
        // Sent command to change led blinking frequency
        public void SetLedFrequency(double ledFrequency, float ledOffInterval, float ledOnInterval)
        {
            // Create command to start sending data
            var command = new SendCommand((int)Command.ControllerLeftAnalogX);
            command.AddArgument(ledFrequency);
            command.AddArgument(ledOffInterval);
            command.AddArgument(ledOnInterval);



            // Put the command on the queue and wrap it in a collapse command strategy
            // This strategy will avoid duplicates of this certain command on the queue: if a SetMode command is
            // already on the queue when a new one is added, it will be replaced at its current queue-position. 
            // Otherwise the command will be added to the back of the queue. 
            // 
            // This will make sure that when the slider raises a lot of events that each send a new blink frequency, the 
            // embedded controller will not start lagging.
            _cmdMessenger.QueueCommand(new CollapseCommandStrategy(command));
        }


        // Sent command to change led on/of state
        //public void SetLedState(bool ledState)
        //{
        //    // Create command to start sending data
        //    var command = new SendCommand((int)Command.SetLed, ledState);

        //    // Send command
        //    _cmdMessenger.SendCommand(new SendCommand((int)Command.SetLed, ledState));         
        //}

        #endregion
    }
}
