#ifndef ROCKET_CONFIG_DRAG_H
#define ROCKET_CONFIG_DRAG_H

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef struct RocketConfig
{
	const float burnoutTime;
	const float startingMass;
	const float burnoutMass;
} RocketConfig;


#endif