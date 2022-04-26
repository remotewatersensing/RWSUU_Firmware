#include <turbidity.h>

uint16_t turbidity;

uint16_t getTurbidity(void)
{   
    float v = analogRead(turbidityPin) * (5.0 / 1024.0);
    turbidity = (v<2.5) ? 3000 : -1120.4*square(v)+ 5742.3*v - 4352.9;
#ifdef DEBUG
    Serial.print("Turbidity\tV:");
    Serial.print(v);
    Serial.print("\tNTU: ");
    Serial.println(turbidity);
#endif
    return turbidity;
}

