#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

extern struct bus_type key_bus_type;

struct device key1_dev = {
     .init_name = "key1_dev",
     .bus = &key_bus_type,	
};

int key1_device_init(void)
{
     int ret;
     ret = device_register(&key1_dev);		// ע��key1_dev��Ϣ�� ���� key_bus_type
     return ret;
     
}


int key1_device_exit(void)
{
	device_unregister(&key1_dev);		//������key_bus_type ж���豸��Ϣ
     return 0;
}

module_init(key1_device_init);
module_exit(key1_device_exit);
