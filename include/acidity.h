/**
 * @file acidity.h
 * @author Robin Westerik
 * @brief Interface for acidity sensor
 */

#include <Arduino.h>
#include <defines.h>
#include <DFRobot_PH.h>
#include <EEPROM.h>
#include <temperature.h>

extern float acidity;//In pH

void initAcidity(void);
float calibAcidity(void);
float getAcidity(void);