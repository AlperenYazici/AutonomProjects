#include "RtosLayer.h"

extern osEventFlagsId_t eventUartComHandle;


//void uartEventWait()
//{
//			osEventFlagsWait(eventUartComHandle,1,osFlagsWaitAll,portMAX_DELAY);
//}

void RtosLayer::UartComEventFlagSet()
{
		osEventFlagsSet(eventUartComHandle,1);
}

void RtosLayer::UartComEventFlagWait()
{

}

void RtosLayer::TaskSleepMs(uint32_t time_ms)
{
	osDelay(time_ms);
}
