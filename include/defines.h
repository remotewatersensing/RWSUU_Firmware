/**
 * @file defines.h
 * @author Robin Westerik
 * @brief File containing shared defines like pin declarations, ids, and addresses
 */

#define temperaturePin 9
#define ledPin 4
#define turbidityPin A0
#define conductivityPin A2
#define acidityPin A1


#define temperatureID 0
#define turbidityID 1
#define conductivityID 2
#define acidityID 3

#define DEBUG
#define PHVALUEADDR 0x00
#define ECVALUEADDR 0x0F
#define SDCSPin 10

/** @brief Converts values from analogRead to a voltage */
#define V(i) (i*(5.0 / 1024.0))