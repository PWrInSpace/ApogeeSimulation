#ifndef TASKS_H
#define TASKS_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/// \brief ** S I M U L A T I O N ** O F ** A P O G E E **
void simulationTask(void *arg);

/// \brief Process and prepare data for simulationTask
void dataProcessingTask(void *arg);

/// \brief Injecting data into the simulator via queue
void testTask(void *arg);

#endif