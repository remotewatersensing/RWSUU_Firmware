#include <main.h>
#include <conductivity.h>
#include <acidity.h>

int deviceCount = 0;
float tempC;

void setup(void)
{
  Serial.begin(9600);
  initTemperature();
  initConductivity();
  initAcidity();
  //calibConductivity();
  //calibAcidity();
}

void loop(void)
{ 
  getTurbidity();
  getTemperature();
  getConductivity();
  getAcidity();
  delay(500);
}