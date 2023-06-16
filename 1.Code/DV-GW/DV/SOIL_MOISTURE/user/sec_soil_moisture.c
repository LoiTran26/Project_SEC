#include "sec_soil_moisture.h"
 

float SEC_Map(float value, float fromLow, float fromHigh, float toLow, float toHigh)
{
    return (value - fromLow)*(toHigh - toLow)/(fromHigh - fromLow) + toLow;
}
