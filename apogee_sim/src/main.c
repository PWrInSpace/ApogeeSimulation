#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"
#include "freertos/FreeRTOS.h"

// to state
// machine
// in final
// code
TaskHandle_t simTask = NULL;
QueueHandle_t dataQueue;

const float newBurnoutTime = 10.0f;
const float newStartingMass = 8.0f;
const float newBurnoutMass = 7.0f;

SimMath breakerSim = { .rocketData.burnoutTime = newBurnoutTime,
					   .rocketData.burnoutMass = newBurnoutMass,
					   .rocketData.startingMass = newStartingMass };
// TODO: notification to start simulation
void app_main()
{
	if (xTaskCreatePinnedToCore(simulationTask, "State task", 4096, NULL, 2,
								&simTask, APP_CPU_NUM))
	{
		ESP_LOGI(pcTaskGetName(NULL), "Simtask started");
	}

	dataQueue = xQueueCreate(20, sizeof(MeasuredData));

	while (1)
	{
		ESP_LOGI(pcTaskGetName(NULL), "Dupa");
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}