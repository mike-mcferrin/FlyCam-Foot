
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
unsigned long prevMillis;
unsigned long txIntervalMillis = 500; // send once per second


void PositionChanged( int newPosition )
{

    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) 
    {
      
    
        
          dataToSend[0] =  settings.id;
          dataToSend[1] = 9;
          dataToSend[2] = newPosition ;
          
          //SetData(0, 2);
          //SetData(1, 1);
          //SetData(2, speed);
         
       radio.stopListening();                                  // First, stop listening so we can talk.
       delay(50);
        if ( radio.write(&dataToSend,sizeof(dataToSend) ) )
        {                         // Send the counter variable to the other radio
          /*
           * 
           available()){                             // If nothing in the buffer, we got an ack but it is blank
                //printf("Got blank response. round-trip delay: %lu ms\n\r",millis()-time);
            }else{
                while(radio.available() ){                      // If an ack with payload was received
                    radio.read( &gotByte, 1 );                  // Read it, and display the response time
                    printf("Got response %d, round-trip delay: %lu ms\n\r",gotByte,millis()-time);
                    counter++;                                  // Increment the counter variable
                }
            }
                */
     Serial.print("position: ");
       Serial.println(newPosition);
           
         
        }
       delay(50);
       prevMillis = millis();
       radio.startListening();
    }

}
