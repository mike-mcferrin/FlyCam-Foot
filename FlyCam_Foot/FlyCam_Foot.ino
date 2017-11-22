/*
 * 
 * This recieves radio signal and displays the text on the oled screen
 * 
 * 
 */



// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SkyKamExtras.h"



#define CE_PIN   9
#define CSN_PIN 10


const byte thisSlaveAddress[5] = {'R','x','A','A','A'};
const byte thisSlaveAddress2[5] = {'R','x','A','A','B'};

RF24 radio(CE_PIN, CSN_PIN);


struct MyData {
  int channel;
  int command;
  String status;
  int intArray[2];
  float floatArray[2];
  byte dataReceived[20];
};

MyData lastReceived;
byte dataReceived[20]; // this must match dataToSend in the TX
bool newData = false;

//===========
const byte encoder0pinA = 2;  //A pin -> the interrupt pin 0
const byte encoder0pinB = 4;  //B pin -> the digital pin 4    
byte encoder0PinALast;
long myPosition = 0;
boolean Direction; //the rotation direction 
long settingTotalRuns = 0;
MotorControl motorControl;
Movement movement;

/*******/

char dataToSend[20] = "Message 0";

/**** EEPROM*****/
struct config_t
{
    int id;
    long positionCurrent;
    long positionMinimum;
    long positionMaximum;
} settings;


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {

      SettingsInit();
 
    Serial.begin(9600);

     Serial.println( settings.id );
     Serial.println( settings.positionCurrent );
     Serial.println( settings.positionMinimum );
     Serial.println( settings.positionMaximum );
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
    display.clearDisplay();
    display.display();
    if ( settings.id <= 0 )
    {
      settings.id = 32;
    }
    LOG(1,2,false, String("ID: "), true );
    display.println( settings.id );
    display.display();
//    LOG(8,1,false,"    SkyKam RX v1.5");
    Serial.println("SimpleRx Starting");
    //delay(1000);
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.openWritingPipe(thisSlaveAddress2);
    radio.startListening();

  EncoderInit();
  motorControl = MotorControl();
  MotorControlInit();
  movement =  Movement(230,100,false);
  
  //delay(1000);
}

void SettingsInit()
{
  
  // WriteSettings(17,1200,100,9999999);
      settings.id = 2;
      settings.positionCurrent = 0;
      settings.positionMinimum = 0;
      settings.positionMaximum = 0;
  
   // ReadSettings();
    

}




//=============

void loop() {
    getData();
    pingHead();
    showData();
}

//==============

unsigned long counter = 0;

void pingHead()
{
  
  if ( PositionChanged( counter ) )
  {
    LOG(3,2,false, "Count:",true);
    display.println(counter);
    display.display();

    
    if ( ++counter == 128 )
      counter = 0;
  }
}
void getData() {
    if ( radio.available() ) 
    {
     //  Serial.println("Data received 1");
       // MyData data;
        radio.read( &dataReceived, sizeof(dataReceived) );
//        delay(10);
       // lastReceived = data;
        newData = true;
    }
}

long GetData(int address)
{  int addressOffset = 4 * address; 
  long anotherLongInt;
  anotherLongInt = ( ( dataReceived[addressOffset+0] << 24) 
                   + ( dataReceived[addressOffset+1] << 16) 
                   + ( dataReceived[addressOffset+2] << 8) 
                   + ( dataReceived[addressOffset+3] ) ) ;
  return anotherLongInt;
}

void showData() {
    if (newData == true) {
        Serial.print("Received: ");
      //  Serial.println(dataReceived);
       Serial.print("Command: ");
    
       byte id = dataReceived[0] ;
       byte command = dataReceived[1] ;
       byte parameter1 = dataReceived[2] ;


       LOG(6,1,false, id );
       LOG(7,1,false, command );
       LOG(8,1,false, parameter1 );

    
       //long command =  GetData(0) ;
       //long action = GetData(1) ;
       //long parameter1 = GetData(2)  ;
    
        Serial.print("Command: ");
        Serial.print( id );
        Serial.print(" Action: ");
        Serial.print( command );
        Serial.print(" Parameter: ");
        Serial.print( parameter1 );
        Serial.println();
    
      if ( String( id ) == String( settings.id ) )
      {
        
          
          switch( command )
          {
            case 1:
    //              LOG(3,1,false,"STEP MOTOR"  );
            
              if ( parameter1 == 1 )
              {
                  movement =  Movement(230,35,true); // 0-255 ,30 min
                  movement.Start();
    //              LOG(4,1,false,"FORWARD"  );
              }
              if ( parameter1 == 2 )
              {
                  movement =  Movement(230,35,false);
                  movement.Start();
    //              LOG(4,1,false,"REVERSE"  );
              }
              break;
            case 2:
              int speed;
              speed = parameter1;
   //               LOG(3,1,false, "DRIVE MOTOR" );
    
              if ( speed == 128 )
              {
      //          LOG(4,1,false,"STOP"  );
                motorControl.Stop();
              }
              else if ( speed > 127 ) 
              {
                int x = map( speed-127  , 0 , 128 , 00, 210 );
         //       LOG(4,1,false, String("FORWARD")  );
                movement =  Movement( x , 30 , true);
                motorControl.DirectionForward(); 
                motorControl.SetSpeed( x );
              } 
              else
              {
                int x = map( 127-speed , 0 , 128 ,00 , 210 );
     //           LOG(4,1,false, String("REVERSE" )  );
              // movement =  Movement( x , 30 , false);
               motorControl.DirectionReverse();
               motorControl.SetSpeed( x );
              }
             // movement.Start();
              break;
            case 5:
              movement =  Movement(220,80,false);
              movement.Start();
              break;
            
          }
         
     //      LOG(5, 1, false ,  String(id));
    //       LOG(6, 1, false,   String(command)); 
   //       LOG(7, 1, false,   String(parameter1));
      }
        newData = false;
    }
}




