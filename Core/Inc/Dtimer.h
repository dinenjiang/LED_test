
#ifndef __Dtimer_H__
#define __Dtimer_H__

#include "stdbool.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t Dtimerstart(void);
bool Dtimer_isUp(uint32_t beginTime, uint32_t elapsedTimeMs );




#ifdef __cplusplus
}
#endif
#endif /*__Dtimer_H__ */

