/**
 * @file temperature.h
 * @author Robin Westerik
 * @brief Interface for temperature sensor
 */

#include <OneWire.h>
#include <DallasTemperature.h>
#include <defines.h>

extern float temperature;

void initTemperature();
float getTemperature();