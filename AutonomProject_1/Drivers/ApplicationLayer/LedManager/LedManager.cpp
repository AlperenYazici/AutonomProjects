#include "LedManager.h"

LedManager::LedManager(IBsp* IBoardSP ,IRtos* IRealTimeOS  )
{
	this->IBoardSP = IBoardSP;
	this->IRealTimeOS = IRealTimeOS;

}

void LedManager::Task()
{
	LED_ON_Process();
	LED_OFF_Process();
}

void LedManager::LED_ON_Process()
{
	IBoardSP->LedGreen_On();
  IRealTimeOS->TaskSleepMs(GreenLed.On_Time);
}

void LedManager::LED_OFF_Process()
{
	IBoardSP->LedGreen_Off();
  IRealTimeOS->TaskSleepMs(GreenLed.Off_Time);
}

void LedManager::SetGreenLedOnTime(uint32_t time_ms)
{
	GreenLed.On_Time = time_ms;
}
void LedManager::SetGreenLedOffTime(uint32_t time_ms)
{
	GreenLed.Off_Time = time_ms;
}
