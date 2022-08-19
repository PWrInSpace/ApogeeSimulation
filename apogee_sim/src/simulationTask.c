#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"
#include "timer.h"

const float newBurnoutTime = 10.0f;
const float newStartingMass = 8.0f;
const float newBurnoutMass = 7.0f;
float newDragVsVelocity[] = { 1.0, 2.0, 3.0 };

SimMath breakerSim = { .rocketData.burnoutTime = newBurnoutTime,
					   .rocketData.burnoutMass = newBurnoutMass,
					   .rocketData.startingMass = newStartingMass,
					   .rocketData.dragVsVelocity = newDragVsVelocity };
					   
void simulationTask(void *arg)
{
	breakerSim.dataQueue = xQueueCreate(20, sizeof(MeasuredData));
	breakerSim.simTimer = xTimerCreate("Simulation Timer", pdMS_TO_TICKS(1),
									   pdTRUE, (void *)0, vTimerCallback);
	while (1)
	{
		ESP_LOGI(pcTaskGetName(NULL), "debug");
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}