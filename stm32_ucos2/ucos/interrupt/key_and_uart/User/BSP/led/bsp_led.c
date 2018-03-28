#include "bsp_led.h" 



static void                         LED_GPIO_Config                  ( void );



 /**
  * @brief  ���� LED �� GPIO ����
  * @param  ��
  * @retval ��
  */
static void LED_GPIO_Config ( void )
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* ���� LED1 ���� */
	macLED1_GPIO_xClock_FUN ( macLED1_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = macLED1_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( macLED1_GPIO_PORT, & GPIO_InitStructure );	

	/* ���� LED2 ���� */
	macLED2_GPIO_xClock_FUN ( macLED2_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = macLED2_GPIO_PIN;	
	GPIO_Init ( macLED2_GPIO_PORT, & GPIO_InitStructure );	

	/* ���� LED3 ���� */
	macLED2_GPIO_xClock_FUN ( macLED3_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = macLED3_GPIO_PIN;	
	GPIO_Init ( macLED3_GPIO_PORT, & GPIO_InitStructure );		
	  		
}


 /**
  * @brief  LED ��ʼ������
  * @param  ��
  * @retval ��
  */
void LED_Init ( void )
{
  LED_GPIO_Config ();
	
	macLED1_OFF();
	macLED2_OFF();
	macLED3_OFF();
	
}



/*********************************************END OF FILE**********************/

