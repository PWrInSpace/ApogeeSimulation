#ifndef SIM_MATH_DRAG_H
#define SIM_MATH_DRAG_H
#include "RocketConfigDrag.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

typedef struct MeasuredData
{
	uint64_t timeInMS;
	float height;
	float acceleration;
	float velocity;
} MeasuredData;

typedef struct SimMath
{
	RocketConfig rocketData;
 // will be implemenented in state machine
} SimMath;

void velocityFromAcceleration(MeasuredData *prev, MeasuredData *cur);

void velocityFromHeight(MeasuredData *prev, MeasuredData *cur);

#endif