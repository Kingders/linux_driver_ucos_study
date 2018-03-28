obj-m := adc1.o
KERNEL_DIR := /home/infortech-ubuntu-1404/SAMA5D4/kernel/kernel1/linux-at91-master 
all:
	make -C $(KERNEL_DIR) M=$(PWD) modules  CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
#	arm-linux-gnueabihf-gcc getevent.c getevent.h -I ./ -o getevent		//Ô´ÂëËð»µ
	cp adc1.ko /home/infortech-ubuntu-1404/tftpboot
clean:
	rm -f *.ko *.o *.mod.o *.symvers *.bak *.order
.PHONY:clean  
