#include "bsp_exti.h"

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
	
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = macEXTI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}


 /**
  * @brief  配置 PA0 为线中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */
void EXTI_Pxy_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	
	/*开启按键GPIO口的时钟*/
	RCC_AHB1PeriphClockCmd( macEXTI_GPIO_CLK, ENABLE );

  GPIO_InitStructure.GPIO_Pin = macEXTI_GPIO_PIN;         //选择按键的引脚 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	          //设置引脚为输入模式 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;          //设置引脚为上拉
  GPIO_Init(macEXTI_GPIO_PORT, &GPIO_InitStructure);      //使用上面的结构体初始化按键
	
	/* 连接 EXTI 中断源到按键引脚 */
  SYSCFG_EXTILineConfig(macEXTI_SOURCE_PORT, macEXTI_SOURCE_PIN);

  /* 选择 EXTI 中断源 */
  EXTI_InitStructure.EXTI_Line = macEXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);


	/* config the NVIC */
	NVIC_Configuration();


}
/*********************************************END OF FILE**********************/
