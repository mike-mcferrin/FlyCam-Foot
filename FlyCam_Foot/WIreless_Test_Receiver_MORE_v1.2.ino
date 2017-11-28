#include "EEPromManager.h"


int textHeight = 8;
const int yOffset = 0;
const int xOffset = 2;
void LOG(int line, char* text)
{
  LOG(line,1,false,text);
}
void LOG(int line, int fontsize, bool invert, char* text)
{
  LOG_setup(line,fontsize,invert);
  display.println(text);
  display.display();
    delay(20);
}
void LOG(int line, int fontsize, bool invert, char text , bool IsCharArray)
{
  LOG_setup(line,fontsize,invert);
  display.println(text);
  display.display();
    delay(20);
}
void LOG(int line, int fontsize, bool invert, String text)
{
  LOG_setup(line,fontsize,invert);
  if ( text != "" )
  {
    display.println(text);
    display.display();
    delay(20);
  }
}
void LOG(int line, int fontsize, bool invert, String text, bool stayOnLine)
{
  LOG_setup(line,fontsize,invert);
    display.print(text);
    delay(20);
}
void LOG(int line, int fontsize, bool invert, unsigned long number)
{
  LOG_setup(line,fontsize,invert);
    display.println(number);
    display.display();
    delay(20);
}
void LOG(int line, int fontsize, bool invert, int number)
{
  LOG_setup(line,fontsize,invert);
    display.println(number);
    display.display();
    delay(20);
}
void LOG(byte text)
{
    display.print(text);
    delay(20);
}
void LOG()
{
    display.display();
    delay(20);
}
void LOG_setup(int line, int fontsize, bool invert)
{
 display.setTextSize(fontsize);
 delay(20);
 display.setCursor(xOffset, yOffset + ( line - 1 ) *  ( textHeight  ));
  if (invert)
  {   display.fillRect(0, yOffset + ( line - 1 )* ( textHeight ), display.width(), ( textHeight * fontsize ), WHITE);
      display.setTextColor(BLACK);
  } else
  {
      display.fillRect(0, yOffset + ( line - 1 )* ( textHeight  ), display.width(), ( textHeight * fontsize ), BLACK);
      display.setTextColor(WHITE);
  }
    delay(20);
}


/**** EEPROM*****/

void ReadSettings()
{
  EEPROM_readAnything(0,settings);
}

void WriteSettings(int id, long position, long min, long max)
{
  settings.id = id;
  settings.positionCurrent = position;
  settings.positionMinimum = min;
  settings.positionMaximum = max;
  
  EEPROM_writeAnything(0,settings);
}

/**** EEPROM*****/




long LoadSetting(int setting)
{
   return EEPROM.read(setting);
}
void SaveSetting(int setting, long value)
{
   EEPROM.put(setting, value);
}
