/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include <stdint.h>
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "myFlash.h"
#include "myLib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/

/**
 * @brief Page number x has start_address = 1024*x
 * 
 */
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t data[] = {22, 12, 1998, 1, 2, 3, 4, 5, 6};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void write_flash(uint32_t start_address, uint32_t end_address)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint32_t error_count = 0;

  HAL_FLASH_Unlock();

  FLASH_EraseInitTypeDef EraseInitStruck;
  EraseInitStruck.TypeErase = FLASH_TYPEERASE_PAGES;
  // EraseInitStruck.Banks       = ;
  EraseInitStruck.PageAddress = start_address;
  EraseInitStruck.NbPages = (end_address - start_address) / FLASH_PAGE_SIZE;
  uint32_t PageError = 0xFFFFFFFF;

  status = HAL_FLASHEx_Erase(&EraseInitStruck, &PageError);
  if (status != HAL_OK)
  {
    ++error_count;
    print("Flash Erase failed\r\n");
    print(__FILE__);
    print(__LINE__);
    print("\r\n");
  }

  status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, start_address, 22);
  if (status != HAL_OK)
  {
    ++error_count;
  }
  status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, start_address + 4, 12);
  if (status != HAL_OK)
  {
    ++error_count;
  }
  status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, start_address + 8, 1998);
  if (status != HAL_OK)
  {
    ++error_count;
  }
  if (error_count != 0)
  {
    print("Write Flash failed\r\n");
  }

  if (error_count == 0)
  {
    print("Write Flash success\r\n");
  }
  HAL_FLASH_Lock();
}

uint32_t read_flash(uint32_t flash_address)
{
  uint32_t data = *(volatile uint32_t *)(flash_address);
  return data;
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  PRINTF("################################################################################################\r\n");
  PRINTF("Project name: [FLASH]ReadWrite_internal_flash\r\n");
  PRINTF("**********************************SHORT DESCRIPTION******************************\r\n");
  PRINTF("This project illustrate how to write data to internal flash as well as Read out Flash data\r\n");
  PRINTF("*********************************************************************************\r\n");
  PRINTF("Run Application\r\n");

  PRINTF("\r\nStart writing data to internal Flash\r\n");
  Flash_WriteWord(ADDR_FLASH_PAGE_50, FLASH_END_ADDRESS, data, sizeof(data) / 4);

  PRINTF("\r\nVerify written data\r\n");
  for (size_t i = 0; i < sizeof(data) / 4; i++)
  {
    printVar(Flash_ReadAddress(ADDR_FLASH_PAGE_50 + i * 4));
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
      toggleLed4;
      HAL_Delay(1000);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
     */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
