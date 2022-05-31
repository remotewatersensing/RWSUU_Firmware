#include <conductivity.h>

DFRobot_EC10 ec;
float conductivity;

/** @brief Initializes the conductivity sensor */
void initConductivity()
{
    ec.begin();
}

/**
 * @brief Retrieves the conductivity value
 * @return float conductivity in pH
 */
float getConductivity()
{
    float v = analogRead(conductivityPin)/1024.0*5000;
    conductivity =  ec.readEC(v,temperature);
#ifdef DEBUG
    Serial.print(F("Conductivity:\tV:"));
    Serial.print(v);
    Serial.print(F("\tEC:"));
    Serial.print(conductivity,1);
    Serial.println(F("ms/cm"));
#endif
    return conductivity;
}

/** @brief Removes the conductivity calibration from the EEPROM */
void clearCalibConductivity()
{
    for(byte i = 0;i< 8; i++)
    {
          EEPROM.write(ECVALUEADDR+i, 0xFF);
    }
}

/**
 * @brief Calibrates the conductivity sensor
 * Blocking function which takes control of the serial interface, printing out the temperature and ms/cm repeatedly.
 * Calibrates and saves the values on the EEPROM.
 * To calibrate, connect the MCU with a serial monitor. The following steps should be taken in sequence:
 * 1. Make sure the sensor is not submerged
 * 2. Send: enterec
 * 3. Put your sensor in a 12.88ms/cm solution
 * 4. Send: calec
 * 5. If it returns a success, send: exitec
 *    If it fails, try again
 * @return float 
 */
void calibConductivity()
{
    clearCalibConductivity();
    float v;
    while(true)
    {
        static unsigned long timepoint = millis();
        if(millis()-timepoint>1000U)
        {
            timepoint = millis();
            v = V(analogRead(conductivityPin));
            conductivity =  ec.readEC(v,getTemperature());
            Serial.print(F("voltage:"));
            Serial.print(v);
            Serial.print(F("  temperature:"));
            Serial.print(temperature,1);
            Serial.print(F("^C  EC:"));
            Serial.print(conductivity,1);
            Serial.println(F("ms/cm"));
        }
        ec.calibration(v,temperature);
    }
}