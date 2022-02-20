#ifndef BSP_LAYER_H
#define BSP_LAYER_H

#include "IBsp.h"

class BspLayer: public IBsp
{
	virtual void LedGreen_On();
	virtual void LedGreen_Off();
	virtual void Uart_Tx(uint8_t *data , uint16_t len , uint32_t time_out);
};

#endif
