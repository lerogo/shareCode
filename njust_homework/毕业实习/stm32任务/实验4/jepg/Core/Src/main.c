/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "libjpeg.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"bmp_file.hpp"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_LIBJPEG_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */

	char getLen[8];

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		// 读取图片大小
		HAL_UART_Receive(&huart1, (uint8_t*) getLen, 8, 0xffff);
		// 输出图片大小
		HAL_UART_Transmit(&huart1, (uint8_t*) getLen, 8, 0xffff);
		int imgLen = 0, i = 0;
		for (i = 0; i < 8; ++i) {
			imgLen = imgLen * 10 + getLen[i] - '0';
		}
		// 建立缓冲区
		unsigned char *imgData = malloc(imgLen);
		memset(imgData, 0, imgLen);
		// 不断接收
		for (i = 0; i < imgLen; i += 256) {
			if (imgLen - i < 256) {
				HAL_UART_Receive(&huart1, (uint8_t*) (imgData + i), imgLen - i,
						0xffff);
			} else {
				HAL_UART_Receive(&huart1, (uint8_t*) (imgData + i), 256,
						0xffff);
			}
		}
		// libjpeg使用
		struct jpeg_decompress_struct info; //for our jpeg info
		struct jpeg_error_mgr err; //the error handler
		info.err = jpeg_std_error(&err);
		jpeg_create_decompress(&info); //fills info structure
		jpeg_mem_src(&info, imgData, imgLen);
		jpeg_read_header(&info, 1);
		jpeg_start_decompress(&info);
		unsigned int w = info.output_width;
		unsigned int h = info.output_height;
		unsigned int numChannels = info.num_components; // 3 = RGB, 4 = RGBA
		unsigned long dataSize = w * h * numChannels;
		unsigned char *data = (unsigned char*) malloc(dataSize);
		unsigned char *rowptr;
		while (info.output_scanline < h) {
			rowptr = data + (h - info.output_scanline - 1) * w * numChannels;
//			rowptr = data + info.output_scanline * w * numChannels;
			jpeg_read_scanlines(&info, &rowptr, 1);
			// bgr 交换
			unsigned char tmpDataSwap;
			int colIdnex = w*numChannels;
			for (i = 0; i < colIdnex; i+=3) {
				tmpDataSwap = rowptr[i];
				rowptr[i] = rowptr[i + 2];
				rowptr[i + 2] = tmpDataSwap;
			}
		}
		jpeg_finish_decompress(&info);
		jpeg_destroy_decompress(&info);

		// 写bmp文件
		struct bmp_file bmp1;
		unsigned fileHeaderSize = sizeof(bmp1.fileHeader);
		unsigned infoHeaderSize = sizeof(bmp1.infoHeader);
		unsigned img_size = dataSize + 4
				- ((bmp1.fileHeader.offset_bits + dataSize) % 4);
		bmp1.fileHeader.offset_bits = fileHeaderSize + infoHeaderSize;
		bmp1.fileHeader.file_type = ('M' << 8) | 'B';
		bmp1.fileHeader.file_size = bmp1.fileHeader.offset_bits + img_size;
		bmp1.infoHeader.image_depth = 24;
		bmp1.infoHeader.color_important = 0;
		bmp1.infoHeader.planes = 1;
		bmp1.infoHeader.compression = 0;
		bmp1.infoHeader.x_pels_permeter = 100;
		bmp1.infoHeader.y_pels_permeter = 100;
		bmp1.infoHeader.color_used = 0;
		bmp1.infoHeader.color_important = 0;
		bmp1.infoHeader.bitmap_info_size = infoHeaderSize;
		bmp1.infoHeader.bitmap_width = w;
		bmp1.infoHeader.bitmap_height = h;
		bmp1.infoHeader.image_size = img_size;

		// 传输头
		for (i = 0; i < fileHeaderSize; i += 256) {
			if (fileHeaderSize - i < 256) {
				HAL_UART_Transmit(&huart1,
						(uint8_t*) ((char*) &bmp1.fileHeader + i),
						fileHeaderSize - i, 0xffff);
			} else {
				HAL_UART_Transmit(&huart1,
						(uint8_t*) ((char*) &bmp1.fileHeader + i), 256, 0xffff);
			}
		}
		for (i = 0; i < infoHeaderSize; i += 256) {
			if (infoHeaderSize - i < 256) {
				HAL_UART_Transmit(&huart1,
						(uint8_t*) ((char*) &bmp1.infoHeader + i),
						infoHeaderSize - i, 0xffff);
			} else {
				HAL_UART_Transmit(&huart1,
						(uint8_t*) ((char*) &bmp1.infoHeader + i), 256, 0xffff);
			}
		}

		// 传输data
		for (i = 0; i < dataSize; i += 256) {
			if (dataSize - i < 256) {
				HAL_UART_Transmit(&huart1, (uint8_t*) (data + i), dataSize - i,
						0xffff);
			} else {
				HAL_UART_Transmit(&huart1, (uint8_t*) (data + i), 256, 0xffff);
			}
		}
		HAL_UART_Transmit(&huart1, (uint8_t*) "\0", img_size - dataSize,
				0xffff);

		HAL_GPIO_TogglePin(GPIOA, led1_Pin);
		HAL_Delay(800);
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
