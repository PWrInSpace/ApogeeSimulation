#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"

extern SimMath breakerSim;
extern QueueHandle_t simQueue;

#define TIMESTEP 0.1f
#define TIMESTEP_SQ 0.01f

#define G 9.81f
#define GHALF 4.905f

void simulationTask(void *arg)
{
	ESP_LOGI(pcTaskGetName(NULL), "%f", breakerSim.rocketData.emptyMass);
	MeasuredData cur;
	while (1)
	{
		if (xQueueReceive(simQueue, &cur, 10) == pdTRUE)
		{
			ESP_LOGI(pcTaskGetName(NULL),
					 "At start; t=%f; h=%f; a=%f; v=%f; ba=%f", cur.timeInMS,
					 cur.height, cur.acceleration, cur.velocity,
					 cur.breakAngle);
			// do while apogee is not achieved
			while (cur.velocity > 0)
			{
				calculateDragForce(&cur);
				calculateMass(&cur, &breakerSim.rocketData);
				cur.height += cur.velocity * TIMESTEP - (GHALF * TIMESTEP_SQ) -
							  (cur.dragForce / cur.mass * TIMESTEP_SQ * 0.5f);
				cur.velocity -= (G + cur.dragForce / cur.mass) * TIMESTEP;
			}
			ESP_LOGI(pcTaskGetName(NULL),
					 "At end; t=%f; h=%f; a=%f; v=%f; ba=%f", cur.timeInMS,
					 cur.height, cur.acceleration, cur.velocity,
					 cur.breakAngle);
		}
	}
}