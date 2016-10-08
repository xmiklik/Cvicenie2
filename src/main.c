/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 6.0.0   2016-10-04

The MIT License (MIT)
Copyright (c) 2009-2016 Atollic AB

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************
*/

/* Includes */
#include <stddef.h>
#include "stm32l1xx.h"


/* Private typedef */
/* Private define  */
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */


/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	uint8_t button;

		//nastavenie vystupu pre LED
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	// LED
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);	// periferia tlacidla

		GPIOA->MODER |=(0b01)<<(5*2);	// out
		GPIOA->OTYPER &= ~((0b1)<<5);	// push pull
		GPIOA->PUPDR |= (0b01)<<(5*2);	// up
		GPIOA->OSPEEDR |= (0b11)<<(5*2);	// 40MHz

		//nastavenie vstupu pre tlacidlo ul2
		GPIOC->MODER &= ~((0b11)<<(13*2));	// Input
		GPIOC->OTYPER &= ~((0b1)<<13);		// Push pull
		GPIOC->PUPDR &=  ~(0b11<<(13*2));	// No pull

		GPIOA->ODR |= 0b1<<5;		// ul1 zapnutie
		GPIOA->ODR &= ~(0b1<<5);	// ul1 vypnutie
		GPIOA->BSRRL |= 0b1<<5;		// ul1 zasvietenie
		GPIOA->BSRRH |= 0b1<<5;		// ul1 vypnutie

		GPIOA->ODR ^= 0b1<<5; // ul1 zmena stavu LED (zapnute)
		GPIOA->ODR ^= 0b1<<5; //ul1 zmena stavu LED (vypnute)


	  while (1)
	  {
		  button = (GPIOC->IDR & (0b1<<13))>>13;

		  if(button==0)
		  {
			  GPIOA->ODR |= 0b1<<5;
		  }
		  else
		  {
			  GPIOA->ODR &= ~(0b1<<5);
		  }

		  for(int i=0;i<1000000;i++)
		        GPIOA->ODR |= 0b1<<5;
		  for(int i=0;i<1000000;i++)
		        GPIOA->ODR &= ~(0b1<<5);

	  }
	  return 0;
	}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
