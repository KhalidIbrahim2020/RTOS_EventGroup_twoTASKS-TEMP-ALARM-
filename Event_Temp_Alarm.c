
#include "FreeRTOS.h"#include "task.h"#include "queue.h"#include "semphr.h"#include "event_groups.h"#include "board.h"#include "ADC.h"#include "lcd.h"void T_Temp(void* pvData);void T_Alarm(void* pvData);void system_init(void);#define E_Alarm (1<<0)EventGroupHandle_t   egEvent;EventBits_t          ebValues;int main(void){	system_init();	egEvent=xEventGroupCreate();	xTaskCreate(T_Temp,"T_Temp",200,NULL,1,NULL);	xTaskCreate(T_Alarm,"T_Alarm",200,NULL,2,NULL);	vTaskStartScheduler();}void T_Temp(void* pvData){	INT8U TEMPCalculate=0;			while(1){		TEMPCalculate=ADC_Read(0)*150UL/1023;//0 -> 150			LCD_DispStrXY(1,1,"TEMPCalculate");			LCD_DispIntXY(2,1,TEMPCalculate);		/*CALCULATION C*/		if ((TEMPCalculate)>=100)		{						/* fire */			xEventGroupSetBits(egEvent,E_Alarm);		}		else if((TEMPCalculate)<100)		{					xEventGroupClearBits(egEvent,E_Alarm);		}	}}void T_Alarm(void* pvData){	while(1){		ebValues = xEventGroupWaitBits(egEvent,		(E_Alarm),		0,		0,		portMAX_DELAY);		if(ebValues&E_Alarm)		{			Led_Toggle();			BUZ_Toggle();			vTaskDelay(500);			Led_Toggle();			BUZ_Toggle();			vTaskDelay(500);
		}
		else {
			
		}
	}
	
}




void system_init(void){	Led_Init();	ADC_INIT();	BUZ_Init();    LCD_Init(); }