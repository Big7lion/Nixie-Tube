/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "string.h"
#include "usart.h"
#include "ds18b20.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId TEMP_TaskHandle;
osThreadId TIME_TaskHandle;
osThreadId NIXIE_TaskHandle;
osThreadId wifi_TaskHandle;
osThreadId uart_TaskHandle;

/* USER CODE BEGIN Variables */
int16_t Temp;
static SemaphoreHandle_t  xMutex = NULL;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void TEMP_Task02(void const * argument);
void TIME_Task03(void const * argument);
void display_Task04(void const * argument);
void wifi_Task05(void const * argument);
void serial_Task06(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void AppObjCreate (void);
void USART_SendData(UART_HandleTypeDef* uartHandle,void const * argument, ...);
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 88);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of TEMP_Task */
  osThreadDef(TEMP_Task, TEMP_Task02, osPriorityNormal, 0, 128);
  TEMP_TaskHandle = osThreadCreate(osThread(TEMP_Task), NULL);

  /* definition and creation of TIME_Task */
  osThreadDef(TIME_Task, TIME_Task03, osPriorityNormal, 0, 128);
  TIME_TaskHandle = osThreadCreate(osThread(TIME_Task), NULL);

  /* definition and creation of NIXIE_Task */
  osThreadDef(NIXIE_Task, display_Task04, osPriorityNormal, 0, 128);
  NIXIE_TaskHandle = osThreadCreate(osThread(NIXIE_Task), NULL);

  /* definition and creation of wifi_Task */
  osThreadDef(wifi_Task, wifi_Task05, osPriorityBelowNormal, 0, 100);
  wifi_TaskHandle = osThreadCreate(osThread(wifi_Task), NULL);

  /* definition and creation of uart_Task */
  osThreadDef(uart_Task, serial_Task06, osPriorityLow, 0, 88);
  uart_TaskHandle = osThreadCreate(osThread(uart_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* TEMP_Task02 function */
void TEMP_Task02(void const * argument)
{
  /* USER CODE BEGIN TEMP_Task02 */
	uint32_t xLastWakeTime;
	const uint32_t xFrequency = 200;
//	uint16_t temp;
//  char SendData[64];
	/* 获取当前的系统时间 */
  xLastWakeTime = xTaskGetTickCount();
	AppObjCreate();
  /* Infinite loop */
  for(;;)
  {
		Temp =DS18B20_ReadTempReg();
		xSemaphoreGive(xMutex);
//		sprintf(SendData,"Now the TEMP is %.2f C",(float)temp/16);
//		USART_SendData(&SendData);
    osDelay(1000);
  }
  /* USER CODE END TEMP_Task02 */
}

/* TIME_Task03 function */
void TIME_Task03(void const * argument)
{
  /* USER CODE BEGIN TIME_Task03 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END TIME_Task03 */
}

/* display_Task04 function */
void display_Task04(void const * argument)
{
  /* USER CODE BEGIN display_Task04 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END display_Task04 */
}

/* wifi_Task05 function */
void wifi_Task05(void const * argument)
{
  /* USER CODE BEGIN wifi_Task05 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END wifi_Task05 */
}

/* serial_Task06 function */
void serial_Task06(void const * argument)
{
  /* USER CODE BEGIN serial_Task06 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END serial_Task06 */
}

/* USER CODE BEGIN Application */
void AppObjCreate (void)
{
		/* 创建互斥信号量 */
    xMutex = xSemaphoreCreateMutex();
	
	if(xMutex == NULL)
    {
      /* 没有创建成功，在这里加入创建失败的处理机制 */
			USART_SendData(Serial_Uart,"xMutex Create Failed!\r\n\0");
    }
}


/* USART_SendData function */
void USART_SendData(UART_HandleTypeDef* uartHandle,void const * argument, ...)
{
  /* USER CODE BEGIN USART_SendData */
  /* Infinite loop */
    char  buf_str[200];
		UART_HandleTypeDef *UART2SEND;
//    va_list   v_args;
//    va_start(v_args, argument);
//   (void)vsnprintf((char       *)&buf_str[0],
//                   (size_t      ) sizeof(buf_str),
//                   (char const *) argument,
//                                  v_args);
//    va_end(v_args);
	
		/* 互斥信号量 */
		xSemaphoreTake(xMutex, portMAX_DELAY);
		if(uartHandle->Instance==USART1)
		{
			UART2SEND=&huart1;
		}
		else if(uartHandle->Instance==USART3)
		{
			UART2SEND=&huart3;
		}
		else
		{
			xSemaphoreGive(xMutex);
			USART_SendData(Serial_Uart,"UART select error!\r\n\0");
			return;
		}
		sprintf(buf_str,"%s\r\n",argument);
    HAL_UART_Transmit(UART2SEND,(uint8_t*)buf_str,strlen(buf_str),300);
   	xSemaphoreGive(xMutex);
  /* USER CODE END USART_SendData */
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
