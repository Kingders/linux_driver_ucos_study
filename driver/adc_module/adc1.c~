
//linux模块加载使用的头文件
#include <linux/module.h>
#include <linux/init.h>
//中断相关头文件
#include <linux/miscdevice.h>
#include <linux/kernel.h>	//printk
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
//gpio初始化相关

//reg about pioE
#define PE_PER	0xFC06D000	//write only
#define PE_PDR	0xFC06D004	//write only
#define PE_PSR	0xFC06D008	//read only
#define PE_OSR	0xFC06D018	//output status	(0:input,1:output)
#define PE_OER  0xFC06D010
#define PE_ODR	0xFC06D014	//output disable
#define PE_IFER	0xFC06D020	//input glitch filter enable reg
#define PE_IFSR	0xFC06D028	//input glitch filter status
#define PE_WPMR 0xFC06D0E4	//write protection enable (for enable some reg writing)
#define PE_PUSR	0xFC06D068	//pull up status (0:enabled,1:disabled)
#define PE_PUER	0xFC06D064	//pill up enable
#define PE_IMR	0xFC06D048	//interrupt mask reg (0:interrupt disabled,1:interrupt enabled)
#define PE_IER	0xFC06D040	//interrupt enable reg
#define PE_PDSR 0xFC06D03C	//PIO Pin Data Status Register
#define PE_PPDSR 0xFC06D098	//PIO Pad Pull-Down Status Register
#define PE_PPDDR 0xFC06D090	//PIO Pad Pull-Down Disable Register

//中断处理函数
static irqreturn_t button_inter (int irq, void *dev_id)
{
	printk(KERN_EMERG "p\n");
	
	return IRQ_HANDLED;
}
	
//按钮硬件初始化
void PE8_init(void)
{
	unsigned int rd;	//read data
	unsigned int wd;	//write data
	void __iomem *pio;

	/* 设置 pe8 input 口 */

	//pio enable  (disable peripheral)
	pio = ioremap(PE_PSR,4);
	rd = readl_relaxed(pio);
	wd = (1<<8) | rd ;
	pio = ioremap(PE_PER,4);
	writel_relaxed(wd, pio);

	//设置 pio input 模式
	pio = ioremap(PE_OSR,4);
	rd = readl_relaxed(pio);
	wd = ~rd;
	wd = (1<<8) | wd ;
	pio = ioremap(PE_ODR,4);
	writel_relaxed(wd, pio);

	//Enables the input glitch filter(能过滤接触一刻的震颤行为)
	pio = ioremap(PE_IFSR,4);
	rd = readl_relaxed(pio);
	wd = (1<<8) | rd ;
	pio = ioremap(PE_IFER,4);
	writel_relaxed(wd, pio);

	//先要关闭 pulldowm 下拉电阻 (不然后面无法设置上拉电阻) (奇怪,写某一位,居然 关闭 PE所有针的pull_dowm)
	pio = ioremap(PE_PPDSR,4);
	rd = readl_relaxed(pio);
	wd = ~rd;
	wd = (1<<8) | wd ;
	pio = ioremap(PE_PPDDR,4);
	writel_relaxed(wd, pio);

	//设置  input pullup 上拉电阻
	pio = ioremap(PE_PUSR,4);
	rd = readl_relaxed(pio);
	wd = ~rd;
	wd = (1<<8) | wd ;
	pio = ioremap(PE_PUER,4);
	writel_relaxed(wd, pio);

	/* 设置 pe8 interrupt */

	//启动 io 中断
	pio = ioremap(PE_IMR,4);
	rd = readl_relaxed(pio);
	wd = (1<<8) | rd ;
	pio = ioremap(PE_IER,4);
	writel_relaxed(wd, pio);

	//未设置其他中断寄存器,所以默认为 both-edge(上升下降沿都促发) 模式
}

static int button_init(void)
{
	int ret;
	printk(KERN_EMERG "irq_init_start\n");


	//注册中断处理程序
	//linux中断号186:系统已经绑定给针 PE8 的中断号, 
	//button_inter:中断处理函数, 
	//flags:IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING 表示上升下降沿触发中断,
	//button1:中断的名称, 
	//ID:中断号irq_desc里挂载关于这个中断的中断事件id号,从而区别使用同一个中断号里的各个中断事件(主要为共享中断服务,一般复用dev数据指针作为ID号)
	ret = request_irq(186, button_inter, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "button1", (void *)1);	
	//ret = request_irq(41, button_inter, 0, "adc1", (void *)1);	

	//按键硬件初始化
	PE8_init();

	printk(KERN_EMERG "irq_init_complete\n");
	return 0;
}

void button_exit(void)
{
	printk(KERN_EMERG "irq_init_exit\n");
	//注销中断处理函数
	free_irq(186,(void *)1);	//irgno:中断号,1:irq_desc里的设备号

}

MODULE_LICENSE("GPL");

module_init(button_init);
module_exit(button_exit);
