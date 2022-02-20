#ifndef IRTOS_H
#define IRTOS_H

#include "stdint.h"

class IRtos
{
	public:
	virtual void EventFlagSet() = 0;
	virtual void EventFlagWait() = 0;
	virtual void TaskSleepMs(uint32_t time_ms) = 0;
	
};

#endif
