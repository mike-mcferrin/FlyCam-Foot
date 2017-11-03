#ifndef SkyKamExtras_h
#define SkyKamExtras_h

class MotorControl
{
  public:
    MotorControl();
    void Init();
    void DirectionForward();
    void DirectionReverse();
    void Stop();
    void SetSpeed(int _speed); 
    void BoostStartup(int boost);
  private:
    int enB; 
    int in3;
    int in4;   
};

class Movement
{
  public:
    Movement();
    Movement(int currentSpeed, int totalTime, bool direction);
    int TotalSteps;
    int CurrentStep;
    int TotalDistance;
    int TotalTime;
    int SpeedMinimum;
    int SpeedMaximum;
    int CurrentSpeed;
    float RampingPercentageOfTravel;
    float RampingIncrement;
    long TimeStarted;
    long TimeEnded;
    long TimeToFullStop;
    int Start(int currentSpeed, int totalTime);
    int Start();
	int Direction;
    int CurrentState;
    MotorControl Motor;
};


#endif


