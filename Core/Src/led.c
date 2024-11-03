#include "main.h"
#include "led.h"
#include "Dtimer.h"
#include "stdio.h"

typedef enum
{
	eLedStep_Init,//0
	eLedStep_forward,//1
	eLedStep_backward,//2

	eLedStep_Num
}eLedStep_t;


typedef struct{
	GPIO_TypeDef *port;
	uint16_t pin;
}sLedPara_t;



sLedPara_t ledpara[]={
	{LED0_GPIO_Port, LED0_Pin},
	{LED1_GPIO_Port, LED1_Pin},
	{LED2_GPIO_Port, LED2_Pin},
	{LED3_GPIO_Port, LED3_Pin},
	{LED4_GPIO_Port, LED4_Pin},
	{LED5_GPIO_Port, LED5_Pin},
	{LED6_GPIO_Port, LED6_Pin},
	{LED7_GPIO_Port, LED7_Pin},

};

const int gLedTotal = 8;
static eLedStep_t gstep = eLedStep_Init;
static int gledNo = 0;
uint32_t beginTime;


void ledCt(int ledNo, bool on)
{
	assert_param(ledNo < gLedTotal);
	HAL_GPIO_WritePin(ledpara[ledNo].port, ledpara[ledNo].pin, (on? GPIO_PIN_RESET: GPIO_PIN_SET));
}

void led_init()
{
  for(int i = 0; i < gLedTotal; i++){
	ledCt(i, false);
  }
  
	//LED on
	gstep = eLedStep_Init;	
	beginTime = Dtimerstart();  	
}	

/*
eLedStep_Init: all led off
eLedStep_forward: (7:off 1:on) -> (1:off 2:on)..(6:off 7:on) 
*/

void led_loop()
{
	if(Dtimer_isUp(beginTime, 1)) {
		beginTime = Dtimerstart();

		switch(gstep){
			case eLedStep_Init:
				printf("%s=>step=%d\n", __func__, gstep);
  			    for(int i = 0; i < gLedTotal; i++){
  				    ledCt(i, false);
  			    }
				gledNo = 0;
				gstep = eLedStep_forward;
				break;
			
			case eLedStep_forward:{				
				//LED on
				int lastledNo = (gledNo == 0)? (gLedTotal - 1): (gledNo - 1);					
				printf("%s=>step=%d, gledNo=%d lastledNo=%d\n", __func__, gstep, gledNo, lastledNo);
				ledCt(gledNo, true);

				//LED off	
				ledCt(lastledNo, false);
				
				gledNo++;					
				if (gledNo >= gLedTotal){
					gledNo = 7;					
					gstep = eLedStep_backward;
				};
			}
				break;
/*eLedStep_backward: (7:on 0:off) -> (6:on 7:off)..(1:on 2:off)->(0:on 1:off)
*/
			case eLedStep_backward:{
				//LED on
				int lastledNo = (gledNo == (gLedTotal - 1))? 0: (gledNo + 1);	
				printf("%s=>step=%d, gledNo=%d lastledNo=%d\n", __func__, gstep, gledNo, lastledNo);
				ledCt(gledNo, true);

				//LED off	
				ledCt(lastledNo, false);
				
				gledNo--;					
				if (gledNo < 0){
					gledNo = 0;					
					gstep = eLedStep_forward;
				}
			}
				break;

			default:
				break;
		}

	}
}

//void led_loop()
//{
//	if(Dtimer_isUp(250)) {
//		Dtimerstart();

//		//LED off
//		ledCt(gstep, false);

//		gstep ++;
			
//		if (gstep >= gLedTotal){
//			gstep = 0;
//		};
//		//LED on
//		ledCt(gstep, true);
//	}
//}

