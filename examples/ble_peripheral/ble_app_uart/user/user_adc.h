#ifndef APP_TEMPERATURE_H
#define APP_TEMPERATURE_H

#define APP_ADC_TEMP_CHECK_TIMES					180

#define APP_ADC_TIMER_PRESCALER					0
#define APP_ADC_TIMER_INTERVAL					APP_TIMER_TICKS(1000, APP_ADC_TIMER_PRESCALER)

#define APP_ADC_180S_TIMER_PRESCALER				0
#define APP_ADC_180S_TIMER_INTERVAL				APP_TIMER_TICKS(1000, APP_ADC_180S_TIMER_PRESCALER)
#define TRUE											true
#define FALSE										false

#if 0
typedef struct
{
	float					temp;
	uint8_t				Data[2];
	uint8_t				calValue[2];
	uint16_t				calTemp;
	bool					calibrated;
	bool					onlyOne;
	float					temp_calc;
	float					temp_calc2;
	float					volt;
	float					vdd;
	float					adc_temp_last;
	float					displayTemp;

	float					fcalTemp;

	float					displayAvgTemp;
	bool					enabled;
	bool					adcStop;
	uint16_t				adcReadCount;

}appTEMP;
#endif
void appADCInit(void);
void appADCUinit(void);
void appADCRead(void);
void appADCCalibrate(void);
void appADCTimerInit(void);
void appADCTimerStart(void);
void appADCTimerStop(void);
void appADCStart(void);
void appADCStop(void);

void appADC180sTimerInit(void);
void appADC180sTimerStart(void);
void appADC180sTimerStop(void);

#endif	/* APP_TEMPERATURE_H */

