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

RF24 radio(CE_PIN, CSN_PIN);


struct MyData {
  int channel;
  int command;
  String status;
  int intArray[2];
  float floatArray[2];
  char dataReceived[20];
};

MyData lastReceived;
char dataReceived[20]; // this must match dataToSend in the TX
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
    LOG(3,1,true, "" );
    LOG(4,4,true, "ID: " + String(settings.id) );
    LOG(8,1,true,"    SkyKam RX v1.2");
    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();

  EncoderInit();
  motorControl = MotorControl();
  MotorControlInit();
  movement =  Movement(230,100,false);
  delay(2000);
}

void SettingsInit()
{
  /* WriteSettings(2,1200,100,9999999);
      settings.id = 0;
      settings.positionCurrent = 0;
      settings.positionMinimum = 0;
      settings.positionMaximum = 0;
  */
    ReadSettings();
    

}



void demoFive()
{
   myPosition = 0;
   movement =  Movement(120,80,true);
   GetEncoderValue();
   movement.Start();
   GetEncoderValue();
   delay(500);
   GetEncoderValue();

    delay(3000);
}

void GetEncoderValue()
{  //Serial.print("position: ");
   //Serial.println(myPosition);
}



//=============

void loop() {
    getData();
    showData();
   
}

//==============

void getData() {
    if ( radio.available() ) 
    {
       Serial.println("Data received 1");
       // MyData data;
        radio.read( &dataReceived, sizeof(dataReceived) );
        
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
        Serial.println(dataReceived);
       Serial.print("Command: ");
    
       char command =  GetData(0) ;
       long action = GetData(1) ;
       long parameter1 = GetData(2)  ;
       LOG(5, 2, false ,  String( "C" + String(command) + " A" + String(action) + " P" + String(parameter1)));

        Serial.print("Command: ");
        Serial.print( command );
        Serial.print(" Action: ");
        Serial.print( action );
        Serial.print(" Parameter: ");
        Serial.print( parameter1 );
        Serial.println();
    

      switch( command )
      {
        case 1:
        
          if ( action == 1 )
          {
              movement =  Movement(255,30,true);
              movement.Start();
          }
          if ( action == 2 )
          {
              movement =  Movement(255,30,false);
              movement.Start();
          }
          break;
        case 2:
          int speed ;
          speed = parameter1;
              LOG(1,2,false,"SPD:" + String(parameter1) + " " + String(speed)  );
         
          if ( parameter1 > 128 ) 
          {
            int x = map( speed-128 , 0 , 128 , 0 , 128 );
            LOG(3,2,false,"X:" + String(x)  );
            movement =  Movement( x , 30 , true);
            motorControl.DirectionForward(); 
            motorControl.SetSpeed( x );
          } 
          else
          {
            int x = map( (speed) , 0 , 128 , 0 , 128 );
            LOG(3,2,false,"X:" + String(x)  );
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
         
        newData = false;
    }
}




