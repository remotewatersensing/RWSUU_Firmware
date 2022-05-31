#include <led.h>
/**
 * @brief Shows the user a fatal error has occured and the program can't continue
 */
void errorLoop()
{
    pinMode(ledPin,OUTPUT);
    while(true)
    {
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
}