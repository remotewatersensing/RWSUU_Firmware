/**
 * @file conductivity.h
 * @author Robin Westerik
 * @brief Interface for conductivity sensor
 */

#include <Arduino.h>
#include <defines.h>
#include <DFRobot_EC10.h>
#include <EEPROM.h>
#include <temperature.h>

extern float conductivity; //in ms/cm

void initConductivity(void);
void calibConductivity(void);
float getConductivity(void);
