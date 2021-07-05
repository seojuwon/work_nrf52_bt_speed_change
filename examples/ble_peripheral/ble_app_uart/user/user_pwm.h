/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
  by seo. 2020 06 25
 */
#include <stdio.h>
#include <string.h>
#include "nrf_drv_pwm.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


// This is for tracking PWM instances being used, so we can unintialize only
// the relevant ones when switching from one demo to another.
#define USED_PWM(idx) (1UL << idx)

void demo1_handler(nrf_drv_pwm_evt_type_t event_type);
 
static void demo1(void);
static void demo2(void);
static void demo3(void);
static void demo4(void);
 
void pwm_demo_run(uint8_t mode);


 

/** @} */
