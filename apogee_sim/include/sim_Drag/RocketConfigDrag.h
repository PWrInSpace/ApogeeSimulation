#ifndef ROCKET_CONFIG_DRAG_H
#define ROCKET_CONFIG_DRAG_H

#include "Arduino.h"

constexpr uint8_t VelocitySamples = 0;
constexpr uint8_t DragSamples = 0;



class RocketConfig
{
    private:
    const static float DragVsVelocity[VelocitySamples][DragSamples];
};

#endif