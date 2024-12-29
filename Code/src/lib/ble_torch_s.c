#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_TORCH_S)
#include "ble_torch_s.h"
#include "ble_srv_common.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "handles.h"

/**@brief Function for handling the Write event.
 *
 * @param[in] p_lbs      LED Button Service structure.
 * @param[in] p_ble_evt  Event received from the BLE stack.
 */
void on_write(ble_torch_s_t * p_torch_s, ble_evt_t const * p_ble_evt){
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

	if((p_evt_write->handle == p_torch_s->lock_handles.value_handle)                && (p_evt_write->len == 1)  && (p_torch_s->lock_handler != NULL)){
		NRF_LOG_INFO("lock_handler");
        p_torch_s->lock_handler(p_ble_evt->evt.gap_evt.conn_handle, p_torch_s, p_evt_write->data[0]);
    }
    else if ((p_evt_write->handle == p_torch_s->led_power_handles.value_handle)     && (p_evt_write->len == 5)  && (p_torch_s->led_power_handler != NULL)){
		NRF_LOG_INFO("led_power_handler");
        p_torch_s->led_power_handler(p_ble_evt->evt.gap_evt.conn_handle, p_torch_s, p_evt_write->data);
    }
    else if ((p_evt_write->handle == p_torch_s->led_pwm_handles.value_handle)       && (p_evt_write->len == 10)  && (p_torch_s->led_pwm_handler != NULL)){
		NRF_LOG_INFO("led_pwm_handler");
        p_torch_s->led_pwm_handler(p_ble_evt->evt.gap_evt.conn_handle, p_torch_s, p_evt_write->data);
    }
	else {
		NRF_LOG_INFO("write handle not found");
	}
    NRF_LOG_FLUSH();
}

void ble_torch_s_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context){
    ble_torch_s_t * p_torch_s = (ble_torch_s_t *)p_context;
    switch (p_ble_evt->header.evt_id){
        case BLE_GATTS_EVT_WRITE:
            on_write(p_torch_s, p_ble_evt);
            break;
        default:	//No implementation needed.
//            NRF_LOG_INFO("Event unhadled: %d", p_ble_evt->header.evt_id);
            break;
    }
}
uint32_t configAndAddChar(ble_torch_s_t * p_torch_s, uint16_t uuid, uint16_t len, bool isWrite, ble_gatts_char_handles_t * p_char_handle){
    ble_add_char_params_t add_char_params;
    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid              = uuid;
    add_char_params.uuid_type         = p_torch_s->uuid_type;
    add_char_params.init_len          = len;
    add_char_params.max_len           = len;
    add_char_params.char_props.read   = !isWrite;
    add_char_params.char_props.write  = isWrite;
	
    add_char_params.read_access       = SEC_OPEN;
    add_char_params.write_access 	  = SEC_OPEN;
//	if(!isWrite)    add_char_params->p_init_value	  = packet;
    return characteristic_add(p_torch_s->service_handle, &add_char_params, p_char_handle);
}

uint32_t ble_torch_s_init(ble_torch_s_t * p_torch_s, const ble_torch_s_init_t * p_torch_s_init){
    uint32_t              err_code;
    ble_uuid_t            ble_uuid;

    // Initialize service structure.
    p_torch_s->lock_handler             = p_torch_s_init->lock_handler;
	p_torch_s->led_power_handler        = p_torch_s_init->led_power_handler;
	p_torch_s->led_pwm_handler          = p_torch_s_init->led_pwm_handler;

    // Add service.
    ble_uuid128_t base_uuid = {TORCH_S_UUID_BASE};
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_torch_s->uuid_type);
    VERIFY_SUCCESS(err_code);

    ble_uuid.type = p_torch_s->uuid_type;
    ble_uuid.uuid = TORCH_S_UUID_SERVICE;

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_torch_s->service_handle);
    VERIFY_SUCCESS(err_code); 
		
    err_code = configAndAddChar(p_torch_s, TORCH_S_UUID_LOCK_CHAR           , 1, 1, &p_torch_s->lock_handles);
    if (err_code != NRF_SUCCESS)	return err_code;

    err_code = configAndAddChar(p_torch_s, TORCH_S_UUID_LED_POWER_CHAR      , 5, 1, &p_torch_s->led_power_handles);
    if (err_code != NRF_SUCCESS)	return err_code;

    err_code = configAndAddChar(p_torch_s, TORCH_S_UUID_LED_PWM_CHAR        , 10, 1, &p_torch_s->led_pwm_handles);
    if (err_code != NRF_SUCCESS)	return err_code;

    err_code = configAndAddChar(p_torch_s, TORCH_S_UUID_READ_LDR_CHAR       , 1, 0, &p_torch_s->read_ldr_handles);		//find out th do th, &p_torch_s->read_ldr_handlesis
    if (err_code != NRF_SUCCESS)	return err_code;
	
    return err_code;
}
#endif // NRF_MODULE_ENABLED(BLE_TORCH_S)
