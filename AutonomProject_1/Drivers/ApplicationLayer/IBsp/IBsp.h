#ifndef IBSP_H
#define IBSP_H

#include "stdint.h"

class IBsp
{
	public:
	virtual void LedGreen_On() = 0;
	virtual void LedGreen_Off() = 0;
	virtual void Uart_Tx(uint8_t *data , uint16_t len , uint32_t time_out) = 0;
};

#endif
