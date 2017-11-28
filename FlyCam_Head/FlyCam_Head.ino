
/*
 *  This sends a string and an incrementing number out on radio
 * 
 * 
 */

// SimpleTx - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <PS2X_lib.h> 
#include <CmdMessenger.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

    

#define ANALOG_MOVEMENT_TOLERANCE 4

#define CE_PIN   9
#define CSN_PIN 10

#define PS2_SEL        2  //16
#define PS2_CMD        3  //15
#define PS2_CLK        4  //17
#define PS2_DAT        5  //14    
#define pressures   true
#define rumble      false


PS2X ps2x; 
byte vibrate = 0;


const byte slaveAddress[5] = {'R','x','A','A','A'};
const byte slaveAddress2[5] = {'R','x','A','A','B'};

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio


struct MyData {
  int channel;
  int command;
  String status;
  int intArray[2];
  float floatArray[2];
  char dataReceived[10];
};


MyData data;
String stringToSend = "";
char dataToSend[20] = "Message 0";
char dataReceived[20] = "dsfsdf  ";
int txNum = 0;


unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 50; // send once per second

CmdMessenger cmdMessenger = CmdMessenger(Serial);
enum
{
  kAcknowledge,
  kError,
  kSetLed, 
  ControllerLeftAnalog,
  ControllerRightAnalog,
  Log
};

//#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);

void setup() {

  //  Serial.begin(9600);

  // Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
    radio.openReadingPipe(1,slaveAddress2);
    radio.openWritingPipe(slaveAddress);
    radio.startListening();
    
     DisplayInit();
     PlaystationControllerInit();
     BrainInit();
}

//====================
bool newData = false;

void loop() {
  
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) {
      ReadPlaystationController();
      cmdMessenger.feedinSerialData();
      prevMillis = millis();
    }
       getData();
       if ( newData )
       { 

        byte id = dataReceived[0] ;
        byte command = dataReceived[1] ;
        byte parameter1 = dataReceived[2] ;
       
        SendControlCommand(11,command);
    //   cmdMessenger.sendCmd( Log,     "Data->" + dataReceived[2]  );
         newData = false;

        cmdMessenger.sendCmdStart(Log);
        cmdMessenger.sendCmdArg("Data->");
        cmdMessenger.sendCmdArg(dataReceived[0]);
        cmdMessenger.sendCmdArg(dataReceived[1]);
        cmdMessenger.sendCmdArg(dataReceived[2]);
        cmdMessenger.sendCmdEnd(); 
        
       }
}



void getData() {
    if ( radio.available() ) 
    {
       Serial.print("Data received: ");
        radio.read( &dataReceived, sizeof(dataReceived) );
      Serial.print(dataReceived[0]);
      Serial.print(dataReceived[1]);
      Serial.print(dataReceived[2]);
      Serial.println();
        newData = true;
 
      
    }
}


void DisplayInit()
{
   // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
   // display.clearDisplay();
   // display.display();
   // LOG(2,2,true,"SKYCAM");
}

bool stateLX = false;
bool stateLY = false;
bool stateRX = false;
bool stateRY = false;
bool stateDpadU = false;
bool stateDpadD = false;
bool stateButtonL1 = false;
bool stateButtonR1 = false;

