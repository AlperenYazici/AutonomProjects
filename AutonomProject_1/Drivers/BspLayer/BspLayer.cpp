#include "BspLayer.h"

void BspLayer::LedGreen_On()
{
	HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,GPIO_PIN_SET);
}
void BspLayer::LedGreen_Off()
{
	HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,GPIO_PIN_RESET);
}
void BspLayer::Uart_Tx(uint8_t *data , uint16_t len , uint32_t time_out)
{
	HAL_UART_Transmit(&huart2,(uint8_t*)data,len,time_out);
}

void BspLayer::Uart_Rx_ISR(uint8_t *uart_msg,uint16_t len)
{
	HAL_UART_Receive_IT(&huart2,uart_msg,len);
}

void BspLayer::Uart_ReConfig()
{
//	HAL_UART_AbortReceive_IT(&huart2);
	HAL_UART_DeInit(&huart2);
	switch(uart_config_values.BaudRate)
	{
		case BAUD_115200: huart2.Init.BaudRate = 115200; break;
		case BAUD_14400 : huart2.Init.BaudRate = 14400; break;
		case BAUD_19200 : huart2.Init.BaudRate = 19200;	break;
		case BAUD_28800 : huart2.Init.BaudRate = 28800;	break;
		case BAUD_9600  : huart2.Init.BaudRate = 9600; break;
	}
	switch(uart_config_values.WordLen)
	{
		case WordLen_7: huart2.Init.WordLength = UART_WORDLENGTH_7B; break;
		case WordLen_8 : huart2.Init.WordLength = UART_WORDLENGTH_8B; break;
		case WordLen_9 : huart2.Init.WordLength = UART_WORDLENGTH_9B;	break;
	
	}
	
	switch(uart_config_values.StopBit)
	{
		case StopBit_0_5: huart2.Init.StopBits = UART_STOPBITS_0_5; break;
		case StopBit_1 : huart2.Init.StopBits = UART_STOPBITS_1; break;
		case StopBit_1_5 : huart2.Init.StopBits = UART_STOPBITS_1_5;	break;
		case StopBit_2 : huart2.Init.StopBits = UART_STOPBITS_2;	break;
	}
	
	if (HAL_UART_Init(&huart2) != HAL_OK) {
    Error_Handler();
	}
	
}

