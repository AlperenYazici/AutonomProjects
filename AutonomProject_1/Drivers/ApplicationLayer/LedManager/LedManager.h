#ifndef LED_MANAGER_H
#define LED_MANAGER_H

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

class LedManager
{		
	IBsp* IBoardSP;
	IRtos* IRealTimeOS;
	
	OnOffTimes GreenLed;
	
	public:
	LedManager( IBsp* IBoardSP ,IRtos* IRealTimeOS );
	
	
	void Task();
	
	void LED_ON_Process();

	void LED_OFF_Process();
	
	void SetGreenLedOnTime(uint32_t time_ms);

	void SetGreenLedOffTime(uint32_t time_ms);
	

	
};

#endif
