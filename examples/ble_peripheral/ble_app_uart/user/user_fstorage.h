

#include <stdint.h>
#include <stdbool.h>
#include "nrf_fstorage.h"
 #ifdef SOFTDEVICE_PRESENT
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_fstorage_sd.h"
#else
#include "nrf_drv_clock.h"
#include "nrf_fstorage_nvmc.h"
#endif
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_drv_timer.h"
//#include "nrf_drv_config.h"
#include "app_util_platform.h"
#include "nrf.h"


#include <string.h>
void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt);
void nvm_control(void);
void nvm_control_2(void); //for test
void nvm_erase(uint8_t page_sel); //1 ¶Ç´Â 2 
void nvm_time_read(void);
void nvm_total_save(void);
