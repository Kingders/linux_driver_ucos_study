/***************************************
*fifo 特点:
*	同一时间,至少1个以O_WRONLY模式打开fifo,至少1个以O_RDONLY模式打开fifo,
*	如果进程都以同一个模式打开,那么都进程都被阻塞在打开函数里.
*
*
*
*
****************************************/


#include <unistd.h>	//getpid()
#include <sys/types.h>	//getpid() open() mkfifo()
#include <sys/stat.h>	//open() mkfifo()
#include <fcntl.h>	//open()

#include <stdio.h>

#define MSDATA		"hello"		//父给子进程数据
#define MSDATA_SIZE	sizeof(MSDATA)		//计算字符串字节数,自动多算一个字符串结束符NULL

#define SMDATA0		"jiuhygfd"		//子给父进程数据
#define SMDATA1		"hahahaha"		//子给父进程数据
#define SMDATA2		"bbbbbbbb"		//子给父进程数据
#define SMDATA_SIZE	sizeof(SMDATA0)		//计算字符串字节数,自动多算一个字符串结束符NULL

#define FIFOPATH	"./fifo1"

int main (void)
{
	pid_t hpid; //getpid获得
	pid_t pid; //fork返回
	char rbuffer[20];
	
	int fifofd;
	char *path;

	/**** hostpid ****/
	hpid = getpid();	
	printf("host pid %d\n\r",((int)hpid));
	printf("\n\r");

	/**** mkfifo() ****/
	
	path = FIFOPATH;
	mkfifo(path,0666);	//0666 是用户一类权限值

	/**** fifo write ****/
	fifofd = open(path,O_WRONLY);
	write(fifofd,MSDATA,MSDATA_SIZE);	//注意write特色,hello只有5个字节,
						//如果在输入字节数参数天6,默认第6个字节填上NULL
	return 0;
}
