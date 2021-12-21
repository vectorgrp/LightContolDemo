#ifndef IO_H
#define IO_H

#include "LightCtrl_SWC.h"

void Output_HeadLight(uint8_T headLightValue);
void Input_LightSwitch(uint8_T *value);
void Input_LightIntensity(uint16_T * lightIntesityValue);

#endif // IO_H
