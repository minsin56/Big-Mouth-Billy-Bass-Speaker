#include "MotorUtils.h"
#include "BassMovement.h"
#include "Pins.h"
#include "Utils.h"
#include "Config.h"


bool IsTalking = false;


void ResetSensorBoundary()
{
    BassMovement::MaxSeen = 1600;
    BassMovement::MinSeen = 0;
}

void UpdateSensorHistory(int SensorValue)
{
    if(BassMovement::MaxSeen < SensorValue)
    {
        BassMovement::MaxSeen = SensorValue;
    }

    if(BassMovement::MinSeen > SensorValue)
    {
        BassMovement::MinSeen = SensorValue;
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);

    BassMovement::MouthThen = millis();
    BassMovement::BodyThen = millis();
    BassMovement::LastTalked = millis();
    BassMovement::BodySpeed = 255;
}


void loop()
{
    int Sound = Utils::ReadSound();

    Utils::Print(Sound);


    if(Sound < SilentVolumeThreshold && IsTalking)
    {
        if(millis() > BassMovement::MouthThen)
        {
            IsTalking = false;

            BassMovement::MouthThen = millis() + floor(random(75, 150));
        }
    }
    else if(Sound > SilentVolumeThreshold)
    {
        if(millis() > BassMovement::MouthThen)
        {
            IsTalking = true;
            BassMovement::MouthThen = millis() + floor(random(70, 100));
        }
    }

    if(millis() < BassMovement::MouthThen)
    {
        if(IsTalking)
        {
            BassMovement::OpenMouth();
            BassMovement::LastTalked = millis();
            BassMovement::MoveBody(true);
            Utils::Print("Opened Mouth");
        }
        else
        {
            BassMovement::CloseMouth();
            BassMovement::MoveBody(false);
            Utils::Print("Closed Mouth");
        }
    }
    else
    {
        IsTalking = false;
    }

    if(millis() - BassMovement::LastTalked > 800)
    {
        BassMovement::LastTalked = millis() + 60l * 60l * 1000l;
        BassMovement::FlapTail(floor(random(1,5)),floor(random(10,100)));
        MotorUtils::ReleaseMotor(BodyMotorPin);
    }

    delay(10);
}