#include <EEPROM.h>
#include <temperature.h>
#include <DFRobot_PH.h>

DFRobot_PH ph;
float acidity;

void initAcidity()
{
    ph.begin();
}

float getAcidity()
{
    float v = analogRead(acidityPin)/1024.0*5000;
    acidity =  ph.readPH(v,temperature);
#ifdef DEBUG
    Serial.print("Acidity:\tV:");
    Serial.print(v);
    Serial.print("\tpH:");
    Serial.println(acidity,1);
#endif
    return acidity;
}

void clearCalibAcidity()
{
    for(byte i = 0;i< 8; i++)
    {
          EEPROM.write(PHVALUEADDR+i, 0xFF);
    }
}

/*
To calibrate, first run enterph dry, run calph inside 7ph and do exitec if calibrated
Do the same thing for 4ph
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
            v = analogRead(acidityPin)/1024.0*5000;  // read the voltage
            acidity = ph.readPH(v,temperature);  // convert voltage to pH with temperature compensation
            Serial.print("temperature:");
            Serial.print(temperature,1);
            Serial.print("^C  pH:");
            Serial.println(acidity,2);
        }
        ph.calibration(v,temperature);
    }
}

