#include "Battery_level.h"

volatile uint8_t batteryLevel;

void saadc_callback(nrf_drv_saadc_evt_t const * p_event){
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE){
        APP_ERROR_CHECK(nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, SAMPLES_IN_BUFFER));

		batteryLevel = p_event->data.done.p_buffer[0]>>2;
    }
	nrfx_saadc_uninit();
}

void saadc_init(void){
    nrf_saadc_channel_config_t channel_config = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_VDD);
	APP_ERROR_CHECK(nrf_drv_saadc_init(NULL, saadc_callback));
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(0, &channel_config));
    APP_ERROR_CHECK(nrfx_saadc_buffer_convert(m_buffer_pool, SAMPLES_IN_BUFFER));
}

void calcBatteryLevel(void * p_context){
    saadc_init();
//	batteryLevel = 0;
	nrfx_saadc_sample();
//	nrf_delay_ms(10);
//	nrfx_saadc_uninit();
}

uint8_t getBatteryLevel(){
	return batteryLevel;
}
