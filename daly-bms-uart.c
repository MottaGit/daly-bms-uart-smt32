/*
 * daly-bms-uart.c
 *
 *  Created on: 17 de dez de 2021
 *      Author: leona
 */


#include <string.h>
#include "stm32f4xx_hal.h"
#include "main.h"
#include "daly-bms-uart.h"

extern UART_HandleTypeDef huart2;

int Daly_BMS_UART_Init()
{
	my_txBuffer[0] = 0xA5;			// Start byte
	my_txBuffer[1] = 0x80; 			// Host address
	my_txBuffer[3] = 0x08; 			// Data Length

    for (int i = 4; i < 12; i++)	// Bytes 5-11 com 0x00
    {
        my_txBuffer[i] = 0x00;
    }

    return 1;
}

void sendCommand(COMMAND  cmID)
{
	my_txBuffer[2] = cmID;
	uint8_t checksum = 0x2D + cmID;
	my_txBuffer[12] = checksum;

	/* enviar os bytes stm32 HAL_TRANSMIT */
	HAL_UART_Transmit(&huart2, my_txBuffer, 13, HAL_TIMEOUT);
}

void receiveBytes()
{
	// Limpa o buffer de rx
	memset(my_rxBuffer, 0, XFER_BUFFER_LENGTH);

	/* le os bytes serial stm32 HAL_RECEIVE */
	HAL_UART_Receive(&huart2, my_rxBuffer, 13, HAL_TIMEOUT);
}

void getPackMeasurements(float *_voltage, float *_current, float *_SOC)
{
	sendCommand(VOUT_IOUT_SOC);

	receiveBytes();

	// Puxa os valores relevantes da tensão para fora do buffer
	*_voltage = (float)((my_rxBuffer[4] << 8) | my_rxBuffer[5]) / 10;

	// A medição atual é fornecida com um deslocamento de 30000 uni
	*_current = (float)(((my_rxBuffer[8] << 8) | my_rxBuffer[9]) - 30000) / 10;

	// Puxa os valores relevantes da carga para fora do buffer
	*_SOC = (float)((my_rxBuffer[10] << 8) | my_rxBuffer[11]) / 10;
}


void getMinMaxCellVoltage(float *_minCellV, uint8_t *_minCellVNum, float *_maxCellV, uint8_t *_maxCellVNum)
{
	sendCommand(MIN_MAX_CELL_VOLTAGE);

	receiveBytes();

	*_maxCellV = (float)((my_rxBuffer[4] << 8) | my_rxBuffer[5]) / 1000; // Dado em mV, convete para V
	*_maxCellVNum = my_rxBuffer[6];
	*_minCellV = (float)((my_rxBuffer[7] << 8) | my_rxBuffer[8]) / 1000; // Dado em mV, convete para V
	*_minCellVNum = my_rxBuffer[9];

}

