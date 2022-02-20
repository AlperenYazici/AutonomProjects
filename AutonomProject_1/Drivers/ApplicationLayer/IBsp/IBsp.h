#ifndef IBSP_H
#define IBSP_H

#include "stdint.h"

typedef enum uart_baudrate_types
{
	// ...
	BAUD_9600,
	BAUD_14400,
	BAUD_19200,
	BAUD_28800,
	// ...
	BAUD_115200
	// ...
}uart_baudrate_types;

typedef enum uart_wordlen_types
{
	WordLen_7,
	WordLen_8,
	WordLen_9
}uart_wordlen_types;

typedef enum uart_stopbit_types
{
	StopBit_0_5,
	StopBit_1,
	StopBit_1_5,
	StopBit_2
	
}uart_stopbit_types;

typedef struct uart_com_configs{
	uart_baudrate_types BaudRate;
	uart_wordlen_types WordLen;
	uart_stopbit_types StopBit;
}uart_com_configs;

class IBsp
{

	public:
	uart_com_configs uart_config_values = {BAUD_115200 , WordLen_8 , StopBit_1};
	virtual void LedGreen_On() = 0;
	virtual void LedGreen_Off() = 0;
	virtual void Uart_Tx(uint8_t *data , uint16_t len , uint32_t time_out) = 0;
	virtual void Uart_Rx_ISR(uint8_t *uart_msg,uint16_t len) = 0;
	virtual void Uart_ReConfig() = 0;
};

#endif
