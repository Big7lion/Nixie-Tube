#ifndef __DS18B20_H
#define __DS18B20_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stdlib.h"
#include "string.h"
#include "delay.h"

#include "FreeRTOS.h"
#include "task.h"

/*端口定义*/
#define PORT_DQ		TEMP_DQ_GPIO_Port                  
#define PIN_DQ		TEMP_DQ_Pin
#define DQ_0()		(PORT_DQ->BRR = PIN_DQ)
#define DQ_1()		(PORT_DQ->BSRR = PIN_DQ)
/* 判断DQ输入是否为低 */
#define DQ_IS_LOW()	((PORT_DQ->IDR & PIN_DQ) == 0)

void bsp_18B20_Init(void);
int16_t DS18B20_ReadTempReg(void);

#endif
