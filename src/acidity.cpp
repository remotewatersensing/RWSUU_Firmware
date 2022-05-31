#include <acidity.h>

DFRobot_PH ph;
float acidity;

/** @brief Initializes the acidity sensor */
void initAcidity()
{
    ph.begin();
}

/**
 * @brief Retrieves the acidity value
 * @return float acidity in pH
 */
float getAcidity()
{
    float v = V(analogRead(acidityPin));
    acidity =  ph.readPH(v,temperature);
#ifdef DEBUG
    Serial.print("Acidity:\tV:");
    Serial.print(v);
    Serial.print("\tpH:");
    Serial.println(acidity,1);
#endif
    return acidity;
}
/** @brief Removes the acidity calibration from the EEPROM */
void clearCalibAcidity()
{
    for(byte i = 0;i< 8; i++)
    {
          EEPROM.write(PHVALUEADDR+i, 0xFF);
    }
}

/**
 * @brief Calibrates the acidity sensor
 * Blocking function which takes control of the serial interface, printing out the temperature and pH repeatedly.
 * Calibrates and saves the values on the EEPROM.
 * To calibrate, connect the MCU with a serial monitor. The following steps should be taken in sequence:
 * 1. Make sure the sensor is not submerged
 * 2. Send: enterph
 * 3. Put your sensor in distilled water with a pH of 7
 * 4. Send: calph
 * 5. If it returns a success, send: exitec
 *    If it fails, try again
 * Repeat the steps in water with a pH of 4
 * @return float 
 */
float calibAcidity()
{
    clearCalibAcidity();
    float v;
    while(true)
    {
        static unsigned long timepoint = millis();
        if(millis()-timepoint>1000U){                  //time interval: 1s
            timepoint = millis();
            temperature = getTemperature();         // read your temperature sensor to execute temperature compensation
            v = V(analogRead(acidityPin));  // read the voltage
            acidity = ph.readPH(v,temperature);  // convert voltage to pH with temperature compensation
            Serial.print("temperature:");
            Serial.print(temperature,1);
            Serial.print("^C  pH:");
            Serial.println(acidity,2);
        }
        ph.calibration(v,temperature);
    }
}

