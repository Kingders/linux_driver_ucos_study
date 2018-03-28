#include "bsp_exti.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
	
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* �����ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = macEXTI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}


 /**
  * @brief  ���� PA0 Ϊ���жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI_Pxy_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	
	/*��������GPIO�ڵ�ʱ��*/
	RCC_AHB1PeriphClockCmd( macEXTI_GPIO_CLK, ENABLE );

  GPIO_InitStructure.GPIO_Pin = macEXTI_GPIO_PIN;         //ѡ�񰴼������� 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	          //��������Ϊ����ģʽ 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;          //��������Ϊ����
  GPIO_Init(macEXTI_GPIO_PORT, &GPIO_InitStructure);      //ʹ������Ľṹ���ʼ������
	
	/* ���� EXTI �ж�Դ���������� */
  SYSCFG_EXTILineConfig(macEXTI_SOURCE_PORT, macEXTI_SOURCE_PIN);

  /* ѡ�� EXTI �ж�Դ */
  EXTI_InitStructure.EXTI_Line = macEXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);


	/* config the NVIC */
	NVIC_Configuration();


}
/*********************************************END OF FILE**********************/
