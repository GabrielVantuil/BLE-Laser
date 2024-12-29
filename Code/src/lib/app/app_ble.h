#ifndef APP_BLE_H__
#define APP_BLE_H__

#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "ble.h"
#include "ble_err.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_conn_params.h"
#include "app_timer.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "ble_torch_s.h"

#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "parameters.h"
#include "handles.h"

#define DEAD_BEEF                       0xDEADBEEF                              /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */

BLE_TORCH_S_DEF(m_torch_s);                                                  		/**< Torch Service instance. */
NRF_BLE_GATT_DEF(m_gatt);                                                       /**< GATT module instance. */
NRF_BLE_QWR_DEF(m_qwr);                                                         /**< Context for the Queued Write module.*/

extern uint16_t m_conn_handle;

void gap_params_init(void);
void gatt_init(void);
void advertising_init(void);
void nrf_qwr_error_handler(uint32_t nrf_error);
void services_init(void);
void on_conn_params_evt(ble_conn_params_evt_t * p_evt);
void conn_params_init(void);
void advertising_start(void);
void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context);
void ble_stack_init(void);

#endif
