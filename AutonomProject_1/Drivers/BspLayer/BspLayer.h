#ifndef BSP_LAYER_H
#define BSP_LAYER_H

#include "IBsp.h"
#include "main.h"
extern UART_HandleTypeDef huart2;

class BspLayer: public IBsp
{
	virtual void LedGreen_On() ;
	virtual void LedGreen_Off() ;
	virtual void Uart_Tx(uint8_t *data , uint16_t len , uint32_t time_out);
	virtual void Uart_Rx_ISR(uint8_t *uart_msg,uint16_t len);
	virtual void Uart_ReConfig();
};

#endif
