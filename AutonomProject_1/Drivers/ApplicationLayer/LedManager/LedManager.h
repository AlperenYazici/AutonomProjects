#ifndef LED_MANAGER_H
#define LED_MANAGER_H

extern "C" {
#include "stdint.h"
}
#include "IRtos.h"
#include "IBsp.h"
#include "ILedManager.h"


class LedManager : public ILedManager
{		
	IBsp* IBoardSP;
	IRtos* IRealTimeOS;
	
//	OnOffTimes GreenLed = {500 , 500};
	
	public:
	LedManager( IBsp* IBoardSP ,IRtos* IRealTimeOS);
	
	
	void Task();
	
	void LED_ON_Process();

	void LED_OFF_Process();
	
	virtual void SetGreenLedOnTime(uint32_t time_ms);

	virtual void SetGreenLedOffTime(uint32_t time_ms);
	

	
};

#endif
