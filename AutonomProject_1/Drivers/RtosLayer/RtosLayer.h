#ifndef RTOS_LAYER_H
#define RTOS_LAYER_H

#include "IRtos.h"

class RtosLayer : public IRtos
{
public:
	virtual void EventFlagSet();
	virtual void EventFlagWait();
	virtual void TaskSleepMs(uint32_t time_ms);
	
};

#endif

