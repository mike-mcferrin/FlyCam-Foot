

int textHeight = 8;
const int yOffset = 0;
const int xOffset = 2;
void LOG(int line, char* text)
{
  LOG(line,1,false,text);
}
void LOG(int line, int fontsize, bool invert, char* text)
{
  display.setTextSize(fontsize);
  display.setCursor(xOffset, yOffset + ( line - 1 ) *  ( textHeight * fontsize ));
  if (invert)
  {   display.fillRect(0, yOffset + ( line - 1 )* ( textHeight * fontsize ), display.width(), ( textHeight * fontsize ), WHITE);
      display.setTextColor(BLACK);
  } else
  {
      display.fillRect(0, yOffset + ( line - 1 )* ( textHeight * fontsize ), display.width(), ( textHeight * fontsize ), BLACK);
      display.setTextColor(WHITE);
  }
  display.println(text);
  display.display();
}


long LoadSetting(int setting)
{
   return EEPROM.read(setting);
}
void SaveSetting(int setting, long value)
{
   EEPROM.put(setting, value);
}
