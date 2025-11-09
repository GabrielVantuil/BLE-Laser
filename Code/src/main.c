#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "app_timer.h"

#include "nrf_drv_gpiote.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "nrf_drv_clock.h"
#include "nrf_delay.h"

#include "app_ble.h"
#include "handles.h"
#include "Battery_level.h"
#include "app_pwm.h"

static void log_init(void){
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

static void lfclk_config(void){
	// initialize the low power low frequency clock
  APP_ERROR_CHECK(nrf_drv_clock_init());

	// request the lf clock to not to generate any events on ticks
	// One tick =  1 value increment in the counter register
  nrf_drv_clock_lfclk_request(NULL);
}

void blinkRGB(){
	nrf_gpio_cfg_output(LED_R);
	nrf_gpio_cfg_output(LED_G);
	nrf_gpio_cfg_output(LED_B);
	nrf_gpio_pin_write(LED_R, 1);
	nrf_gpio_pin_write(LED_G, 1);
	nrf_gpio_pin_write(LED_B, 1);
	
	nrf_gpio_pin_write(LED_R, 0);
	nrf_delay_ms(100);
	nrf_gpio_pin_toggle(LED_R);
	nrf_gpio_pin_write(LED_G, 0);
	nrf_delay_ms(100);
	nrf_gpio_pin_toggle(LED_G);
	nrf_gpio_pin_write(LED_B, 0);
	nrf_delay_ms(100);
	nrf_gpio_pin_toggle(LED_B);
}

void pwm_laser_ready_callback(uint32_t pwm_id){}
void setPwmLaser(app_pwm_t const * const p_instance, uint16_t val){
	uint32_t ticks = ((uint32_t)app_pwm_cycle_ticks_get(p_instance) * (uint32_t)val) / 100UL;
	while (app_pwm_channel_duty_ticks_set(p_instance, 0, ticks) == NRF_ERROR_BUSY);
}
		
uint16_t getAdc(void){
    nrf_saadc_value_t value;
    APP_ERROR_CHECK(nrf_drv_saadc_sample_convert(0, &value));
	if(value>10000) value=0;
    return value;
}

APP_PWM_INSTANCE(PWM_LASER, 1);
/**@brief Function for application main entry.
 */
	
#define GET_TEST_BT 	(!nrf_gpio_pin_read(TEST_BT))
#define GET_FULL_BT 	(!nrf_gpio_pin_read(FULL_PWR_BT))
	
int main(void){
    // Initialize.
    lfclk_config();
    log_init();
//    leds_init();
    timers_init();
    APP_ERROR_CHECK(nrf_pwr_mgmt_init());
    ble_stack_init();
    gap_params_init();
    gatt_init();
    services_init();
    advertising_init();
    conn_params_init();
	blinkRGB();
//	calcBatteryLevel(NULL);
	// sd_ble_gap_tx_power_set(BLE_GAP_TX_POWER_ROLE_ADV, m_adv_handle, 4);
	
    // Start execution.
	advertising_start();
	
    APP_ERROR_CHECK(nrf_drv_saadc_init(NULL, NULL));
    nrf_saadc_channel_config_t channel_config = 
		NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN3);
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(0, &channel_config));
	
	nrf_gpio_cfg_input(TEST_BT, NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_input(FULL_PWR_BT, NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_output(LASER_PWR_CTRL);
	
    app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_1CH(10, LASER_CTRL);
    APP_ERROR_CHECK(app_pwm_init(&PWM_LASER, &pwm1_cfg, pwm_laser_ready_callback));
    app_pwm_enable(&PWM_LASER);
    // Enter main loop.
    for (;;){
		if(GET_TEST_BT || GET_FULL_BT){
			nrf_gpio_pin_write(LED_G, LED_OFF);
			
			nrf_gpio_cfg_output(LASER_PWR_CTRL);
			nrf_gpio_pin_write(LASER_PWR_CTRL, LASER_PWR_ON);
			if(GET_TEST_BT ^ GET_FULL_BT){
				nrf_gpio_pin_write(LED_R, LED_OFF);
				nrf_gpio_pin_write(LED_B, LED_ON);
				app_pwm_channel_duty_set(&PWM_LASER, 0, 98 - (getAdc()/50));
			}
			else if(GET_TEST_BT && GET_FULL_BT){
				nrf_gpio_pin_write(LED_R, LED_ON);
				nrf_gpio_pin_write(LED_B, LED_OFF);
				app_pwm_channel_duty_set(&PWM_LASER, 0, 0);
			}
		}
		else{
			nrf_gpio_cfg_default(LASER_PWR_CTRL);
			app_pwm_channel_duty_set(&PWM_LASER, 0, 100);
			nrf_gpio_pin_write(LED_R, LED_OFF);
			nrf_gpio_pin_write(LED_B, LED_OFF);
			nrf_gpio_pin_write(LED_G, LED_ON);
		}
    }
}


/**
 * @}
 */
