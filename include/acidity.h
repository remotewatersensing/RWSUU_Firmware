#include <Arduino.h>
#include <defines.h>

extern float acidity;//In pH

void initAcidity(void);
void calibAcidity(void);
float getAcidity(void);