void ReadPlaystationController()
{
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

  bool DpadU = ps2x.Button(PSB_PAD_UP);
  bool DpadD = ps2x.Button(PSB_PAD_DOWN);
  bool DpadL = ps2x.Button(PSB_PAD_LEFT);
  bool DpadR = ps2x.Button(PSB_PAD_RIGHT);
  
  bool ButtonX = ps2x.NewButtonState(PSB_CROSS);
  bool ButtonO = ps2x.NewButtonState(PSB_CIRCLE);
  bool ButtonS = ps2x.NewButtonState(PSB_SQUARE);
  bool ButtonT = ps2x.NewButtonState(PSB_TRIANGLE);
  bool ButtonL1 = ps2x.Button(PSB_L1);
  bool ButtonL2 = ps2x.Button(PSB_L2);
  bool ButtonR1 = ps2x.Button(PSB_R1);
  bool ButtonR2 = ps2x.Button(PSB_R2);

 if ( ButtonL1 )
    {   
      if ( !stateButtonL1 )
      {
        stateButtonL1 = true;
      }
    }
    else
    {
      if ( stateButtonL1 )
      {
          stateButtonL1  = false;
          MotorOut(1, 128);
      }
    }
 

 if ( ButtonR1 )
    {   
      if ( !stateButtonR1 )
      {
        stateButtonR1 = true;
      }
    }
    else
    {
      if ( stateButtonR1 )
      {
          MotorOut(2, 128);
          stateButtonR1  = false;
      }
    }
 


 
      int LX = ps2x.Analog(PSS_LX) - 128;
      if ( abs(LX) > ANALOG_MOVEMENT_TOLERANCE && ( stateLX || ( (!stateLX && LX < 127) && (!stateLX && LX > -127) ) ) )
      { 
        stateLX = true;
        SendControlCommand(1,LX);
      }
      else
      {
        if ( stateLX )
        {
          SendControlCommand(1,0);
          stateLX = false;
        }
      }

       
       
     
      int LY = -1 * ( ps2x.Analog(PSS_LY) - 128 );

      if ( abs(LY) > ANALOG_MOVEMENT_TOLERANCE )   // && ( stateLY || ( (!stateLY && LY < 127) && (!stateLY && LY > -127) ) ) )
      {
        stateLY = true;
     /**** IF FOOT_TYPE == MOTOR_CONTROL *****/
     /* 
       // SendControlCommand(2,LY);
        if (stateButtonL1)
        {
          MotorOut(1,   ps2x.Analog(PSS_LY)  );
        }
     */
     /**** IF FOOT_TYPE == SERVO ****/
          SendControlCommand(2,LY);
           MotorOut(1,   ps2x.Analog(PSS_LY)  );
      }
       else
      {
        if ( stateLY )
        {
           /**** IF FOOT_TYPE == MOTOR_CONTROL *****/
          /*MotorOut(1, 128);
        SendControlCommand(2,0);
        */
         SendControlCommand(2,0);
        stateLY = false;
        }
      }

      int RX = ps2x.Analog(PSS_RX) - 128;
      if ( abs(RX) > ANALOG_MOVEMENT_TOLERANCE ) //  && ( stateRX || ( (!stateRX && RX < 127) && (!stateRX && RX > -127) ) ) )
      { 
          stateRX = true;
        SendControlCommand(3,RX);
      }
      else
      {
        if ( stateRX )
        {
          SendControlCommand(3,0);
          stateRX = false;
        }
      }

      
      int RY = -1 * ( ps2x.Analog(PSS_RY) - 128 );
      if ( abs(RY) > ANALOG_MOVEMENT_TOLERANCE ) // && ( stateRY || ( (!stateRY && RY < 127) && (!stateRY && RY > -127) ) ) )
      {
        stateRY = true;
        SendControlCommand(4,RY);
       /**** IF FOOT_TYPE == MOTOR_CONTROL *****/
     /*    if (stateButtonR1)
        {
          MotorOut(2,   ps2x.Analog(PSS_RY)  );
        }
        */
        /**** IF FOOT_TYPE == SERVO ****/
        }
       else
      {
        if ( stateRY )
        {
             /**** IF FOOT_TYPE == MOTOR_CONTROL *****/
             /*
           MotorOut(2, 128);
       SendControlCommand(4,0);
       */
        stateRY = false;
         SendControlCommand(4,0);
        }
      }



  if ( ButtonX )
  {
     MotorStep(1,1);
        cmdMessenger.sendCmd( Log,     "Cross");
  }

  if ( ButtonT )
  {
     MotorStep(1,2);
        cmdMessenger.sendCmd( Log,     "Triangle");
  }

  if ( ButtonS )
  {
     MotorStep(2,1);
        cmdMessenger.sendCmd( Log,     "Square");
  }

  if ( ButtonO )
  {
     MotorStep(2,2);
        cmdMessenger.sendCmd( Log,     "Circle");
  }

  
  if ( DpadU )
    {   
      if ( !stateDpadU )
      {
        SendControlCommand(6,1);
        stateDpadU = true;
      }
    }
    else
    {
      if ( stateDpadU )
      {
          stateDpadU  = false;
      }
    }
  if ( DpadD )
  {   
     if ( !stateDpadD )
      {
        SendControlCommand(6,-1);
        stateDpadD = true;
      }
  //  Serial.println("Out");
   
  } else
    {
      if ( stateDpadD )
      {
          stateDpadD  = false;
      }
    }

  
 
 

}

