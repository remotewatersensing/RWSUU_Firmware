#include <Arduino.h>
#include <defines.h>

extern float conductivity; //in ms/cm

void initConductivity(void);
void calibConductivity(void);
float getConductivity(void);
