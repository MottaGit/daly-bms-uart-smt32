/*
 * daly-bms-uart.h
 *
 *  Created on: 17 de dez de 2021
 *      Author: leona
 */

#ifndef INC_DALY_BMS_UART_H_
#define INC_DALY_BMS_UART_H_

#define XFER_BUFFER_LENGTH 13

#include <string.h>
#include "stm32f4xx_hal.h"
#include "main.h"

extern UART_HandleTypeDef huart2;

uint8_t my_txBuffer[13];	// Buffer usado para transmitir dados pro BMS
uint8_t my_rxBuffer[13];	// Buffer preenchido com dados do BMS


/* Estes nomes de comando recebem os endereços referentes ao Data ID de cada menssagem */
typedef enum
{
	VOUT_IOUT_SOC = 0x90,
	MIN_MAX_CELL_VOLTAGE = 0x91,
	MIN_MAX_TEMPERATURE = 0x92,
	DISCHARGE_CHARGE_MOS_STATUS = 0x93,
	STATUS_INFO = 0x94,
	CELL_VOLTAGES = 0x95,
	FAILURE_CODES = 0x98
} COMMAND;

/* Pré-carrega o buffer de transmissão com bytes, de acordo com o manual */
int Daly_BMS_UART_Init(void);


/* Recebe como parâmetro o Comando ID pro BMS e configura os bytes 2 (ID) e 12 (checksum)
 * Envia os bytes para o BMS, envia o my_txBuffer[]
 * */
void sendCommand(COMMAND  cmID);

/* Recebe os bytes do BMS, recebe no my_rxBuffer[] */
void receiveBytes();

/* Obtém medições de tensão, corrente e carga do BMS.
 * Devem ser passados os endereços de memória das variaveis desejadas.
 * _voltage - retorna a tensão em volts [V]
 * _current - retorna a corrente em amperes [A]
 * _SOC - retorna a carga em porcentagem [%]
 *  */
void getPackMeasurements(float *_voltage, float *_current, float *_SOC);

/* Retorna a tensão de célula individual mais alta e mais baixa, e qual célula é a mais alta / mais baixa.
 * Devem ser passados os endereços de memória das variaveis desejadas.
 * _minCellV/_maxCellV - retorna menor e maior tensão
 * _minCellVNum/_maxCellVNum - retorna qual a célula de tensão minima e maior
 */
void getMinMaxCellVoltage(float *_minCellV, uint8_t *_minCellVNum, float *_maxCellV, uint8_t *_maxCellVNum);

#endif /* INC_DALY_BMS_UART_H_ */
