#ifndef __HV_DISPLAY_H
#define __HV_DISPLAY_H

#include "stm32f1xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "delay.h"

/*续行符后不可注释*/
#define LE_Enable(n) (n?HAL_GPIO_WritePin(HVLE_GPIO_Port,HVLE_Pin,GPIO_PIN_RESET):\
											HAL_GPIO_WritePin(HVLE_GPIO_Port,HVLE_Pin,GPIO_PIN_SET))								//锁存使能
#define HVCLK_Write(n) 	(n?HAL_GPIO_WritePin(HVCLK_GPIO_Port,HVCLK_Pin,GPIO_PIN_SET):\
											HAL_GPIO_WritePin(HVCLK_GPIO_Port,HVCLK_Pin,GPIO_PIN_RESET))						//时钟上升下降
#define HVPOL_Enable(n)  (n?HAL_GPIO_WritePin(HVPOL_GPIO_Port,HVPOL_Pin,GPIO_PIN_RESET):\
											HAL_GPIO_WritePin(HVPOL_GPIO_Port,HVPOL_Pin,GPIO_PIN_SET))							//极性反转使能
#define HVDIN1_Write(n) (n?HAL_GPIO_WritePin(HVDIN1_GPIO_Port,HVDIN1_Pin,GPIO_PIN_SET):\
											HAL_GPIO_WritePin(HVDIN1_GPIO_Port,HVDIN1_Pin,GPIO_PIN_RESET))					//HVDIN1		 
#define HVDIN2_Write(n) (n?HAL_GPIO_WritePin(HVDIN2_GPIO_Port,HVDIN2_Pin,GPIO_PIN_SET):\
											HAL_GPIO_WritePin(HVDIN2_GPIO_Port,HVDIN2_Pin,GPIO_PIN_RESET))					//     :
#define HVDIN3_Write(n) (n?HAL_GPIO_WritePin(HVDIN3_GPIO_Port,HVDIN3_Pin,GPIO_PIN_SET):\
											HAL_GPIO_WritePin(HVDIN3_GPIO_Port,HVDIN3_Pin,GPIO_PIN_RESET))					//		 :
#define HVDIN4_Write(n) (n?HAL_GPIO_WritePin(HVDIN4_GPIO_Port,HVDIN4_Pin,GPIO_PIN_SET):\
											HAL_GPIO_WritePin(HVDIN4_GPIO_Port,HVDIN4_Pin,GPIO_PIN_RESET))					//HVDIN4写数据
#define BLINK_1_Write(n) (n?HAL_GPIO_WritePin(BLINK_1_GPIO_Port,BLINK_1_Pin,GPIO_PIN_SET):\
											HAL_GPIO_WritePin(BLINK_1_GPIO_Port,BLINK_1_Pin,GPIO_PIN_RESET))				//BLINK1        
#define BLINK_2_Write(n) (n?HAL_GPIO_WritePin(BLINK_2_GPIO_Port,BLINK_2_Pin,GPIO_PIN_SET):\
											HAL_GPIO_WritePin(BLINK_2_GPIO_Port,BLINK_2_Pin,GPIO_PIN_RESET))        //     :
#define BLINK_3_Write(n) (n?HAL_GPIO_WritePin(BLINK_3_GPIO_Port,BLINK_3_Pin,GPIO_PIN_SET):\
											HAL_GPIO_WritePin(BLINK_3_GPIO_Port,BLINK_3_Pin,GPIO_PIN_RESET))		    //		 :        
#define BLINK_4_Write(n) (n?HAL_GPIO_WritePin(BLINK_4_GPIO_Port,BLINK_4_Pin,GPIO_PIN_SET):\
											HAL_GPIO_WritePin(BLINK_4_GPIO_Port,BLINK_4_Pin,GPIO_PIN_RESET))     		//BLINK4闪烁
#define TXB0108_Enable(n) (n?HAL_GPIO_WritePin(LOGIC_OE_GPIO_Port,LOGIC_OE_Pin,GPIO_PIN_SET):\
											HAL_GPIO_WritePin(LOGIC_OE_GPIO_Port,LOGIC_OE_Pin,GPIO_PIN_RESET))      //3.3与5v互转使能
											
#define Dataerror		1						//无法显示数据标识

/*输出数据定义*/
#define DISPLAY_0 0x000003FE
#define DISPLAY_1 0x000003DF
#define DISPLAY_2	0x000003FB
#define	DISPLAY_3 0x000003F7
#define	DISPLAY_4	0x000003EF
#define	DISPLAY_5 0x000003DF
#define	DISPLAY_6	0x000003BF
#define	DISPLAY_7	0x0000037F
#define	DISPLAY_8	0x000002FF
#define	DISPLAY_9	0x000001FF



enum{
	LE_SET=0,
	LE_RESET
};

enum{
	BL_SET=0,
	BL_RESET
};

enum{
	POL_SET=0,
	POL_RESET
};

enum{
	DIR_A2B=1,
	DIR_B2A=0
};

enum{
	HVCLK_Down=0,
	HVCLK_Up
};

void HV_Display_Init_write(void);									//初始化
uint8_t Data2Signal(uint8_t *Point2Data);					//解析数据并写到HV57708

#endif
