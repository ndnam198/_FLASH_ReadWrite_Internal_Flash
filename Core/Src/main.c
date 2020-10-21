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
#include "myLib.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
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
#define ADDR_FLASH_PAGE_0 ((uint32_t)0x08000000)  /* Base Address Page 0, 1Kbytes each */
#define ADDR_FLASH_PAGE_1 ((uint32_t)0x08000400)  /* Base Address Page 1, 1Kbytes each */
#define ADDR_FLASH_PAGE_2 ((uint32_t)0x08000800)  /* Base Address Page 2, 1Kbytes each */
#define ADDR_FLASH_PAGE_3 ((uint32_t)0x08000c00)  /* Base Address Page 3, 1Kbytes each */
#define ADDR_FLASH_PAGE_4 ((uint32_t)0x08001000)  /* Base Address Page 4, 1Kbytes each */
#define ADDR_FLASH_PAGE_5 ((uint32_t)0x08001400)  /* Base Address Page 5, 1Kbytes each */
#define ADDR_FLASH_PAGE_6 ((uint32_t)0x08001800)  /* Base Address Page 6, 1Kbytes each */
#define ADDR_FLASH_PAGE_7 ((uint32_t)0x08001c00)  /* Base Address Page 7, 1Kbytes each */
#define ADDR_FLASH_PAGE_8 ((uint32_t)0x08002000)  /* Base Address Page 8, 1Kbytes each */
#define ADDR_FLASH_PAGE_9 ((uint32_t)0x08002400)  /* Base Address Page 9, 1Kbytes each */
#define ADDR_FLASH_PAGE_10 ((uint32_t)0x08002800) /* Base Address Page 10, 1Kbytes each */
#define ADDR_FLASH_PAGE_11 ((uint32_t)0x08002c00) /* Base Address Page 11, 1Kbytes each */
#define ADDR_FLASH_PAGE_12 ((uint32_t)0x08003000) /* Base Address Page 12, 1Kbytes each */
#define ADDR_FLASH_PAGE_13 ((uint32_t)0x08003400) /* Base Address Page 13, 1Kbytes each */
#define ADDR_FLASH_PAGE_14 ((uint32_t)0x08003800) /* Base Address Page 14, 1Kbytes each */
#define ADDR_FLASH_PAGE_15 ((uint32_t)0x08003c00) /* Base Address Page 15, 1Kbytes each */
#define ADDR_FLASH_PAGE_16 ((uint32_t)0x08004000) /* Base Address Page 16, 1Kbytes each */
#define ADDR_FLASH_PAGE_17 ((uint32_t)0x08004400) /* Base Address Page 17, 1Kbytes each */
#define ADDR_FLASH_PAGE_18 ((uint32_t)0x08004800) /* Base Address Page 18, 1Kbytes each */
#define ADDR_FLASH_PAGE_19 ((uint32_t)0x08004c00) /* Base Address Page 19, 1Kbytes each */
#define ADDR_FLASH_PAGE_20 ((uint32_t)0x08005000) /* Base Address Page 20, 1Kbytes each */
#define ADDR_FLASH_PAGE_21 ((uint32_t)0x08005400) /* Base Address Page 21, 1Kbytes each */
#define ADDR_FLASH_PAGE_22 ((uint32_t)0x08005800) /* Base Address Page 22, 1Kbytes each */
#define ADDR_FLASH_PAGE_23 ((uint32_t)0x08005c00) /* Base Address Page 23, 1Kbytes each */
#define ADDR_FLASH_PAGE_24 ((uint32_t)0x08006000) /* Base Address Page 24, 1Kbytes each */
#define ADDR_FLASH_PAGE_25 ((uint32_t)0x08006400) /* Base Address Page 25, 1Kbytes each */
#define ADDR_FLASH_PAGE_26 ((uint32_t)0x08006800) /* Base Address Page 26, 1Kbytes each */
#define ADDR_FLASH_PAGE_27 ((uint32_t)0x08006c00) /* Base Address Page 27, 1Kbytes each */
#define ADDR_FLASH_PAGE_28 ((uint32_t)0x08007000) /* Base Address Page 28, 1Kbytes each */
#define ADDR_FLASH_PAGE_29 ((uint32_t)0x08007400) /* Base Address Page 29, 1Kbytes each */
#define ADDR_FLASH_PAGE_30 ((uint32_t)0x08007800) /* Base Address Page 30, 1Kbytes each */
#define ADDR_FLASH_PAGE_31 ((uint32_t)0x08007c00) /* Base Address Page 31, 1Kbytes each */
#define ADDR_FLASH_PAGE_32 ((uint32_t)0x08008000) /* Base Address Page 32, 1Kbytes each */
#define ADDR_FLASH_PAGE_33 ((uint32_t)0x08008400) /* Base Address Page 33, 1Kbytes each */
#define ADDR_FLASH_PAGE_34 ((uint32_t)0x08008800) /* Base Address Page 34, 1Kbytes each */
#define ADDR_FLASH_PAGE_35 ((uint32_t)0x08008c00) /* Base Address Page 35, 1Kbytes each */
#define ADDR_FLASH_PAGE_36 ((uint32_t)0x08009000) /* Base Address Page 36, 1Kbytes each */
#define ADDR_FLASH_PAGE_37 ((uint32_t)0x08009400) /* Base Address Page 37, 1Kbytes each */
#define ADDR_FLASH_PAGE_38 ((uint32_t)0x08009800) /* Base Address Page 38, 1Kbytes each */
#define ADDR_FLASH_PAGE_39 ((uint32_t)0x08009c00) /* Base Address Page 39, 1Kbytes each */
#define ADDR_FLASH_PAGE_40 ((uint32_t)0x0800a000) /* Base Address Page 40, 1Kbytes each */
#define ADDR_FLASH_PAGE_41 ((uint32_t)0x0800a400) /* Base Address Page 41, 1Kbytes each */
#define ADDR_FLASH_PAGE_42 ((uint32_t)0x0800a800) /* Base Address Page 42, 1Kbytes each */
#define ADDR_FLASH_PAGE_43 ((uint32_t)0x0800ac00) /* Base Address Page 43, 1Kbytes each */
#define ADDR_FLASH_PAGE_44 ((uint32_t)0x0800b000) /* Base Address Page 44, 1Kbytes each */
#define ADDR_FLASH_PAGE_45 ((uint32_t)0x0800b400) /* Base Address Page 45, 1Kbytes each */
#define ADDR_FLASH_PAGE_46 ((uint32_t)0x0800b800) /* Base Address Page 46, 1Kbytes each */
#define ADDR_FLASH_PAGE_47 ((uint32_t)0x0800bc00) /* Base Address Page 47, 1Kbytes each */
#define ADDR_FLASH_PAGE_48 ((uint32_t)0x0800c000) /* Base Address Page 48, 1Kbytes each */
#define ADDR_FLASH_PAGE_49 ((uint32_t)0x0800c400) /* Base Address Page 49, 1Kbytes each */
#define ADDR_FLASH_PAGE_50 ((uint32_t)0x0800c800) /* Base Address Page 50, 1Kbytes each */
#define ADDR_FLASH_PAGE_51 ((uint32_t)0x0800cc00) /* Base Address Page 51, 1Kbytes each */
#define ADDR_FLASH_PAGE_52 ((uint32_t)0x0800d000) /* Base Address Page 52, 1Kbytes each */
#define ADDR_FLASH_PAGE_53 ((uint32_t)0x0800d400) /* Base Address Page 53, 1Kbytes each */
#define ADDR_FLASH_PAGE_54 ((uint32_t)0x0800d800) /* Base Address Page 54, 1Kbytes each */
#define ADDR_FLASH_PAGE_55 ((uint32_t)0x0800dc00) /* Base Address Page 55, 1Kbytes each */
#define ADDR_FLASH_PAGE_56 ((uint32_t)0x0800e000) /* Base Address Page 56, 1Kbytes each */
#define ADDR_FLASH_PAGE_57 ((uint32_t)0x0800e400) /* Base Address Page 57, 1Kbytes each */
#define ADDR_FLASH_PAGE_58 ((uint32_t)0x0800e800) /* Base Address Page 58, 1Kbytes each */
#define ADDR_FLASH_PAGE_59 ((uint32_t)0x0800ec00) /* Base Address Page 59, 1Kbytes each */
#define ADDR_FLASH_PAGE_60 ((uint32_t)0x0800f000) /* Base Address Page 60, 1Kbytes each */
#define ADDR_FLASH_PAGE_61 ((uint32_t)0x0800f400) /* Base Address Page 61, 1Kbytes each */
#define ADDR_FLASH_PAGE_62 ((uint32_t)0x0800f800) /* Base Address Page 62, 1Kbytes each */
#define ADDR_FLASH_PAGE_63 ((uint32_t)0x0800fc00) /* Base Address Page 63, 1Kbytes each */

#define FLASH_END_ADDRESS ((uint32_t)0x08010000)
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
  write_flash(ADDR_FLASH_PAGE_50, FLASH_END_ADDRESS);
  printVar(read_flash(ADDR_FLASH_PAGE_50));
  printVar(read_flash(ADDR_FLASH_PAGE_50 + 4));
  printVar(read_flash(ADDR_FLASH_PAGE_50 + 8));

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

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
