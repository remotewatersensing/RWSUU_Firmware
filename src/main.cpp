#include <main.h>

/**
 * @brief Setting up the peripherals
 * It initializes the sensors, initializes the real time clock, and creates a new file on the SD card where files can be logged
 */
void setup(void)
{
  Serial.begin(9600);
  while (!Serial) {}; // wait for serial
  initTemperature();
  initConductivity();
  initAcidity();
  initRTC();
  initSD();
  createFile();
  logFile(0,0);
  logFile(0,0);
}


/**
 * @brief Main loop that logs the sensor values to the SD card
 */
void loop(void)
{
  logFile(temperatureID,getTemperature());
  logFile(turbidityID,getTurbidity());
  logFile(conductivityID,getConductivity());
  logFile(acidityID,getAcidity());
  delay(5000);
}
