#ifndef RTOS_LAYER_H
#define RTOS_LAYER_H

#include "IRtos.h"

#include "cmsis_os.h"

extern osEventFlagsId_t eventUartComHandle;

class RtosLayer : public IRtos
{
public:
	virtual void UartComEventFlagSet();
	virtual void UartComEventFlagWait();

	virtual void TaskSleepMs(uint32_t time_ms);
	
};



#endif

