#include "freertos/FreeRTOS.h"

#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"

// to state machine in final code
TaskHandle_t simTask = NULL;

void app_main()
{
  if(xTaskCreatePinnedToCore(simulationTask, "State task", 4096, NULL, 2, &simTask, APP_CPU_NUM))
  {
    ESP_LOGI(pcTaskGetName(NULL), "SimTask started");
  }
  while(1)
  {
    ESP_LOGI(pcTaskGetName(NULL), "Dupa");
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}