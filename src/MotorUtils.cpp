#include "MotorUtils.h"
#include <MotorDriver.h>

static MotorDriver Motors;

void MotorUtils::Motor(int Index,int Direction,int Speed)
{
    Motors.motor(Index,Direction,Speed);
}

void MotorUtils::SpinMotor(int Index, int Speed)
{
    int Direction;
    if(Speed < 0)
    {
        Direction = BACKWARD;
    }
    else if(Speed > 0)
    {
        Direction = FORWARD;
    }
    else
    {
        Direction = BRAKE;
    }

    Motors.motor(Index, Direction, Speed);
}



void MotorUtils::StopMotor(int Index)
{
    Motors.motor(Index,BRAKE,255);
}

void MotorUtils::ReleaseMotor(int Index)
{
    Motors.motor(Index,RELEASE,255);
}