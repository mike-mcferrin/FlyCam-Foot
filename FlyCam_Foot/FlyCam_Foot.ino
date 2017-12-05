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
#include <Servo.h>


#define CE_PIN   9
#define CSN_PIN 10

#define MY_ID 1

enum LOG_LEVELS
{
  LOG_LEVEL_OFF = 1,
  LOG_LEVEL_COMM_IN = 2,
  LOG_LEVEL_COMM_ALL = 3,
  LOG_LEVEL_DEBUG = 4,
  LOG_LEVEL_ALL = 5
} ;

enum MODES
{
  MODE_PING = 1,
  MODE_SETUP = 2,
  MODE_RUN = 3,
  MODE_MANUAL = 4
} ;

int SETTING_LOG_LEVEL = LOG_LEVEL_DEBUG;
int SETTING_MODE = MODE_PING;

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};
const byte thisSlaveAddress2[5] = {'R','x','A','A','B'};

RF24 radio(CE_PIN, CSN_PIN);


struct MyData {
  int channel;
  int command;
  String status;
  int intArray[2];
  float floatArray[2];
  byte dataReceived[7];
};

MyData lastReceived;
byte dataReceived[7]; // this must match dataToSend in the TX
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

char dataToSend[7] = "       ";

/**** EEPROM*****/
struct config_t
{
    byte id;
    long positionCurrent;
    long positionMinimum;
    long positionMaximum;
} settings;


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Servo SERVO_1;

void setup() {

      SettingsInit();

    Serial.begin(9600);

     Serial.println( settings.id );
     Serial.println( settings.positionCurrent );
     Serial.println( settings.positionMinimum );
     Serial.println( settings.positionMaximum );

    SETTING_LOG_LEVEL = LOG_LEVEL_ALL;
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
    display.clearDisplay();
   
    SetID( MY_ID );
    SetMODE( SETTING_MODE );    
    
   

 //   LOG(8,1,false,"    SkyKam RX v1.5");
    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.openWritingPipe(thisSlaveAddress2);
    radio.startListening();

    SERVO_1.attach(5);

  EncoderInit();
  motorControl = MotorControl();
  MotorControlInit();
  movement =  Movement(230,100,false);
  
  //delay(1000);
}

void SettingsInit()
{    
      SETTING_MODE = MODE_PING;
      settings.id = MY_ID;
      settings.positionCurrent = 0;
      settings.positionMinimum = 0;
      settings.positionMaximum = 0; 
}

void SetID( int id )
{
    settings.id = id;
    LOG(1,1,2,false, "ID:" );
    LOG(1,5,2,false, id);
}

void SetMODE( int mode )
{
    bool highlightMode = false;
      SETTING_MODE  = mode ;
      LOG(1,18,1,false, "M:");   
      LOG(1,21,1,highlightMode , mode);   
}


//=============


void loop() {
    getData();
    if ( SETTING_MODE == MODE_PING )
    {
      pingHead();
    }
    showData();
}

//==============

unsigned long counter = 0;

void pingHead()
{
  
  if ( PositionChanged( counter ) )
  {
    LOG(2,18,1,false, "C:");
    LOG(2,21,1,counter %2 == 0, counter);
    if ( ++counter >= 255 )
      counter = 0;
  }
}
void getData() {
    if ( radio.available() ) 
    {
     //  Serial.println("Data received 1");
       // MyData data;
        radio.read( &dataReceived, sizeof(dataReceived) );
        delay(20);
       // lastReceived = data;
        newData = true;
    }
}

unsigned long GetData(int address)
{  int addressOffset = 4 * address; 
  unsigned long anotherLongInt;
  anotherLongInt = ( ( dataReceived[addressOffset+0] << 24) 
                   + ( dataReceived[addressOffset+1] << 16) 
                   + ( dataReceived[addressOffset+2] << 8) 
                   + ( dataReceived[addressOffset+3] ) ) ;
  return anotherLongInt;
}
         int speed;
void showData() {
    if (newData == true) {
      //  Serial.print("Received: ");
      //  Serial.println(dataReceived);
      // Serial.print("Command: ");
    
       byte id = dataReceived[0] ;
       byte command = dataReceived[1] ;
       byte parameter1 = dataReceived[2] ;
       unsigned long parameter2 = GetData(3);
/* 

      LOG(6,1,false, id );
       LOG(7,1,false, command );
       LOG(8,1,false, parameter1 );
     */
    
       //long command =  GetData(0) ;
       //long action = GetData(1) ;
       //long parameter1 = GetData(2)  ;
    
        Serial.print("Command: ");
        Serial.print( id );
        Serial.print(" Action: ");
        Serial.print( command );
        Serial.print(" Parameter: ");
        Serial.print( parameter1 );
        Serial.print(" Parameter2: ");
        Serial.print( parameter2 );
        Serial.println();

     
      if ( id == settings.id || id == 0 )
      {

         if ( SETTING_LOG_LEVEL >= LOG_LEVEL_ALL )
          {
                LOG(5,1,2,false, command);        
                LOG(5,6,2,false, parameter1);        
            //    LOG(8,1,false, parameter2);        
          }
              
          switch( command )
          {
            case 101:
                  Serial.print("Set Mode: ");
                  Serial.println( parameter1 );
                  SetMODE( parameter1 );
                  break;
        
            case 102:
                  Serial.print("Set Debug Level: ");
                  Serial.println( parameter1 );
                  SETTING_LOG_LEVEL = parameter1;
                  break;

             case 103:
                  Serial.print("Set ID: ");
                  Serial.println( parameter1 );
                   SetID( dataReceived[2] );
                  break;

             case 104:
                  counter = parameter1;
                  ResetCurrentMillis();
                  break;
                  
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
     
              if ( speed != parameter1 )
              {
                  speed = parameter1;
                  
                /* IF (FOOT_TYPE == SERVO) { */
        Serial.println("SERVO WRITE");
                  SERVO_1.write(speed);
              }

            /* FOOT TYPE SERVO */
   /*
   if ( FOOT_TYPE == MOTOR_CONTROLLER )
   {
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
             
   }
    break;
   */

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




