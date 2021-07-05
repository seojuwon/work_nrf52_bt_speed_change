#include <stdint.h>
#include <string.h>

#include "bsp.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_soc.h"
#include "nrf_drv_saadc.h"
#include "app_timer.h"

//#include "app_private.h"
#include "user_adc.h"

APP_TIMER_DEF(ADCTimerId);


#define ADC_REF_VOLTAGE_IN_MILLIVOLTS       600                                          /**< Reference voltage (in milli volts) used by ADC while doing conversion. */
#define ADC_PRE_SCALING_COMPENSATION        6                                            /**< The ADC is configured to use VDD with 1/3 prescaling as input. And hence the result of conversion is to be multiplied by 3 to get the actual value of the battery voltage.*/
#define DIODE_FWD_VOLT_DROP_MILLIVOLTS      270                                          /**< Typical forward voltage drop of the diode (Part no: SD103ATW-7-F) that is connected in series with the voltage supply. This is the voltage drop when the forward current is 1mA. Source: Data sheet of 'SURFACE MOUNT SCHOTTKY BARRIER DIODE ARRAY' available at www.diodes.com. */
#define ADC_RES_10BIT                       1024                                         /**< Maximum digital value for 10-bit ADC conversion. */

#define ADC_RESULT_IN_MILLI_VOLTS(ADC_VALUE)		((((ADC_VALUE) * ADC_REF_VOLTAGE_IN_MILLIVOLTS) / ADC_RES_10BIT) * ADC_PRE_SCALING_COMPENSATION)

static nrf_saadc_value_t adcBuf[2];
//static bool forceMode = FALSE;
//bool timerStartFlag = TRUE;

//static uint16_t adcReadCount = 0;
//static bool adcReadFlag = FALSE;
//static bool adcCheckFlag = FALSE;
 
uint16_t calTemp = 0;
float fcalTemp = 0.0;

uint16_t		adc_temp_buf[10]; //V1.5 ADC 10번  수정
uint8_t			adc_temp_buf_cnt; //0~16 
//uint16_t		adc_temp_last; //last calc data
uint16_t		adc_temp_max;
uint16_t		adc_temp_min;
uint16_t		calc_buf[10]; //V1.5 ADC 10번  수정

bool readFlag = TRUE;

void saadc_event_handler(nrf_drv_saadc_evt_t const * p_event)
{
	uint32_t err_code;
//	nrf_saadc_value_t adcResult;
	uint16_t temp_raw, temp_vdd;
	
		if(p_event->type == NRF_DRV_SAADC_EVT_DONE)
		{		
			temp_raw = p_event->data.done.p_buffer[0];
			temp_vdd = p_event->data.done.p_buffer[1];
//				timerStartFlag = FALSE;
#if 0
//					nrf_drv_saadc_uninit();

					NRF_SAADC->INTENCLR = (SAADC_INTENCLR_END_Clear << SAADC_INTENCLR_END_Pos);
					NVIC_ClearPendingIRQ(SAADC_IRQn);
#endif

			}

			printf(" >>adc : %x  %x \r\n", temp_raw, temp_vdd);
			//printf((" >>adc_temp_buf_cnt:%d\r\n", adc_temp_buf_cnt));
			//APP_DEBUG(("[ADC %d %d %d %d %d \r\n",theAppTask.bat.battery_buf[0],theAppTask.bat.battery_buf[1],theAppTask.bat.battery_buf[2],theAppTask.bat.battery_buf[3],theAppTask.bat.battery_buf[4] ));
			//////////////////////////////////////////////////////////
			err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, 2);
		
			APP_ERROR_CHECK(err_code);
	//readFlag = TRUE;
}


void appADCInit(void)
{
	//APP_DEBUG(("[ADC_INIT]\r\n"));
	
	ret_code_t err_code = nrf_drv_saadc_init(NULL, saadc_event_handler);
	APP_ERROR_CHECK(err_code);
	
	nrf_saadc_channel_config_t config = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN1);

	err_code = nrf_drv_saadc_channel_init(0, &config);
	APP_ERROR_CHECK(err_code);

	nrf_saadc_channel_config_t config2 = NRF_DRV_SAADC_VDD_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_VDD); // VDD

	err_code = nrf_drv_saadc_channel_init(1, &config2); //use - ch 1
	APP_ERROR_CHECK(err_code);

	err_code = nrf_drv_saadc_buffer_convert(&adcBuf[0], 2);
	APP_ERROR_CHECK(err_code);
}

void appADCUinit(void)
{
	//APP_DEBUG(("[ADC_UN INIT]\r\n"));
	
	nrf_drv_saadc_uninit();

	NRF_SAADC->INTENCLR = (SAADC_INTENCLR_END_Clear << SAADC_INTENCLR_END_Pos);
	NVIC_ClearPendingIRQ(SAADC_IRQn);
}

void appADCStart(void)
{
		appADCInit();
		appADCTimerStart();
}

void appADCStop(void)
{
	appADCUinit();
}

void appADCRead(void)
{
	
	nrf_drv_saadc_sample();
}

static void appADCTimerHandler(void *pContext)
{
	appADCTimerStop();
	
	if(readFlag)
	{
		readFlag = FALSE;
		appADCRead();
	}
		appADCTimerStart();
	
}

void appADCTimerInit(void)
{
	uint32_t err_code;
	err_code = app_timer_create(&ADCTimerId, APP_TIMER_MODE_SINGLE_SHOT, appADCTimerHandler);
	APP_ERROR_CHECK(err_code);
}

void appADCTimerStart(void)
{
	uint32_t err_code;
//				   app_timer_start(m_bsp_leds_tmr_seo, APP_TIMER_TICKS(5000), NULL);  //ms
	err_code = app_timer_start(ADCTimerId,         APP_TIMER_TICKS(5000), NULL); //5sec
	APP_ERROR_CHECK(err_code);
}

void appADCTimerStop(void)
{
	uint32_t err_code;

	err_code = app_timer_stop(ADCTimerId);
	APP_ERROR_CHECK(err_code);
}
 



