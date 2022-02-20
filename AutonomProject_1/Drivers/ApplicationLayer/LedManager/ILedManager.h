#ifndef ILED_MANAGER_H
#define ILED_MANAGER_H

extern "C" {
#include "stdint.h"
}
#include "IRtos.h"
#include "IBsp.h"

typedef struct OnOffTimes
{
	uint32_t On_Time;
	uint32_t Off_Time;

}OnOffTimes;

class ILedManager
{		
	public:
		
	OnOffTimes GreenLed	= {500 , 500};


	virtual void SetGreenLedOnTime(uint32_t time_ms) = 0;

	virtual void SetGreenLedOffTime(uint32_t time_ms) = 0;
	

	
};

#endif
