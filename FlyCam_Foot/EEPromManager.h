
#include <EEPROM.h>
#include <Arduino.h>  // for type definitions

template <class T> int EEPROM_writeAnything(int ee, const T& value)
    {
        const byte* p = (const byte*)(const void*)&value;
        unsigned int i;
        for (i = 0; i < sizeof(value); i++)
        EEPROM.write(ee++, *p++);
        return i;
    }

template <class T> int EEPROM_readAnything(int ee, T& value)
    {
        byte* p = (byte*)(void*)&value;
        unsigned int i;
        for (i = 0; i < sizeof(value); i++)
        *p++ = EEPROM.read(ee++);
        return i;
    }
    

struct configuration_ {
      int  MyId;
      long CurrentPosition;
      long MinimumPosition;
      long MaximumPosition;
      float SpeedRatio;
      int PositionX;
      int PositionY;
      int PositionZ;
      long TimeOn;
      byte Saved;
      char Name[12];
      long ArrayOfLongs[10];
    } configuration;


bool EEPROMLoad() {
      EEPROM_readAnything(0, configuration);
      return (configuration.Saved == 111);
    }

void EEPROMSave() {
      configuration.Saved = 111;
      EEPROM_writeAnything(0, configuration);
    }

void EEPROMClear(){
      Serial.println( "CLEARING EEPROM...");
      for (int i = 0 ; i < EEPROM.length() ; i++)
          EEPROM.write(i, 0);
      Serial.println( "EEPROM CLEARED!"); 
    }

