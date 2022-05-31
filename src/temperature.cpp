#include <temperature.h>

OneWire oneWire(temperaturePin);  
DallasTemperature sensors(&oneWire);
float temperature;

/** @brief Initializes the temperature sensor */
void initTemperature()
{
    sensors.begin();
#ifdef DEBUG
    uint8_t deviceCount = sensors.getDeviceCount();
    Serial.print(F("Sensors found on OneWire: "));
    Serial.print(deviceCount, DEC);
#endif
}

/**
 * @brief Retrieves the temperature value
 * @return float temperature in C
 */
float getTemperature()
{
    sensors.requestTemperatures(); 
    temperature = sensors.getTempCByIndex(0); //Only have one

#ifdef DEBUG
    if(temperature == DEVICE_DISCONNECTED_C)
    {
        Serial.println(F("Temperature sensor not connected"));
    } else
    {
        Serial.print(F("Temperature\t"));
        Serial.print(temperature);
        Serial.println(F("°C"));
    }
#endif

    return temperature;
}