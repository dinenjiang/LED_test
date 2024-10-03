#include "main.h"
#include "Dtimer.h"

//uint32_t beginTime;

uint32_t Dtimerstart()
{
	
	return HAL_GetTick(); 
}

/*
elapsedTimeMs: 經過時間 (單位 毫秒)

*/

bool Dtimer_isUp(uint32_t beginTime, uint32_t elapsedTimeMs )
{
	uint32_t presentTime = HAL_GetTick(); 
	uint32_t passedTime = presentTime - beginTime;
	if (passedTime >= elapsedTimeMs){
		return true;
	}
	else{
		return false;
	}
}

