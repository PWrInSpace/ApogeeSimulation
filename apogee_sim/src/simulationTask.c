#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"

const float newBurnoutTime = 10.0f;
const float newStartingMass = 8.0f;
const float newBurnoutMass = 7.0f;

void simulationTask(void *arg)
{

    while (1)
    {
        ESP_LOGI(pcTaskGetName(NULL), "debug");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}