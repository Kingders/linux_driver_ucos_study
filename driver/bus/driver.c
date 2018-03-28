/**************************************************************


��֮ǰ button_interrupt_waitqueue:button.c ��ͨ������linuxģ�鷽ʽ ��ɰ����ж��豸��linux�ϵ�ע�����

�����������ͨ�������豸��ע�� ��ɰ����ж��豸��linux�ϵ�ע�����


�ص�����:
bus.c
include/linux/device.h
struct bus_type {			//һ�����ߵ������ṹ
	const char	*name;		//�������ߵ�����
	int (*match)(struct device *dev, struct device_driver *drv);	//����ƥ�亯��,һ�����߹����豸/������Ϣʱ���Զ�ִ�еĺ���
	...}
extern int __must_check bus_register(struct bus_type *bus);	//���������豸����豸��,ע�Ტ����һ�������豸��linux��,�����豸������һ������
extern void bus_unregister(struct bus_type *bus); //��linux��ж��һ�������豸,�����豸ɾ����һ������,�ͷ������豸����豸��,

device.h
include/linux/device.h
struct device {				//һ���豸��Ϣ�������ṹ
	const char	*init_nam	//�����豸������
	struct bus_type	*bus;		//Ҫ����� ���� ������
	struct kobject kobj;		//��¼�����ں���Ϣ,�ر��,��һ���豸��Ϣ��������ʱ,���Ȱ� init_nam ���ݿ���kobj.name,Ȼ���ÿ� init_nam
	...}
extern int __must_check device_register(struct device *dev);	//��һ���豸��Ϣ��������
extern void device_unregister(struct device *dev);	//��ĳ������ע��һ���豸��Ϣ

driver.h
include/linux/device.h
struct device_driver {			//һ��������Ϣ�������ṹ
	const char	*name;		//��������������
	struct bus_type	*bus;		//Ҫ����� ���� ������
	int (*probe) (struct device *dev);  //һ��ƥ��߻��ڹʹ�,��ִ�еĺ���,һ�����������XX�豸����豸��,ע�Ტ����һ��XX�豸��linux��
	int (*remove) (struct device *dev); //ƥ��ɹ���,��������ע�� �豸������ ��Ϣʱ,��Ҫִ�еĺ���,һ���������linux��ж���豸,�ͷ��豸��
	...}
extern int __must_check driver_register(struct device_driver *drv);	//��һ��������Ϣ��������
extern void driver_unregister(struct device_driver *drv);	//��ĳ������ע��һ��������Ϣ



�������ͨ��(ע��makefile����,���������ں�ģ��)
��������:	insmod bus.ko	//���������豸����豸��,ע�Ტ����һ�������豸��linux��,�����豸������һ��key_bus_type����
		insmod device.ko	//��key_bus_typeע�� �豸��Ϣ,��������ƥ��,û����������Ϣ
		insmod driver.ko	//��key_bus_typeע�� ������Ϣ,������һ��ƥ��,�ɹ�!������driver.ko���peobe����
					//��probe�﹤��, ���������豸����豸��,ע�Ტ����һ�������ж��豸��linux��
		./app		//ִ�ж�Ӧ���û�����
		��������Ӧ
		rmmod device.ko	//��key_bus_typeж�� �豸��Ϣ,����driver.ko���remove����
				//��remove�﹤��, ��linuxж�ذ����ж��豸,���ͷ������豸����豸��
		����û�з�Ӧ
		insmod device.ko	//������key_bus_typeע�� �豸��Ϣ,����ƥ��,�ɹ�!������driver.ko���peobe����
		��������Ӧ
		rmmod driver.ko	//��key_bus_typeж�� ������Ϣ,ж��������Ϣǰ ���Զ�����driver.ko���remove����
				//��remove�﹤��, ��linuxж�ذ����ж��豸,���ͷ������豸����豸��
		����û�з�Ӧ
		insmod driver.ko	//������key_bus_typeע�� ������Ϣ,����ƥ��,�ɹ�!������driver.ko���peobe����
		��������Ӧ
		....
**************************************************************/


//linuxģ�����ʹ�õ�ͷ�ļ�
#include <linux/module.h>
#include <linux/init.h>
//�������豸���ͷ�ļ�
#include <linux/device.h>
//�ж����ͷ�ļ�
#include <linux/miscdevice.h>
#include <linux/kernel.h>	//printk
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
//�ȴ��������ͷ�ļ�
#include <linux/wait.h>	
#include <linux/sched.h>		//����TASK_UNINTERRUPTIBLE һ���

