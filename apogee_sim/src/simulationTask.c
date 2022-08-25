#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"

extern SimMath breakerSim;
extern QueueHandle_t dataQueue;

void simulationTask(void *arg)
{
	MeasuredData tmp1, tmp2;
	ESP_LOGI(pcTaskGetName(NULL), "%f", breakerSim.rocketData.burnoutMass);
	while(xQueueReceive(dataQueue, &tmp1, 10) != pdTRUE)
	{
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
	while (1)
	{
		if(xQueueReceive(dataQueue, &tmp2, 10) == pdTRUE)
		{
			velocityFromHeight(&tmp1, &tmp2);
			tmp1 = tmp2;
		}
		ESP_LOGI(pcTaskGetName(NULL), "debug");
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}