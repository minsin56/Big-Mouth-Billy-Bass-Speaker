#include "Utils.h"
#include <Arduino.h>
#include <Wire.h>
 
int Utils::ReadSound()
{
    int Left = analogRead(A1);
    int Right = analogRead(A2);


    return Left + Right;
}

void Utils::ExecuteAfterDelay(int MS, void Exec())
{
    delay(MS);
    Exec();
}