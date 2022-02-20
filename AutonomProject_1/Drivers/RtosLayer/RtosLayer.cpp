#include "RtosLayer.h"



void RtosLayer::UartComEventFlagSet()
{
	osEventFlagsSet(eventUartComHandle,1);
}

void RtosLayer::UartComEventFlagWait()
{
 osEventFlagsWait(eventUartComHandle,1,osFlagsWaitAll,portMAX_DELAY);
}

void RtosLayer::TaskSleepMs(uint32_t time_ms)
{
	osDelay(time_ms);
}
