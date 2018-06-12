/*
 * debug_funcs.c
 *
 *  Created on: May 21, 2018
 *      Author: Bruno
 */


#include "stm32f4xx_hal.h"
#include "cc112x_spi.h"
#include "debug_funcs.h"
#include "ccconfig.h"
#include <stdint.h>
#include "main.h"

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

IWDG_HandleTypeDef hiwdg;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi2_rx;

UART_HandleTypeDef huart5;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_uart5_tx;

void reg_wr_rd_test(){

	unsigned char message[] = "yee boiii\n";
	uint8_t spirx;

	HAL_UART_Transmit(&huart3,message, sizeof(message), 100);
	HAL_Delay(1000);
	cc_tx_wr_reg(0x002E,0x13);
	cc_rx_wr_reg(0x002E,0x21);

	cc_tx_rd_reg(0x002E,&spirx);
	sprintf(message,"boi %d",(unsigned int)spirx);
	HAL_UART_Transmit(&huart3, message, sizeof(message), 100);
	HAL_Delay(1000);

	cc_rx_rd_reg(0x002E,&spirx);
	sprintf(message,"boii %d",(unsigned int)spirx);
	HAL_UART_Transmit(&huart3, message, sizeof(message), 100);
	HAL_Delay(1000);

	if(spirx==0x21){
		HAL_UART_Transmit(&huart3, "yas", sizeof("yas"), 100);
	}
	else{
		HAL_UART_Transmit(&huart3, "nah", sizeof("nah"), 100);
	}

	return;
}

void rx_test(){
		unsigned char message[] = "yee boiii\n";
		uint8_t spirx;

	  HAL_UART_Transmit(&huart3,"LOOP START\n", sizeof("LOOP START\n"), 100);
	  sprintf(message,"byte:%d\n  ",cc_rx_cmd(SRX)&0xF0);
	  HAL_UART_Transmit(&huart3,message, sizeof(message), 100);
	  sprintf(message,"byte:%d\n  ",cc_rx_cmd(SNOP)&0xF0);
	  HAL_UART_Transmit(&huart3,message, sizeof(message), 100);
	  sprintf(message,"byte:%d\n  ",MRX&0xF0);
	  HAL_UART_Transmit(&huart3,message, sizeof(message), 100);
	  //  Serial.print("Waiting for packet");
	  cc_rx_cmd(SNOP);
	  while((cc_rx_cmd(SNOP)&0xF0)==(MRX&0xF0)){
		  cc_rx_rd_reg(NUM_RXBYTES,&spirx);
		  sprintf(message,"nrx:%d\n   ",spirx);
		  HAL_UART_Transmit(&huart3,message, sizeof(message), 100);
		  HAL_UART_Transmit(&huart3,"\r", sizeof("\r"), 100);
//		  cc_rx_rd_reg(FIFOR,&spirx);
//		  sprintf(message,"byterx:%d\n",(unsigned int)spirx);
//		  HAL_UART_Transmit(&huart3,message, sizeof(message), 100);
//		  HAL_UART_Transmit(&huart3,"\r", sizeof("\r"), 100);
			  }
	  sprintf(message,"byte:%d\n  ",cc_rx_cmd(SNOP)&0xF0);
	  HAL_UART_Transmit(&huart3,message, sizeof(message), 100);
	  cc_rx_cmd(SFRX);
	  HAL_Delay(10000);
	  return;
}
