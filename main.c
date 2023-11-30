/**
  ******************************************************************************
  * @file    main.c
  * @author  SRA
  * @version v1.3.0
  * @date    17-Sep-2021
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
#include "arm_math.h"
#include "audio_application.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define FFT_BUFFER_SIZE 2048

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
extern float PCM_Buffer[FFT_BUFFER_SIZE];
arm_rfft_fast_instance_f32 fftHandler;
float fftBufOut[FFT_BUFFER_SIZE];
uint8_t fftFlag =0;
int new_Audio=1;
float fft_freq[FFT_BUFFER_SIZE/2+1];
float sampling_rate = 8000.0f; //fréquence d'echantillonage à 8kHz


/** @addtogroup X_CUBE_MEMSMIC1_Applications
  * @{
  */

/** @addtogroup Microphones_Acquisition
  * @{
  */

/** @defgroup MAIN
  * @{
  */

/** @defgroup MAIN_Exported_Variables
  * @{
  */
USBD_HandleTypeDef hUSBDDevice;
extern USBD_AUDIO_ItfTypeDef  USBD_AUDIO_fops;
/**
  * @}
  */

/** @defgroup MAIN_Private_Functions
  * @{
  */
/* Private function prototypes -----------------------------------------------*/
/**
  * @}
  */

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

    /* STM32F4xx HAL library initialization:
    - Configure the Flash prefetch, instruction and Data caches
    - Configure the Systick to generate an interrupt each 1 msec
    - Global MSP (MCU Support Package) initialization
    */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();
    /* Initialize USB descriptor basing on channels number and sampling frequency */
    USBD_AUDIO_Init_Microphone_Descriptor(&hUSBDDevice, AUDIO_IN_SAMPLING_FREQUENCY, AUDIO_IN_CHANNELS);
    /* Init Device Library */
    USBD_Init(&hUSBDDevice, &AUDIO_Desc, 0);
    /* Add Supported Class */
    USBD_RegisterClass(&hUSBDDevice, &USBD_AUDIO);
    /* Add Interface callbacks for AUDIO Class */
    USBD_AUDIO_RegisterInterface(&hUSBDDevice, &USBD_AUDIO_fops);
    /* Start Device Process */
    USBD_Start(&hUSBDDevice);

    arm_rfft_fast_init_f32(&fftHandler,FFT_BUFFER_SIZE);


    /* Start audio acquisition and streaming */
#ifdef DISABLE_USB_DRIVEN_ACQUISITION
    Init_Acquisition_Peripherals(AUDIO_IN_SAMPLING_FREQUENCY, AUDIO_IN_CHANNELS, 0);
  Start_Acquisition();
#endif

    while (1)
    {
        if(new_Audio){
            arm_rfft_fast_f32(&fftHandler,PCM_Buffer,fftBufOut,fftFlag);

            for(int k;k<=FFT_BUFFER_SIZE/2;++k){
                fft_freq[k]= (float)k*sampling_rate/FFT_BUFFER_SIZE;
            }

            fftFlag =1;
        }
    }
}

/* Private functions ---------------------------------------------------------*/


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
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif  /* USE_FULL_ASSERT */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

