#ifndef SIM_MATH_DRAG_H
#define SIM_MATH_DRAG_H
#include "RocketConfigDrag.h"

struct SimMath
{
    RocketConfig rocketData;
};

struct MeasuredData
{
    float t;
    float v;
    float a;
};

#endif