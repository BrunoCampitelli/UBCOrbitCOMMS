/*
 * ccconfig.c
 *
 *  Created on: May 21, 2018
 *      Author: Bruno
 */
#include "ccconfig.h"
#include "cc112x_spi.h"

int cc_rx_Start(void){
	uint8_t rx;
	uint16_t i;

  cc_rx_cmd(SRES);

//force idle
  cc_rx_cmd(SIDLE);
  cc_rx_cmd(SNOP);
  while((cc_rx_cmd(SNOP)&0b111000)==(MCAL&0xF0));

//register setup
  rx_set_reg();

//register write check
  cc_rx_rd_reg(FREQ2,&rx);
  for (i=0;Registers_rx[i].addr!=FREQ2;i++);
  if (rx!=Registers_rx[i].data) return -1;

  cc_rx_cmd(SNOP);
  while((cc_rx_cmd(SNOP)&0b111000)==(MCAL&0xF0));

  return 0;
}

int cc_tx_Start(void){
	uint8_t tx;
	uint16_t i;

  cc_tx_cmd(SRES);

//force idle
  cc_tx_cmd(SIDLE);
  cc_tx_cmd(SNOP);
  while((cc_tx_cmd(SNOP)&0b111000)==(MCAL&0xF0));

//register setup
  tx_set_reg();

//register write check
  cc_tx_rd_reg(FREQ2,&tx);
  for (i=0;Registers_tx[i].addr!=FREQ2;i++);
  if (tx!=Registers_tx[i].data) return -1;

  cc_tx_cmd(SNOP);
  while((cc_tx_cmd(SNOP)&0b111000)==(MCAL&0xF0));

  return 0;
}

void tx_set_reg(){

	  for(uint16_t i = 0;
	        i < (sizeof(Registers_tx)/sizeof(registerSetting_t)); i++) {
		  cc_tx_wr_reg(Registers_tx[i].addr, Registers_tx[i].data);
	    }

	  return;
}

void rx_set_reg(){

	  for(uint16_t i = 0;
	        i < (sizeof(Registers_rx)/sizeof(registerSetting_t)); i++) {
		  cc_rx_wr_reg(Registers_rx[i].addr, Registers_rx[i].data);
	    }

	  return;
}
