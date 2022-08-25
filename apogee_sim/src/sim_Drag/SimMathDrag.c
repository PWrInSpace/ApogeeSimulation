#include "../include/sim_Drag/SimMathDrag.h"

void velocityFromAcceleration(MeasuredData *prev, MeasuredData *cur)
{
	// area of a trapezoid
	cur->velocity = 0.5 * (prev->acceleration + cur->acceleration) *
					(float)(cur->timeInMS - prev->timeInMS) / 1000.0f +
					prev->velocity;
}

void velocityFromHeight(MeasuredData *prev, MeasuredData *cur)
{
	// simple derivative
	cur->velocity = (cur->height - prev->height) /
		   ((float)(cur->timeInMS - prev->timeInMS) / 1000.0f);
}