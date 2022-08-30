#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"

#define AVG_SAMPLES 10.0f

extern QueueHandle_t dataQueue;
extern QueueHandle_t simQueue;

void dataProcessingTask(void *arg)
{
	MeasuredData tmp1, tmp2, sum;
	size_t i = 0;
	while (xQueueReceive(dataQueue, &tmp1, 10) != pdTRUE)
	{
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
	sum.velocity = tmp1.velocity;
	sum.acceleration = tmp1.acceleration;
	sum.breakAngle = 0.0;
	while (1)
	{
		if (xQueueReceive(dataQueue, &tmp2, 10) == pdTRUE)
		{
			velocityFromHeight(&tmp1, &tmp2);
			tmp1 = tmp2;
			sum.velocity += tmp1.velocity;
			sum.acceleration += tmp1.acceleration;

			if (++i == (int)AVG_SAMPLES)
			{
				sum.velocity /= AVG_SAMPLES;
				sum.acceleration /= AVG_SAMPLES;
				sum.height = tmp2.height;
				sum.timeInMS = tmp2.timeInMS;
				xQueueSend(simQueue, (void *)&sum, 10);
				i = 0;
			}
		}
		ESP_LOGI(pcTaskGetName(NULL), "debug");
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}