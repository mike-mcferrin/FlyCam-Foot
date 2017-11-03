
void MotorControlInit()
{
  motorControl.Init();
}
void EncoderInit()
{
      Direction = true;//default -> Forward  
      pinMode(encoder0pinB,INPUT);  
      attachInterrupt(0, wheelSpeed, CHANGE);
}



void wheelSpeed()
{
  int Lstate = digitalRead(encoder0pinA);
  if((encoder0PinALast == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(encoder0pinB);
    if(val == LOW && Direction)
    {
       Direction = false; //Reverse
    }
    else if(val == HIGH && !Direction)
    {
      Direction = true;  //Forward
    }
  }
  encoder0PinALast = Lstate;
  if(!Direction)
    PositionChanged(++myPosition);
  else
    PositionChanged(--myPosition);

}

void PositionChanged( int newPosition )
{
 //Serial.print("position: ");
  // Serial.println(newPosition);
  
}

