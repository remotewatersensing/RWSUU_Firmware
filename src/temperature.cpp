#include <temperature.h>

OneWire oneWire(temperaturePin);  
DallasTemperature sensors(&oneWire);
float temperature;

void initTemperature()
{
    sensors.begin();
#ifdef DEBUG
    uint8_t deviceCount = sensors.getDeviceCount();
    Serial.print("Sensors found on OneWire: ");
    Serial.print(deviceCount, DEC);
#endif
}

float getTemperature()
{
    sensors.requestTemperatures(); 
    temperature = sensors.getTempCByIndex(0); //Only have one

#ifdef DEBUG
    if(temperature == DEVICE_DISCONNECTED_C)
    {
        Serial.println("Temperature sensor not connected");
    } else
    {
        Serial.print("Temperature\t");
        Serial.print(temperature);
        Serial.println("°C");
    }
#endif

    return temperature;
}