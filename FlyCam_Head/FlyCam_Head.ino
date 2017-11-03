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
const byte slaveAddress2[5] = {'R','x','A','A','A'};

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
int txNum = 0;


unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 50; // send once per second


void setup() {

    Serial.begin(9600);

    Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(slaveAddress);
    radio.openWritingPipe(slaveAddress2);
    
     PlaystationControllerInit();
}

//====================

void loop() {
  
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) {
   
   ReadPlaystationController();
        
        prevMillis = millis();
    }
}

void ReadPlaystationController()
{
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
  bool DpadU = ps2x.Button(PSB_PAD_UP);
  bool DpadD = ps2x.Button(PSB_PAD_DOWN);
  bool DpadL = ps2x.Button(PSB_PAD_LEFT);
  bool DpadR = ps2x.Button(PSB_PAD_RIGHT);
  int LX = ps2x.Analog(PSS_LX) - 128;
  int LY = ps2x.Analog(PSS_LY) - 128;
  int RX = ps2x.Analog(PSS_RX) - 128;
  int RY = ( ps2x.Analog(PSS_RY) - 128 ) * -1;
  bool ButtonX = ps2x.NewButtonState(PSB_CROSS);
  bool ButtonO = ps2x.NewButtonState(PSB_CIRCLE);
  bool ButtonS = ps2x.NewButtonState(PSB_SQUARE);
  bool ButtonT = ps2x.NewButtonState(PSB_TRIANGLE);
  bool ButtonL1 = ps2x.Button(PSB_L1);
  bool ButtonL2 = ps2x.Button(PSB_L2);
  bool ButtonR1 = ps2x.Button(PSB_R1);
  bool ButtonR2 = ps2x.Button(PSB_R2);


  if ( DpadU )
    {   
      Serial.println("In");
      dataToSend[0] = 1;
      dataToSend[1] = 2;
      dataToSend[2] = LX;
       send(); 
    }
  if ( DpadD )
  {   
    Serial.println("Out");
    dataToSend[0] = 1;
    dataToSend[1] = 1;
    dataToSend[2] = LX;
    send();    
  }

  
  if ( ButtonL2 )
  {
      dataToSend[0] = 2;
      dataToSend[1] = 1;
      dataToSend[2] = LY;
      send();    
  }

 

}




void PlaystationControllerInit()
{
    //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if ( error > 0 )
  {
    Serial.print("Error setting up controller: ");
    Serial.println( error );
  }
}
//====================

void send() {

  //  stringToSend.toCharArray(dataToSend, 20 );
    bool rslt = radio.write( &dataToSend, sizeof(dataToSend) );
      
    if (rslt) 
    {
        Serial.println("Acknowledge received");
    }
    else 
    {
      Serial.println("Acknowledge Failed");
     //  LOG(1,2,true,"Tx failed");
    }
}