MODULE_LICENSE("GPL");

#define GPH2CON		0xe0200c40

extern struct bus_type key_bus_type;
wait_queue_head_t wq1;		//����һ���ȴ�����
int c = 0;			//���Եȴ����еı���

//�жϴ�����
irqreturn_t button_inter (int irq, void *dev_id)
{
	//����Ƿ��Լ����ж�(�����ж�)
	//����������ж�״̬,ʹ֮���Է�����һ���ж�
	//��������
	printk(KERN_EMERG "push !!\n");
	
	c = 999;

	wake_up(&wq1);		//����wq1
	
	return IRQ_HANDLED;
}
	
//��ťӲ����ʼ��
void hw_init(void)
{
	unsigned int *gpio_config;
	unsigned int data;

	//ȡ���Ĵ�����ַ
	gpio_config = ioremap(GPH2CON,4);

	//��֯����
	data = readw(gpio_config);		
	data &= ~0b11111111;
	data |= 0b11111111;
	
	//��������
	writew(data,gpio_config);

}

int button_open (struct inode *n, struct file *fd)
{
	return 0;
}

ssize_t button_read (struct file *filp, char __user *buff, size_t count, loff_t *pos)
{
	int ret_r;
	wait_event_killable(wq1, c);
	printk(KERN_EMERG "button_read:\n");
	ret_r = copy_to_user(buff,&c,4);
	c = 0;
	
	return ret_r;
}

int button_close (struct inode *n, struct file *fd)
{
	return 0;
}

struct file_operations button_ops ={
	.open = button_open,
	.read = button_read,
	.release = button_close,
};

struct miscdevice misc_button ={
	.minor = 200,
	.name = "button",
	.fops = &button_ops,
};

int key1_probe(struct device *dev)	//��Ҫ������ ע������豸��linux��, ��button_interrupt_waitqueue:button.c:button_init һ��
{

	int ret;	
	printk("init_key1\n");
	printk(KERN_EMERG "irq_init_start\n");

	//��linux����һ�������豸����,
	//��ʵ���ǹ���һ�����豸��Ϊ200���豸���������豸Ϊ10���ַ��豸����,
	//�Զ����ɶ�Ӧ�߼��豸�ļ���ӳ��
	misc_register(&misc_button);

	//��ʼ���ȴ�����wq1
	init_waitqueue_head(&wq1);

	//ע���жϴ������
	//IRQ_EINT(16):�жϺ�, button_inter:�жϴ�����, flags:IRQF_TRIGGER_FALLING��ʾ�½��ش����ж�,
	//button1:�жϵ�����, 1:�жϺ�irq_desc����ع�������жϵ��ж��¼�id��,�Ӷ�����ʹ��ͬһ���жϺ���ĸ����ж��¼�(��ҪΪ�����жϷ���)
	ret = request_irq(IRQ_EINT(16),button_inter,IRQF_TRIGGER_FALLING,"button1",(void *)1);	

	//����Ӳ����ʼ��
	hw_init();

	printk(KERN_EMERG "irq_init_complete\n");

    return 0;
}

int key1_remove (struct device *dev)	//��Ҫ�����Ǵ�linux�� ж���豸,��button_interrupt_waitqueue:button.c:button_exit һ��
{						
	//��linuxж��һ�������豸����,
	misc_deregister(&misc_button);

	//ע���жϴ�����
	free_irq(IRQ_EINT(16),(void *)1);	//irgno:�жϺ�,1:irq_desc����豸��

    return 0;
}

struct device_driver key1_driver = {
    .name = "key1_dev",		//�����豸ƥ�亯��mach ƥ�������
    .bus = &key_bus_type,	
    .probe = key1_probe,	//������key_bus_type mach�ɹ��� ���� ����
    .remove = key1_remove,	//���豸��Ϣ ��������ע��ʱ, ���� ������Ϣ ��������ע��ʱ ������õĺ���
};

int key1_driver_init(void)				//ģ���ʼ��
{
	int ret;
	
	ret = driver_register(&key1_driver);	//��ʾģ��ĳ�ʼ�� �� ������key_bus_type��������Ϣ,������ ע������豸��linux��
	
	return ret;
}


void key1_driver_exit(void)
{
	driver_unregister(&key1_driver);	// ������key_bus_type ж��������Ϣ
}


module_init(key1_driver_init);
module_exit(key1_driver_exit);
