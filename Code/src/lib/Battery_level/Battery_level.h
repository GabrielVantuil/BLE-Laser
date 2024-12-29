#ifndef BATTERY_LEVEL_H__
#define BATTERY_LEVEL_H__

#include "nrf_drv_saadc.h"
#include "nrf_delay.h"

#define SAMPLES_IN_BUFFER 	1

static nrf_saadc_value_t     m_buffer_pool[SAMPLES_IN_BUFFER];

void saadc_callback(nrf_drv_saadc_evt_t const * p_event);
void saadc_init(void);
void calcBatteryLevel(void * p_context);
uint8_t getBatteryLevel(void);

#endif
