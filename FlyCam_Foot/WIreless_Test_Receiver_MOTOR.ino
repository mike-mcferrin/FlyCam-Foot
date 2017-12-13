
int txIntervalMillis = 25000;
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



unsigned long currentMillis;
unsigned long prevMillis = 0;

void ResetCurrentMillis()
{
  currentMillis = 0;
}
bool PositionChanged( long newPosition )
{
  
    if (currentMillis++ >= txIntervalMillis) 
    {
        currentMillis = 0;   
      dataToSend[0] =  settings.id;
      dataToSend[1] = 9;
      dataToSend[2] = newPosition ;
      
      radio.stopListening();                                  // First, stop listening so we can talk.

      //****** THIS WAS 50 AND IT WORKED ******/
      delay(50);
      
      if ( radio.write(&dataToSend,sizeof(dataToSend) ) )
      {                       
              Serial.print("Data Sent: ");
              Serial.print("position: ");
              Serial.println(newPosition);
              
           /*   
          if( radio.available())
          {                             // If nothing in the buffer, we got an ack but it is blank
              //printf("Got blank response. round-trip delay: %lu ms\n\r",millis()-time);
              Serial.println("Got blank response.");
          }
          else
          {
              while(radio.available() )
              {                      // If an ack with payload was received
                  radio.read( &gotByte, 1 );                  // Read it, and display the response time
                  //printf("Got response %d, round-trip delay: %lu ms\n\r",gotByte,millis()-time);
                  Serial.println("Got response");
                  counter++;                                  // Increment the counter variable
              }
              
          }
              
      
         */
       
      }
      else
      {
        Serial.println("DATA NOT SENT!");
      }
       delay(50);
       radio.startListening();


    
       return true;
    }
    return false;

}
