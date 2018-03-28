/*interrupt registes*/
#define EXT_INT_2_CON       *((volatile unsigned int *)0xE0200E08)   
#define EXT_INT_2_MASK      *((volatile unsigned int *)0xE0200F08)       
#define VIC0INTENABLE       *((volatile unsigned int *)0xF2000010)   
#define key_VICADDR         *((volatile unsigned int *)0xF2000140)     
#define VIC0ADDRESS         *((volatile unsigned int *)0xF2000F00)   
#define EXT_INT_2_PEND      *((volatile unsigned int *)0xE0200F48)  

void key_isr()
{
    volatile unsigned int key_code;
    
    __asm__( 				//���滷��
    					//�жϳ�����,�ı��ֻ��pcָ��ֵ,�������Ĵ������жϳ���ı�ǰ��Ҫ��������
    "sub lr, lr, #4\n"  		//����ldr
    "stmfd sp!, {r0-r12, lr}\n"       	//��r1~r12,�Լ�lr ѹ��ջ
    : 
    : 
   );

 
    key_code = EXT_INT_2_PEND & 0b11; 
	
    switch(key_code) 
    {
        case 1: //K1
            led_on();
            break;
		
        case 2: //K2
            led_off();
            break;
		
        default:
            break;
    }
	
    /* ����ж� */    
    EXT_INT_2_PEND =  ~0x0;  		//����൱�ڶ�Ӧflags
    VIC0ADDRESS = 0;			//�жϺ�������ʱ,�жϺ����ĵ�ַҲ�ᱣ�浽������!!,����ʱ�ǵ������		
   
    __asm__( 				//�ظ�����
    "ldmfd sp!, {r0-r12, pc}^ \n"       //��ջ��Ķ���ȡ����
    : 
    : 
  );
}



void init_irq()
{
    EXT_INT_2_CON = 0b010 | (0b010<<4);    /*EINT16,17�½��ش����ж�,EINT[16]~[31]����Ӧvic16����Ĵ������õ��жϴ�������ַ*/
    EXT_INT_2_MASK = 0;                   /* ȡ�������ⲿ�ж�,�����ж�*/  
 
    VIC0INTENABLE = 0b1<<16;              /*����vic[16]����жϵ�ַ*/ 
    key_VICADDR = (int)key_isr;           /*����key1~key4����ͬһ�ж�Դ������ֻ������һ����ַ*/
    
    __asm__( 
    /*���ж�*/  
    "mrs r0,cpsr\n"
    "bic r0, r0, #0x80\n"
    "msr cpsr_c, r0\n"            
    : 
    : 
  );
}
