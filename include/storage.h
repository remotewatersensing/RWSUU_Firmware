/**
 * @file storage.h
 * @author Robin Westerik
 * @brief Allows for saving files on the SD card
 */

#include <Arduino.h>
#include <defines.h>
#include <rtc.h>
#include <led.h>
#include <SD.h>


bool initSD();
bool createFile();
void logFile(uint8_t id, float val);