#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (void)
{
	int fd = 0;
	int dat = 0;

	fd = open("/dev/chardev0",O_RDWR);
	perror("open");
	read(fd,&dat,sizeof(int));
	perror("read");
	printf("read:dat is %d\n",dat);
	
	close(fd);
	return 0;
}




