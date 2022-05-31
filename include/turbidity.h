/**
 * @file turbidity.h
 * @author Robin Westerik
 * @brief Interface for turbidity sensor
 */

#include <Arduino.h>
#include <defines.h>

extern uint16_t turbidity; //in NTU

uint16_t getTurbidity(void);