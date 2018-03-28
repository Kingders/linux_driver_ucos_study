#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");

#define GPH2CON		0xe0200c40

static struct resource key_resource[] = {	//��ʼ����������Դ
	[0] = {
		.start = GPH2CON,
		.end   = GPH2CON + 3,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_EINT(16),
		.end   = IRQ_EINT(16),
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device key_device = {
	.name		  = "key1",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(key_resource),	//������� key_resource[] ��������Ա
	.resource	  = key_resource,		//��д��Դ�ĵ�ַ
};

static int button_init()
{
    platform_device_register(&key_device);
     
    return 0;
}


static void button_exit()
{	   
    platform_device_unregister(&key_device);
}


module_init(button_init);
module_exit(button_exit);
