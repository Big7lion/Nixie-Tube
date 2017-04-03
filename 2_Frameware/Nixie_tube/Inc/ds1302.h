#ifndef DS1302_H
#define DS1302_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stdlib.h"
#include "string.h"
#include "delay.h"

#include "FreeRTOS.h"
#include "task.h"

#define DS1302_CLK_H()	(TIME_SCK_GPIO_Port->BSRR=TIME_SCK_Pin)
#define DS1302_CLK_L()	(TIME_SCK_GPIO_Port->BRR=TIME_SCK_Pin)

#define DS1302_RST_H()	(TIME_CE_GPIO_Port->BSRR=TIME_CE_Pin)
#define DS1302_RST_L()	(TIME_CE_GPIO_Port->BRR=TIME_CE_Pin)

#define DS1302_OUT_H()	(TIME_IO_GPIO_Port->BSRR=TIME_IO_Pin)
#define DS1302_OUT_L()	(TIME_IO_GPIO_Port->BRR=TIME_IO_Pin)
											
#define DS1302_IN_X		(TIME_IO_GPIO_Port->IDR&TIME_IO_Pin)

#define Time_24_Hour	0x00	//24时制控制	
#define Time_Start		0x00	//开始走时

#define DS1302_SECOND	0x80	//DS1302各寄存器操作命令定义
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84
#define DS1302_DAY		0x86
#define DS1302_MONTH	0x88
#define DS1302_WEEK		0x8A
#define DS1302_YEAR		0x8C
#define DS1302_WRITE	0x8E
#define DS1302_POWER	0x90

void bsp_1302_Init(void);
void ReadDS1302Clock(uint8_t *p);
void WriteDS1302Clock(uint8_t *p);
void ReadDSRam(uint8_t *p,uint8_t add,uint8_t cnt);
void WriteDSRam(uint8_t *p,uint8_t add,uint8_t cnt);

#endif
