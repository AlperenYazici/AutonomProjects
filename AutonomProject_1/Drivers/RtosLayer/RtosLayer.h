#ifndef RTOS_LAYER_H
#define RTOS_LAYER_H

#include "IRtos.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "main.h"
#include "cmsis_os.h"


class RtosLayer : public IRtos
{
public:
	virtual void UartComEventFlagSet();
	virtual void UartComEventFlagWait();
	virtual void TaskSleepMs(uint32_t time_ms);
	
};

#endif

