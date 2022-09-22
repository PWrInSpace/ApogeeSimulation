#include "../include/sim_Drag/SimMathDrag.h"
#include "../include/tasks.h"

extern SimMath breakerSim;
extern QueueHandle_t simQueue;

#define TIMESTEP 0.005f // in seconds :)


#define G 9.81f
#define GHALF 4.905f

void simulationTask(void *arg)
{
	ESP_LOGI(pcTaskGetName(NULL), "%f", breakerSim.rocketData.emptyMass);
	MeasuredData cur, prev;
	ESP_LOGI(
	pcTaskGetName(NULL),
	";time of start; height at start; time of end sim; height of end sim;");
	while (1)
	{
		if (xQueueReceive(simQueue, &cur, 10) == pdTRUE)
		{
			prev = cur;
			/*ESP_LOGI(pcTaskGetName(NULL),
					 "At start; t=%f; h=%f; a=%f; v=%f; ba=%f", cur.timeInMS,
					 cur.height, cur.acceleration, cur.velocity,
					 cur.breakAngle);*/
			// do while apogee is not achieved
			while (cur.velocity > 0)
			{
				calculateDragForce(&cur);
				calculateMass(&cur, &breakerSim.rocketData);
				cur.height =
				cur.height + cur.velocity * TIMESTEP -
				(GHALF * TIMESTEP * TIMESTEP) -
				(cur.dragForce / cur.mass * TIMESTEP * TIMESTEP * 0.5f);
				cur.velocity =
				cur.velocity - (G + cur.dragForce / cur.mass) * TIMESTEP;
				cur.timeInMS += TIMESTEP * 1000.f;
			}
			/*ESP_LOGI(pcTaskGetName(NULL),
					 "At end; t=%f; h=%f; a=%f; v=%f; ba=%f\n", cur.timeInMS,
					 cur.height, cur.acceleration, cur.velocity,
					 cur.breakAngle);*/
			ESP_LOGI(pcTaskGetName(NULL), ";%f; %f; %f; %f;", prev.timeInMS,
					 prev.height, cur.timeInMS, cur.height);
		}
	}
}