void MotorOut(long motor, int speed)
{
      dataToSend[0] = motor;
      dataToSend[1] = 2;
      dataToSend[2] = speed ;
      
      //SetData(0, 2);
      //SetData(1, 1);
      //SetData(2, speed);
      send(); 
                delay(30);

}


void MotorStep(long motor, int direction)
{
      dataToSend[0] = motor;
      dataToSend[1] = 1;
      dataToSend[2] = direction ;
      send(); 
}
void SetData(int address, long longInt )
{   int addressOffset = 4 * address;          
    dataToSend[addressOffset+0] = (int)((longInt >> 24) & 0xFF) ;
    dataToSend[addressOffset+1] = (int)((longInt >> 16) & 0xFF) ;
    dataToSend[addressOffset+2] = (int)((longInt >> 8) & 0XFF);
    dataToSend[addressOffset+3] = (int)((longInt & 0XFF));
}   

void SendControlCommand(float bank, float value)
{
        cmdMessenger.sendCmdStart(ControllerLeftAnalog);
        cmdMessenger.sendCmdArg(bank);
        cmdMessenger.sendCmdArg(float( value ));
        cmdMessenger.sendCmdEnd(); 
}

void SendLogCommand(float bank, String value)
{
        cmdMessenger.sendCmdStart(ControllerLeftAnalog);
        cmdMessenger.sendCmdArg(bank);
        cmdMessenger.sendCmdArg(value );
        cmdMessenger.sendCmdEnd(); 
}

void BrainInit()
{
   Serial.begin(115200); 
 
  //cmdMessenger.printLfCr();               // Adds newline to every command
    cmdMessenger.attach(  kSetLed,          OnRecievedSerial_Led);
    cmdMessenger.attach(  ControllerLeftAnalog, OnRecievedSerial_Frequency);
//    cmdMessenger.attach(  Log, OnRecievedSerial_Log);
    cmdMessenger.sendCmd( kAcknowledge,     "Started");
    cmdMessenger.sendCmd( Log,     "Started");
}
  
  float ledFrequency   = 1.0; 
  bool messageReceived = false;
  
  void OnRecievedSerial_Frequency()
  {
    // Read led state argument, interpret string as boolean
    ledFrequency = cmdMessenger.readFloatArg();
    messageReceived = true;
    cmdMessenger.sendCmd(kAcknowledge,ledFrequency);
  }

  
  void OnRecievedSerial_Led()
  {
    // Read led state argument, interpret string as boolean
    bool ledState = cmdMessenger.readBoolArg();
    cmdMessenger.sendCmd(kAcknowledge,ledState);
  }



void PlaystationControllerInit()
{
    //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if ( error > 0 )
  {
  //  Serial.print("Error setting up controller: ");
 //   Serial.println( error );
  }
}
//====================

void send() {
     radio.stopListening();
  //  stringToSend.toCharArray(dataToSend, 20 );
    bool rslt = radio.write( &dataToSend, sizeof(dataToSend) );
      
    if (rslt) 
    {
       // Serial.println("Acknowledge received");
    }
    else 
    {
    //  Serial.println("Acknowledge Failed");
     //  LOG(1,2,true,"Tx failed");
    }
    radio.startListening();
}




