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

long ID;

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


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {

      SettingsInit();
 
    Serial.begin(9600);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
    display.clearDisplay();
    display.display();
    LOG(2,2,true,"SKYCAM");
    char ids = ID+48;
    LOG(1,2,true,&ids);
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
  SaveSetting(0,2);
  ID = LoadSetting( 0 );
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

void showData() {
    if (newData == true) {
        Serial.print("Received: ");
        Serial.println(dataReceived);
       Serial.print("Command: ");
    
       char command = dataReceived[0] ;
       char action = dataReceived[1] ;
       char parameter1 = dataReceived[2] ;
       int parameter1int = dataReceived[2];
       LOG(3,dataReceived);

        Serial.print("Command: ");
        Serial.print( command );
        Serial.print(" Action: ");
        Serial.print( action );
        Serial.print(" Parameter: ");
        Serial.print( parameter1int );
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
          if ( parameter1 > 0 )
          {
            int x = map( parameter1 , 0 , 128 , 50 , 254 );
            movement =  Movement( x , 30 , true);
          } 
          else
          {
            int x = map( -parameter1 , 0 , 128 , 50 , 254 );
            movement =  Movement( x , 30 , false);
          }
          movement.Start();
          break;
        case 5:
          movement =  Movement(220,80,false);
          movement.Start();
          break;
        
      }
         
        newData = false;
    }
}




