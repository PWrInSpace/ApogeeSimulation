#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"

#define AVG_SAMPLES 3.0f

extern QueueHandle_t dataQueue;
extern QueueHandle_t simQueue;

void dataProcessingTask(void *arg)
{
	MeasuredData tmp1, tmp2,
	sum = { .velocity = 0.0f, .acceleration = 0.0f, .mass = 0.0f };
	size_t i = 0;
	if (xQueueReceive(dataQueue, &tmp1, portMAX_DELAY))
	{
		tmp1.breakAngle = 0.0;
		tmp2.breakAngle = 0.0;
		sum.breakAngle = 0.0;
	}
	while (1)
	{
		if (xQueueReceive(dataQueue, &tmp2, portMAX_DELAY) == pdTRUE)
		{
			velocityFromHeight(&tmp1, &tmp2);
			tmp1 = tmp2;
			sum.velocity += tmp2.velocity;
			if (++i == (size_t)AVG_SAMPLES)
			{
				sum.height = tmp2.height;
				sum.timeInMS = tmp2.timeInMS;
				sum.velocity /= AVG_SAMPLES;
				if (sum.velocity > 0)
				{
					xQueueSend(simQueue, (void *)&sum, 10);
				}
				i = 0;
				sum.velocity = 0.0f;
				sum.mass = 0.0f;
			}
		}
		// ESP_LOGI(pcTaskGetName(NULL), "debug");
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}