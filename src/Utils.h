#include <Arduino.h>

namespace Utils
{
    int ReadSound();

    void ExecuteAfterDelay(int MS, void Exec());
    template<typename Ty>
    void Print(Ty Object)
    {
        Serial.println(Object);

    }
    
}