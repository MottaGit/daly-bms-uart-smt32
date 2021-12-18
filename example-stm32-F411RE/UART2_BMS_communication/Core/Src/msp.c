/*
 * msp.c
 *
 *  Created on: Dec 03, 2021
 *      Author: leona
 */


#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
	/* Inicialização de baixo lvl do processador */

	/* 1. Configurar o agrupamento de prioridades do processador. */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* 2. Ativar as exceções do sistema */
	SCB -> SHCSR |= 0x7 << 16; //exceções de falha de uso, falha de memória e falha de barramento

	/* 3. Configurar a prioridade das exceções do sistema. */
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;

	/* Inicialização de baixo lvl do periférico UART2 */

	/* 1. habilitar o clock do periférico USART2 e GPIOA*/
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* 2. configurar pinos */
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2;	//UART2_TX
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin = GPIO_PIN_3;	//UART2_RX
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	/* 3. habilitar IRQ e definir prioridade (configuração NVIC)*/
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);

}
