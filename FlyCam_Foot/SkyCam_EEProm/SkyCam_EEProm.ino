//EEPROMAnything.h

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



struct config_t {
  double Setpoint;
  double consKp;
  double consKi;
  double consKd;
  int MinPower;
  byte Saved;
} configuration;

 double SPZero ;
 double  consKp ;
 double  consKi ;
 double   consKd ;
 int  MinPower;

config_t currentConfig;

void EEPROMLoad() {
  EEPROM_readAnything(0, configuration);
  if (configuration.Saved != 111)
    return;
  currentConfig.Setpoint = configuration.Setpoint;
  currentConfig.consKp = configuration.consKp;
  currentConfig.consKi = configuration.consKi;
  currentConfig.consKd = configuration.consKd;
  currentConfig.MinPower = configuration.MinPower;
}

void EEPROMSave() {
  configuration.Setpoint = currentConfig.Setpoint;
  configuration.consKp = currentConfig.consKp;
  configuration.consKi = currentConfig.consKi;
  configuration.consKd = currentConfig.consKd;
  configuration.MinPower = currentConfig.MinPower;
  configuration.Saved = 111;
  EEPROM_writeAnything(0, configuration);

}



double counter = 0;


void setup()
{
  Serial.begin(57600);
  Serial.println( "START");
  EEPROMLoad();
  Serial.print( "LOADED pt: ");
  Serial.print( currentConfig.Setpoint);
  Serial.print( "  Kp: ");
  Serial.println( currentConfig.consKp);
  counter = currentConfig.Setpoint;
}

void loop()
{  counter ++;
  if ( counter > 10000 && ( (int)counter % 9387 == 0 ) )
  {Serial.print("new ");
    currentConfig.Setpoint = counter;
    currentConfig.consKp = millis();
    EEPROMSave();
      Serial.print( "SAVE pt: ");
    Serial.print( currentConfig.Setpoint);
    Serial.print( "  Kp: ");
    Serial.println( currentConfig.consKp);
  }
}

