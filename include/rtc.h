/**
 * @file rtc.h
 * @author Robin Westerik
 * @brief Controls the RTC
 */

#include <defines.h>
#include <DS1307RTC.h>
#include <Arduino.h>

uint8_t getDay();
uint8_t getMonth();
uint16_t getYear();
uint8_t getHour();
uint8_t getMinute();
uint8_t getSecond();


void getDigits(int number);
bool initRTC();
bool readRTC();