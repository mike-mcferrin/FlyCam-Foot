#include "EEPromManager.h"


int textHeight = 8;
int textWidth = 5;
const int yOffset = 0;
const int xOffset = 2;
void LOG(int line, char* text)
{
  LOG(line,1,1,false,text);
}
void LOG(int line, int pos, int fontsize, bool invert, char* text)
{ 
  if ( SETTING_LOG_LEVEL <= LOG_LEVEL_OFF )
    return;
  LOG_setup(line,pos,fontsize,invert);
  display.println(text);
  display.display();
    delay(20);
}
void LOG(int line, int pos, int fontsize, bool invert, char text , bool IsCharArray)
{
  if ( SETTING_LOG_LEVEL <= LOG_LEVEL_OFF )
    return;
  LOG_setup(line,pos,fontsize,invert);
  display.println(text);
  display.display();
    delay(20);
}
void LOG(int line, int pos, int fontsize, bool invert, String text)
{
  if ( SETTING_LOG_LEVEL <= LOG_LEVEL_OFF )
    return;
  LOG_setup(line,pos,fontsize,invert);
  if ( text != "" )
  {
    display.println(text);
    display.display();
    delay(20);
  }
}

void LOG(int line, int pos,  int fontsize, bool invert, unsigned long number)
{
  if ( SETTING_LOG_LEVEL <= LOG_LEVEL_OFF )
    return;
  LOG_setup(line,pos,fontsize,invert);
    display.println(number);
    display.display();
    delay(20);
}
void LOG(int line, int pos,  int fontsize, bool invert, int number)
{
  if ( SETTING_LOG_LEVEL <= LOG_LEVEL_OFF )
    return;
  LOG_setup(line,pos,fontsize,invert);
    display.println(number);
    display.display();
    delay(20);
}
void LOG(byte text)
{
  if ( SETTING_LOG_LEVEL <= LOG_LEVEL_OFF )
    return;
    display.print(text);
    delay(20);
}
void LOG()
{
  if ( SETTING_LOG_LEVEL <= LOG_LEVEL_OFF )
    return;
    display.display();
    delay(20);
}
void LOG_setup(int line, int pos, int fontsize, bool invert)
{
  if ( SETTING_LOG_LEVEL <= LOG_LEVEL_OFF )
    return;
 display.setTextSize(fontsize);
 delay(20);
 display.setCursor(xOffset  + (pos * (textWidth * fontsize)), yOffset + ( line - 1 ) *  ( textHeight  ));
  if (invert)
  {   display.fillRect(xOffset +  (pos * (textWidth * fontsize)), yOffset + ( line - 1 )* ( textHeight ), display.width(), ( textHeight * fontsize ), WHITE);
      display.setTextColor(BLACK);
  } else
  {
      display.fillRect(xOffset +  (pos * (textWidth * fontsize)), yOffset + ( line - 1 )* ( textHeight  ), display.width(), ( textHeight * fontsize ), BLACK);
      display.setTextColor(WHITE);
  }
    delay(20);
}




