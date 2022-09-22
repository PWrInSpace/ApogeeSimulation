#ifndef SIM_MATH_DRAG_H
#define SIM_MATH_DRAG_H
#include "RocketConfigDrag.h"
#include "freertos/queue.h"
#include "freertos/timers.h"


typedef struct MeasuredData
{
	float timeInMS; // time from start
	float height;
	float acceleration;
	float velocity;
	float breakAngle;
	float mass;
	float dragForce;
} MeasuredData;

typedef struct SimMath
{
	RocketConfig rocketData;
	// will be implemenented in state machine
} SimMath;

void velocityFromAcceleration(MeasuredData *prev, MeasuredData *cur);

void velocityFromHeight(MeasuredData *prev, MeasuredData *cur);

void calculateDragForce(MeasuredData *cur);

void calculateMass(MeasuredData *cur, RocketConfig *rocket);

#endif