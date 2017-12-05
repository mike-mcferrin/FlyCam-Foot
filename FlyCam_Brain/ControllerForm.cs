using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.Integration;
using _6_ArduinoController;

namespace ArduinoController
{
    public partial class ControllerForm : Form
    {
        private ArduinoController _arduinoController;
        private double _ledFrequency;

        public ControllerForm()
        {
            InitializeComponent();
            SetupArduino();
            WPFControl1.Child = wpfControl;

            FootControls.Add(new FootControl() { ID = 4, Text = "Foot 4", Status = "Offline" });
            FootControls.Add(new FootControl() { ID = 3, Text = "Foot 3", Status = "Offline" });
            FootControls.Add(new FootControl() { ID = 2, Text = "Foot 2", Status = "Offline" });
            FootControls.Add(new FootControl() { ID = 1, Text = "Foot 1", Status = "Offline" });

            foreach (var foot in FootControls)
            {
                foot.Width = 60;
                foot.CallOut += (control, command, sub, value, value2, args) =>
                {
                    var controlName = control.Text;
                    _arduinoController.SendDirectMessage(command, sub, value, value2);
                    listView2.Items.Insert(0,string.Format("FOOT control:{0} command:{2} value:{1}", control.Text, command, value));
                };
                
                ElementHost H1 = new ElementHost();
                H1.Width = 320;
                H1.Height = 300;
                H1.Child = foot;
                H1.Dock = foot.ID <= 10 ? DockStyle.Top : DockStyle.Bottom;
//                PanelFootList.AutoSize = true;
  //              PanelFootList.AutoSizeMode = AutoSizeMode.GrowAndShrink;
                PanelFootList.Controls.Add(H1);
            }

        }

        private FootControl GetFootControl(int id)
        {
            return FootControls.Where(x => x.ID == id).FirstOrDefault();
        }

        private void SetupArduino()
        {
            _arduinoController = new ArduinoController();
            _arduinoController.Setup(this);
            _arduinoController.CallOut += _arduinoController_CallOut;
            _arduinoController.Log += (controller, text) =>
            {
                listView2.Items.Insert(0, string.Format("LOG: {0}", text));

                var id = int.Parse(text.Substring(text.IndexOf("a)") + 3, 3));
                var channel = int.Parse(text.Substring(text.IndexOf("b)") + 3, text.IndexOf("c)") - text.IndexOf("b)") - 3));
                var value = int.Parse(text.Substring(text.IndexOf("c)") + 3, text.IndexOf("d)") - text.IndexOf("c)") - 3));
                var value2 = int.Parse(text.Substring(text.IndexOf("d)") + 3, 3));
                GetFootControl(id)?.SetSliderValue((double)value,false);
            };
        }
        FootSelectionList wpfControl = new FootSelectionList();
        List<FootControl> FootControls = new  List<FootControl>();
      
        private void _arduinoController_CallOut(ArduinoController arduino, int a, int b, int c , double d, EventArgs e)
        {
            listView2.Items.Insert(0, string.Format("AC control:{0} \n value:{1}", b, c));
            wpfControl.SetXY(b,c);
        }

        // Update arduinoController on value checkbox checked/unchecked
        private void EnableLedCheckBoxCheckedChanged(object sender, EventArgs e)
        {
          //  _arduinoController.SetLedState(true);
        }

        // Update value label and arduinoController on value changed using slider
        private void LedFrequencyTrackBarScroll(object sender, EventArgs e)
        {
            //LedFrequencyValue.Text = _ledFrequency.ToString(CultureInfo.InvariantCulture);
            _arduinoController.SetLedFrequency(10, (float)2, (float) 1);
        }

//        // Set ledState checkbox
//        public void SetFoot(int foot)
//        {
//          //  EnableLedCheckBox.Checked = ledState;
//        }

//        // Set frequency slider
//        public void SetMode(double ledFrequency)
//        {
////            LedFrequencyLabelTrackBar.Value = (int) ((ledFrequency - 0.4)*2.5);
//        }

        // Update value label and arduinoController on value changed
        private void LedFrequencyLabelTrackBarValueChanged(object sender, EventArgs e)
        {
            LedFrequencyTrackBarScroll(sender,e);
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing )
            {
                _arduinoController.Exit();
                if (components!=null)
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void elementHost1_ChildChanged(object sender, System.Windows.Forms.Integration.ChildChangedEventArgs e)
        {
           
        }

        private void btn_ReConnect_Serial_Click(object sender, EventArgs e)
        {
            _arduinoController.Exit();
            SetupArduino();
        }

        private void PanelFootList_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
