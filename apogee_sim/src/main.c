#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"
#include "freertos/FreeRTOS.h"

// to state
// machine
// in final
// code
TaskHandle_t simTask = NULL;
TaskHandle_t dataTask = NULL;
TaskHandle_t temstTask = NULL;

QueueHandle_t dataQueue;
QueueHandle_t simQueue;

const float newBurnoutTime = 3.0f;
const float newPropellantMass = 0.857f;
const float newEmptyMass = 3.143f;

SimMath breakerSim = { .rocketData.burnoutTime = newBurnoutTime,
					   .rocketData.emptyMass = newEmptyMass,
					   .rocketData.propellantMass = newPropellantMass };

// TODO: notification to start simulation
void app_main()
{
	dataQueue = xQueueCreate(20, sizeof(MeasuredData));
	simQueue = xQueueCreate(20, sizeof(MeasuredData));
	
	if (xTaskCreatePinnedToCore(simulationTask, "Simulation task", 4096, NULL,
								2, &simTask, APP_CPU_NUM))
	{
		ESP_LOGI(pcTaskGetName(NULL), "Simtask started");
	}
	if (xTaskCreatePinnedToCore(dataProcessingTask, "Data processing task",
								4096, NULL, 2, &dataTask, APP_CPU_NUM))
	{
		ESP_LOGI(pcTaskGetName(NULL), "dataTask started");
	}
	if (xTaskCreatePinnedToCore(testTask, "Test task", 8192, NULL, 2,
								&temstTask, APP_CPU_NUM))
	{
		ESP_LOGI(pcTaskGetName(NULL), "testTask started");
	}

	while (1)
	{
		//ESP_LOGI(pcTaskGetName(NULL), "Dupa");
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}