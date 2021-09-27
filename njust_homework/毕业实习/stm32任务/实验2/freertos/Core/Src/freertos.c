/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for task_led0 */
osThreadId_t task_led0Handle;
const osThreadAttr_t task_led0_attributes = { .name = "task_led0", .stack_size =
		128 * 4, .priority = (osPriority_t) osPriorityNormal, };
/* Definitions for task_led1 */
osThreadId_t task_led1Handle;
const osThreadAttr_t task_led1_attributes = { .name = "task_led1", .stack_size =
		128 * 4, .priority = (osPriority_t) osPriorityNormal, };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void task_led0_start(void *argument);
void task_led1_start(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
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

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* creation of task_led0 */
	task_led0Handle = osThreadNew(task_led0_start, NULL, &task_led0_attributes);

	/* creation of task_led1 */
	task_led1Handle = osThreadNew(task_led1_start, NULL, &task_led1_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_task_led0_start */
/**
 * @brief  Function implementing the task_led0 thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_task_led0_start */
void task_led0_start(void *argument) {
	/* USER CODE BEGIN task_led0_start */
	HAL_GPIO_WritePin(GPIOA, led0_Pin, GPIO_PIN_RESET);
	/* Infinite loop */
	for (;;) {
		HAL_GPIO_TogglePin(GPIOA, led0_Pin);
		osDelay(80);
	}
	/* USER CODE END task_led0_start */
}

/* USER CODE BEGIN Header_task_led1_start */
/**
 * @brief Function implementing the task_led1 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_task_led1_start */
void task_led1_start(void *argument) {
	/* USER CODE BEGIN task_led1_start */
	HAL_GPIO_WritePin(GPIOA, led1_Pin, GPIO_PIN_RESET);
	/* Infinite loop */
	for (;;) {
		HAL_GPIO_TogglePin(GPIOA, led1_Pin);
		osDelay(200);
	}
	/* USER CODE END task_led1_start */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
