#ifndef SIM_MATH_DRAG_H
#define SIM_MATH_DRAG_H
#include "RocketConfigDrag.h"

#include "freertos/queue.h"
#include "freertos/timers.h"

typedef struct
{
    float t;
    float v;
    float a;
}MeasuredData;

typedef struct
{
    RocketConfig rocketData;
    QueueHandle_t dataQueue;
    TimerHandle_t simTimer;
}SimMath;

#endif