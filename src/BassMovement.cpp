#include "BassMovement.h"
#include "Utils.h"
#include "Pins.h"
#include "MotorUtils.h"
#include<MotorDriver.h>

void BassMovement::OpenMouth()
{
    MotorUtils::ReleaseMotor(MouthMotorPin);
    MotorUtils::SpinMotor(MouthMotorPin,255);
    delay(1);
    MotorUtils::SpinMotor(MouthMotorPin,0);
}

void BassMovement::CloseMouth()
{
    MotorUtils::ReleaseMotor(MouthMotorPin);
    MotorUtils::SpinMotor(MouthMotorPin,-255);
    delay(1);
    MotorUtils::SpinMotor(MouthMotorPin,0);
}

void BassMovement::FlapTail(int Times,int Duration)
{
    if(IsFlappingTail)
    {
        Utils::Print("Tail Is Flapping Already");
        return;
    }

    Utils::Print("Tail Started Flapping");

    IsFlappingTail = true;
    for(int i = 0; i < Times;i++)
    {
        //spin the body motor backwards to flap the tail
        MotorUtils::SpinMotor(BodyMotorPin,-255);
        delay(Duration);
        MotorUtils::ReleaseMotor(BodyMotorPin);
        delay(Duration);
    }

    MotorUtils::ReleaseMotor(BodyMotorPin);

    IsFlappingTail = false;
}

void BassMovement::MoveBody(bool IsTalking)
{
    if(IsTalking)
    {
        if(millis() > BodyThen)
        {
            int R = floor(random(0,8));

            if(R < 1)
            {
                BodySpeed = 0;
                BodyThen = millis() + floor(random(500,1000));
                BodyDirection = FORWARD;
            }
            else if(R < 3)
            {
                BodySpeed = 150;
                BodyThen = millis() + floor(random(500,1000));
                BodyDirection = FORWARD;
            }
            else if(R == 4)
            {
                BodySpeed = 200;
                BodyThen = millis() + floor(random(500,1000));
                BodyDirection = FORWARD;
            }
            else if(R == 5)
            {
                BodySpeed = 0;
                MotorUtils::ReleaseMotor(BodyMotorPin);
                delay(1);
                BodyDirection = BACKWARD;
                MotorUtils::SpinMotor(BodyMotorPin,-255);
                delay(1);
                BodyThen = millis() + floor(random(900,1200));
            }
            else
            {
                BodySpeed = 255;
                BodyThen = millis() + floor(random(1500,3000));
            }
            MotorUtils::SpinMotor(BodyMotorPin,BodyDirection == 0 ? -BodySpeed:BodySpeed);

            Utils::Print("Body Direction:" + BodyDirection);
 
        }
        else
        {
            if(millis() > BodyThen)
            {
                MotorUtils::ReleaseMotor(BodyMotorPin);
                BodyThen = millis() + floor(random(20,50));
            }
        }
    }
}