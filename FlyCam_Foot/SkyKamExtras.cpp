/*******************************************************************
* 
*   Summary: Finally got this shit to compile!
*
*   Features:  
*
*/

#include "SkyKamExtras.h"
#include <Arduino.h>


Movement::Movement()
{
}
Movement::Movement(int currentSpeed, int totalTime , bool direction)
{
  CurrentSpeed = currentSpeed;
  TotalTime = totalTime;
  Direction = direction;
  Motor = MotorControl();
}

int Movement::Start(int currentSpeed, int totalTime)
{   CurrentSpeed = currentSpeed;
    TotalTime = totalTime;
    this->Start();
}
int Movement::Start()
{ int result = 0;
  if ( this->RampingPercentageOfTravel == 0 )  //No ramping, single speed
  { result = 1;
    if ( this->CurrentSpeed > 0 && this->TotalTime > 0)
    { result = 2;
      this->CurrentState=1;
      //GetEncoderValue();
      if ( this->Direction )
        Motor.DirectionForward();
      else
        Motor.DirectionReverse();
      Motor.SetSpeed(this->CurrentSpeed);
      delay(this->TotalTime);
      //GetEncoderValue();
      Motor.SetSpeed(0);
      Motor.Stop();
      result = 3;
      this->CurrentState=0;
    }
  }
  return result;
}


MotorControl::MotorControl()
{
    enB = 3; 
    in3 = 6;
    in4 = 5;   
}

void MotorControl::Init()
{
    // set all the motor control pins to outputs
      pinMode(enB, OUTPUT);
      pinMode(in3, OUTPUT);
      pinMode(in4, OUTPUT);
}

void MotorControl::DirectionForward()
{
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
}
void MotorControl::DirectionReverse()
{
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
}
void MotorControl::Stop()
{
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
}
void MotorControl::SetSpeed(int speed)
{
  analogWrite(enB, speed);
}
void MotorControl::BoostStartup(int boost)
{
  analogWrite(enB, boost);
  delay(20);
}



