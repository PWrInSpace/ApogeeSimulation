#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"

extern SimMath breakerSim;

void simulationTask(void *arg)
{
	ESP_LOGI(pcTaskGetName(NULL), "%f", breakerSim.rocketData.burnoutMass);
	while (1)
	{
		ESP_LOGI(pcTaskGetName(NULL), "debug");
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}