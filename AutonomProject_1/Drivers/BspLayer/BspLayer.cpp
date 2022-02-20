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
