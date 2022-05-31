#include <turbidity.h>

uint16_t turbidity;

/**
 * @brief Retrieves the turbidity value
 * @return float turbidity in NTU
 */
uint16_t getTurbidity(void)
{   
    float v = V(analogRead(turbidityPin));
    
    //See chart at https://wiki.dfrobot.com/Turbidity_sensor_SKU__SEN0189
    if(turbidity<=4.5){turbidity = (4.5-v)*1500.0;} else {turbidity = 0;}
    
#ifdef DEBUG
    Serial.print(F("Turbidity\tV:"));
    Serial.print(v);
    Serial.print(F("\tNTU: "));
    Serial.println(turbidity);
#endif
    return turbidity;
}

