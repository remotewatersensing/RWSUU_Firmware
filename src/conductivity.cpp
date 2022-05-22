#include <conductivity.h>
#include <DFRobot_EC10.h>
#include <EEPROM.h>
#include <temperature.h>
// k = 0.17 (13-05-22)
DFRobot_EC10 ec;
float conductivity;

void initConductivity()
{
    ec.begin();
}

float getConductivity()
{
    float v = analogRead(conductivityPin)/1024.0*5000;
    conductivity =  ec.readEC(v,temperature);
#ifdef DEBUG
    Serial.print("Conductivity:\tV:");
    Serial.print(v);
    Serial.print("\tEC:");
    Serial.print(conductivity,1);
    Serial.println("ms/cm");
#endif
    return conductivity;
}

void clearCalibConductivity()
{
    for(byte i = 0;i< 8; i++)
    {
          EEPROM.write(ECVALUEADDR+i, 0xFF);
    }
}

/*
To calibrate, first run enterec dry, run calec inside 12.88ms/cm and do exitec if calibrated
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
            v = analogRead(conductivityPin)/1024.0*5000;
            conductivity =  ec.readEC(v,getTemperature());
            Serial.print("voltage:");
            Serial.print(v);
            Serial.print("  temperature:");
            Serial.print(temperature,1);
            Serial.print("^C  EC:");
            Serial.print(conductivity,1);
            Serial.println("ms/cm");
        }
        ec.calibration(v,temperature);
    }
}