/*
 * main.c
 *
 *  Created on: Dec 03, 2021
 *      Author: leona
 */

#include <string.h>
#include "stm32f4xx_hal.h"
#include "main.h"
#include "daly-bms-uart.h"

#define TRUE 1
#define FALSE 0

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);

UART_HandleTypeDef huart2;

int main(void)
{
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	Daly_BMS_UART_Init();

	while(1)
	{
		float volts = 0;
		float amps = 0;
		float percentage = 0;

		getPackMeasurements(&volts, &amps, &percentage);

		float maxCellVoltage = 0;
		float minCellVoltage = 0;
		uint8_t maxCellNumber = 0;
		uint8_t minCellNumber = 0;

		getMinMaxCellVoltage(&minCellVoltage, &minCellNumber, &maxCellVoltage, &maxCellNumber);
	}

	return 0;
}

void SystemClockConfig(void)
{
	/* usar essa função quando forem necessárias configurações especiais no clock*/

}

void UART2_Init(void) /* Inicialização de alto nível do periférico (parâmetros) */
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_handler();
	}
}

void Error_handler(void)
{
	while(1);
}

