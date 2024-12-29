
#ifndef BLE_Torch_S_H__
#define BLE_Torch_S_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include "app_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_lbs instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_TORCH_S_DEF(_name)							\
	static ble_torch_s_t _name;      					\
	NRF_SDH_BLE_OBSERVER(_name ## _obs,                 \
                     NRF_BLE_TORCH_OBSERVER_PRIO,       \
                     ble_torch_s_on_ble_evt, &_name)

//"4756-616e-7475-696c5f424c45" = "GVantuil_BLE"
#define TORCH_S_UUID_BASE                 	{0x45, 0x4c, 0x42, 0x5f, 0x6c, 0x69, 0x75, 0x74, 0x6e, 0x61, 0x56, 0x47, 0, 0, 0, 0}
#define TORCH_S_UUID_SERVICE				0x0000
#define TORCH_S_UUID_LOCK_CHAR				0x0001
#define TORCH_S_UUID_LED_POWER_CHAR			0x0002
#define TORCH_S_UUID_LED_PWM_CHAR			0x0003
#define TORCH_S_UUID_READ_LDR_CHAR			0x0006


// Forward declaration of the ble_lbs_t type.
typedef struct ble_torch_s_s ble_torch_s_t;

typedef void (*ble_torch_s_lock_handler_t)         		(uint16_t conn_handle, ble_torch_s_t * p_torch_s, uint8_t lock);
typedef void (*ble_torch_s_led_power_handler_t)    		(uint16_t conn_handle, ble_torch_s_t * p_torch_s, const uint8_t *params);
typedef void (*ble_torch_s_led_pwm_handler_t)     		(uint16_t conn_handle, ble_torch_s_t * p_torch_s, const uint8_t *params);

typedef struct{			/**< Event handler to be called when which Characteristic is written. */
    ble_torch_s_lock_handler_t              lock_handler;
    ble_torch_s_led_power_handler_t         led_power_handler;
    ble_torch_s_led_pwm_handler_t           led_pwm_handler;
} ble_torch_s_init_t;

/**@brief LED Button Service structure. This structure contains various status information for the service. */
struct ble_torch_s_s{
    uint16_t                    service_handle;
    ble_gatts_char_handles_t    lock_handles; 
    ble_gatts_char_handles_t    led_power_handles;
    ble_gatts_char_handles_t    led_pwm_handles;
    ble_gatts_char_handles_t    read_ldr_handles;  
	
    uint8_t                     uuid_type;                              /**< UUID type for the Tag Service. */
    ble_torch_s_lock_handler_t				lock_handler;
    ble_torch_s_led_power_handler_t			led_power_handler;
    ble_torch_s_led_pwm_handler_t	        led_pwm_handler;
};

/**@brief Function for initializing the Tag Service.
 *
 * @param[out] p_torch_s      Tag Service structure. This structure must be supplied by
 *                        	the application. It is initialized by this function and will later
 *                        	be used to identify this particular service instance.
 * @param[in] p_torch_s_init  Information needed to initialize the service.
 *
 * @retval NRF_SUCCESS If the service was initialized successfully. Otherwise, an error code is returned.
 */
uint32_t ble_torch_s_init(ble_torch_s_t * p_torch_s, const ble_torch_s_init_t * p_torch_s_init);


/**@brief Function for handling the application's BLE stack events.
 *
 * @details This function handles all events from the BLE stack that are of interest to the LED Button Service.
 *
 * @param[in] p_ble_evt  Event received from the BLE stack.
 * @param[in] p_context  Tag Service structure.
 */
void ble_torch_s_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for sending a button state notification.
 *
 ' @param[in] conn_handle   Handle of the peripheral connection to which the button state notification will be sent.
 * @param[in] p_torch_s       Tag Service structure.
 * @param[in] button_state  New button state.
 *
 * @retval NRF_SUCCESS If the notification was sent successfully. Otherwise, an error code is returned.
 */
//uint32_t ble_lbs_on_button_change(uint16_t conn_handle, ble_torch_s_t * p_torch_s, uint8_t button_state);


#ifdef __cplusplus
}
#endif

#endif // BLE_LBS_H__

/** @} */
