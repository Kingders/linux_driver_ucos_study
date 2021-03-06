#ifndef __USART1_H
#define	__USART1_H


#include "stm32f4xx.h"
#include <stdio.h>



/**************************USART��������********************************/
#define             macUSARTx                                USART1
#define             macUSART_BAUD_RATE                       115200
#define             macUSART_xClock_FUN                      RCC_APB2PeriphClockCmd
#define             macUSART_CLK                             RCC_APB2Periph_USART1

#define             macUSART_GPIO_xClock_FUN                 RCC_AHB1PeriphClockCmd
#define             macUSART_GPIO_CLK                        RCC_AHB1Periph_GPIOA     
#define             macUSART_TX_PORT                         GPIOA   
#define             macUSART_TX_PIN                          GPIO_Pin_9
#define             macUSART_TX_AF                           GPIO_AF_USART1
#define             macUSART_TX_SOURCE                       GPIO_PinSource9
#define             macUSART_RX_PORT                         GPIOA 
#define             macUSART_RX_PIN                          GPIO_Pin_10
#define             macUSART_RX_AF                           GPIO_AF_USART1
#define             macUSART_RX_SOURCE                       GPIO_PinSource10

#define             macUSART_IRQ                             USART1_IRQn
#define             macUSART_INT_FUN                         USART1_IRQHandler



void                USARTx_Config                           ( void );



#endif /* __USART1_H */

