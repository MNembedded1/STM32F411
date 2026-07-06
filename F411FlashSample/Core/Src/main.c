/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FLASH_TIMEOUT_VALUE       50000U /* 50 s */

#define FLASH_USER_START_ADDR   0x0800C000
#define FLASH_USER_END_ADDR (FLASH_USER_START_ADDR + 0x4000 - 1)


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint32_t SectorError = 0;

uint32_t UserAddress = 0;

static FLASH_EraseInitTypeDef F411EraseInitStruct;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void GetChar(uint8_t *pByte);
void userInput();
#define MY_PUTCHAR int __io_putchar(int ch)
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	userInput();
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_ODD;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
MY_PUTCHAR
{
	  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);

	  return ch;
}

void GetChar(uint8_t *pByte)
{
	  HAL_UART_Receive(&huart2, pByte, 1, 100);
}

void userInput()
{
   uint8_t inputChar = 0;

   GetChar(&inputChar);

   HAL_StatusTypeDef flashStatus = HAL_OK;

   // TODO: set inputchar to upper case use ToUpper()

   if(0 != inputChar)
   {
	 switch(inputChar)
	 {
	 	 case 'H':
	 	 case 'h':
	 	 	 {
	 	 		printf("\n\r help Menu type any of the following letters:\n\r");
	 	 		printf("\n\r 'E': Erase sector 3 \n\r");
	 	 		printf("\n\r 'P': Simple Programming example \n\r");
	 	 	 }
	 		 break;
	 	 case 'E':
	 	 case 'e':
	 		    printf("\n\r 'E': Erase sector 3 \n\r");

	 			F411EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	 			F411EraseInitStruct.Banks = FLASH_BANK_1;

	 			// let's erase sector 3, lower sectors are for our code and we don't want to erase them
	 			F411EraseInitStruct.Sector = FLASH_SECTOR_3;

	 			// we just erase one sector as a test
	 			F411EraseInitStruct.NbSectors = 1;
	 		    flashStatus = HAL_FLASH_Unlock();
	 		    if(HAL_OK != flashStatus)
	 		    {
	 		    	printf("\n\r 'E': Unlock flash failed, status is 0x%d \n\r", flashStatus);
	 		    }
	 		    /* Wait for last operation to be completed */
	 		    flashStatus = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

	 		    if(HAL_OK != flashStatus)
	 		    {
	 		    	printf("\n\r 'E': wait for bsy bit failed, status is 0x%d \n\r", flashStatus);
	 		    }

	 		    flashStatus = HAL_FLASHEx_Erase(&F411EraseInitStruct, &SectorError);

	 		    if(HAL_OK != flashStatus)
	 		    {
	 		    	printf("\n\r 'E': Erasing failed, status is 0x%d \n\r", flashStatus);
	 		    }
	 		 break;
	 	 case 'P':
	 	 case 'p':
	 		    printf("\n\r 'P': Simple Programming example \n\r");
	 		    flashStatus = HAL_FLASH_Unlock();

	 		    if(HAL_OK != flashStatus)
	 		    {
	 		    	printf("\n\r 'P': Unlock flash failed, status is 0x%d \n\r", flashStatus);
	 		    }

	 			UserAddress = FLASH_USER_START_ADDR;

	 			while(UserAddress < FLASH_USER_END_ADDR)
	 			{
	 				HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, UserAddress, (uint64_t)0xDEED1234);


	 				if(HAL_OK != flashStatus)
	 				{
	 					printf("\n\r 'P': Programming 0x%lx failed, status is 0x%d \n\r", UserAddress, flashStatus);
	 					break;
	 				}
	 				UserAddress += 4;
	 			}



	 		    //flashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, 0x800C000, (uint64_t)0xABCD1234);

	 		    //if(HAL_OK != flashStatus)
	 		    //{
	 		    //	printf("\n\r 'P': Programming failed, status is 0x%d \n\r", flashStatus);
	 		    //}

	 		    break;
	 	 default:
	 		 break;
	 }

	 inputChar = 0;
   }


}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
