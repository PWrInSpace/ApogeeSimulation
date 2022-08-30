#include "../include/sim_Drag/SimMathDrag.h"

void velocityFromAcceleration(MeasuredData *prev, MeasuredData *cur)
{
	// area of a trapezoid
	cur->velocity = 0.5 * (prev->acceleration + cur->acceleration) *
					(cur->timeInMS - prev->timeInMS) +
					prev->velocity;
}

void velocityFromHeight(MeasuredData *prev, MeasuredData *cur)
{
	// simple derivative
	cur->velocity =
	(cur->height - prev->height) / (cur->timeInMS - prev->timeInMS);
}


void calculateDragForce(MeasuredData *cur)
{
	static const float dragCoeffs[6] = { 1.64088047e+00,  -7.39657125e-2,
										 -1.16091823e-02, 2.58012239e-03,
										 4.44306647e-04,  -7.55789478e-04 };
	cur->dragForce = dragCoeffs[0] + dragCoeffs[1] * cur->velocity +
					 dragCoeffs[2] * cur->breakAngle +
					 dragCoeffs[3] * cur->velocity * cur->breakAngle +
					 dragCoeffs[4] * cur->velocity * cur->velocity +
					 dragCoeffs[5] * cur->breakAngle * cur->breakAngle;
}

void calculateMass(MeasuredData *cur, RocketConfig *rocket)
{
	if (cur->timeInMS > rocket->burnoutTime)
	{
		cur->mass = rocket->emptyMass;
	}
	else
	{
		cur->mass =
		rocket->emptyMass +
		rocket->propellantMass * (1.0f - cur->timeInMS / rocket->burnoutTime);
	}
}