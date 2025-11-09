#ifndef PARAMETERS_H__
#define PARAMETERS_H__
#include "board_config.h"

#define DEVICE_NAME                     "GV Laser"                   			/**< Name of device. Will be included in the advertising data. */

#define APP_BLE_OBSERVER_PRIO           3                                		/**< Application's BLE observer priority. You shouldn't need to modify this value. */
#define APP_BLE_CONN_CFG_TAG            1                                		/**< A tag identifying the SoftDevice BLE configuration. */

#define APP_ADV_INTERVAL                MSEC_TO_UNITS(100, UNIT_0_625_MS)		/**< The advertising interval (in units of 0.625 ms; this value corresponds to 40 ms). */
#define APP_ADV_DURATION                0								 		/**< The advertising time-out (in units of 10ms). When set to 0, we will never time out. */

#define MIN_CONN_INTERVAL               MSEC_TO_UNITS(20, UNIT_1_25_MS)  		/**< Minimum acceptable connection interval */
#define MAX_CONN_INTERVAL               MSEC_TO_UNITS(100, UNIT_1_25_MS)  		/**< Maximum acceptable connection interval */
#define SLAVE_LATENCY                   0                                		/**< Slave latency. */
#define CONN_SUP_TIMEOUT                MSEC_TO_UNITS(500, UNIT_10_MS)  		/**< Connection supervisory time-out (recommended 4x MAX_CONN_INTERVAL). */	

#define FIRST_CONN_PARAMS_UPDATE_DELAY  APP_TIMER_TICKS(200)              		/**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (15 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(500)              		/**< Time between each call to sd_ble_gap_conn_param_update after the first call (5 seconds). */
#define MAX_CONN_PARAMS_UPDATE_COUNT    3                                 		/**< Number of attempts before giving up the connection parameter negotiation. */

#endif
