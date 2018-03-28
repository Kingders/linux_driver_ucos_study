/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    06-March-2015
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include <includes.h>
#include "bsp_usart1.h"
#include "bsp_exti.h"



extern OS_TCB	 AppTaskUsartTCB;
extern OS_TCB	 AppTaskKeyTCB;

extern OS_MEM  mem;



/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @brief  USART 中断服务函数
  * @param  无
  * @retval 无
  */	
void macUSART_INT_FUN(void)
{
	OS_ERR   err;
	
	char *   p_mem_blk;
	
	
	OSIntEnter(); 	                                     //进入中断
	
	/* 从内存分区 mem 获取一个内存块 */
	p_mem_blk = OSMemGet((OS_MEM      *)&mem,
										   (OS_ERR      *)&err);
	
	if ( USART_GetITStatus ( macUSARTx, USART_IT_RXNE ) != RESET )
	{
		* p_mem_blk = USART_ReceiveData ( macUSARTx );     //获取接收到的数据
		
    /* 发布任务消息到任务 AppTaskUsart */
		OSTaskQPost ((OS_TCB      *)&AppTaskUsartTCB,      //目标任务的控制块
								 (void        *)p_mem_blk,             //消息内容的首地址
								 (OS_MSG_SIZE  )1,                     //消息长度
								 (OS_OPT       )OS_OPT_POST_FIFO,      //发布到任务消息队列的入口端
								 (OS_ERR      *)&err);                 //返回错误类型
		
	}
	
	OSIntExit();	                                       //退出中断
	
}


/**
  * @brief  EXTI 中断服务函数
  * @param  无
  * @retval 无
  */
void macEXTI_INT_FUNCTION (void)
{
	OS_ERR   err;
	
	
	OSIntEnter(); 	                             //进入中断
	
	if(EXTI_GetITStatus(macEXTI_LINE) != RESET)  //确保是否产生了EXTI Line中断
	{
		/* 发送任务信号量到任务 AppTaskKey */
		OSTaskSemPost((OS_TCB  *)&AppTaskKeyTCB,   //目标任务
									(OS_OPT   )OS_OPT_POST_NONE, //没选项要求
									(OS_ERR  *)&err);            //返回错误类型		

		EXTI_ClearITPendingBit(macEXTI_LINE);      //清除中断标志位
	}  
	
	OSIntExit();	                               //退出中断
	
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
