/***************************************
*1,��������û�����ִ��exitע������ ���ֳ�����Ϣ:process: cxa_atexit.c:100: __new_exitfn: Assertion `l != ((void *)0)' failed.
*2,vfork()�󸸽��̵ı�������,���ڹ���ջ�ռ�,�ӽ��������,Ȼ��return�˳�,�ͷ���ջ,���µ�������ִ��ʱ,��ȡջ����,���Ѿ�����,
* 1��2������,Ҫ��vfork���ӽ��̽�������ʱҪ��exit()���˳�.
****************************************/


#include <unistd.h>	//fork() vfork() getpid() execl()
#include <sys/types.h>	//vfork() getpid() wait()
#include <stdlib.h>	//exit()
#include <sys/wait.h>	//wait()

#include <stdio.h>


int main (void)
{
	pid_t hpid; //getpid���
	pid_t pid; //fork����
	pid_t vpid; //vfork����

	int c = 0;	//����ջ�ռ�

	/**** getpid ****/
	hpid = getpid();	
	printf("host pid %d\n\r",((int)hpid));
	printf("\n\r");

	/**** fork wait execl****/
	pid = fork();	//�������̳ɹ�,�����̴������ӽ���pid,�ӽ��̴�����0, ʧ�ܷ���-1,
			//�ɹ���,ʵ���ǰ�ִ�д��붼������һ�ݵ��µ��ӽ���,�ӽ������Լ�������ջ�ռ�,���ӽ��̼���ִ�����´���		
	if(pid)		//���︸����ָ��ִ�д���,
	{
		wait(NULL);	//���̵ȴ�
				//�ȴ��ӽ�����ȫ��������ִ�и�����,����ӽ��̻���vfork,Ҳ�����ӽ��̵�����vfork���̽���
		hpid = getpid();
		c++;	
		printf("fork parent part host  pid %d\n\rfork parent part child pid %d c:%d\n\r\n\r",	\
			((int)hpid),((int)pid),c);
	}
	else		//���������ӽ���ָ��ִ�д���,
	{
		hpid = getpid();
		c++;
		execl("/bin/ls","ls","../",NULL);//�ļ�·��,arg0:ִ�г�������������ls,arg1:ִ�г���ʹ�ò���"../",û�и������ʱ���һ����NULL
						 //exec������fork()ʹ��,��Ҫ���vforkʹ��,��Ϊvfork������ջ�� 
		//���ʹ����execl(),�ӽ������������ݱ�ɾ��,�������µ�����	
		//ԭ���ӽ��̲�������Ҳ�Ͳ���ִ��,�Լ��ӽ��̺����vforkҲ����ִ��
		printf("fork child part host  pid %d c:%d\n\r\n\r",	\
			((int)hpid),c);
	}								
#if 1
	/**** vfork exit ****/
	vpid = vfork();	//�������̳ɹ�,������������,���ӽ����Ƚ���
			//�����̴������ӽ���pid,�ӽ��̴�����0, ʧ�ܷ���-1,
			//�ɹ���,ʵ���ǰ�ִ�д��붼������һ�ݵ��µ��ӽ���,���ӽ����븸���̹���ջ�ռ�,���ӽ��̼���ִ�����´��� 		
	if(vpid)		//���︸����ָ��ִ�д���,
	{
		hpid = getpid();
		//c++;	
		printf("vfork parent part host  pid %d\n\rvfork parent part child pid %d c:%d\n\r\n\r",	\
			((int)hpid),((int)vpid),c);
	}
	else		//���������ӽ���ָ��ִ�д���,
	{
		hpid = getpid();
		c++;	
		printf("vfork child part host  pid %d c:%d\n\r\n\r",	\
			((int)hpid),c);
		exit(0);	//�˳�vfork�ӽ���һ��Ҫ��exit()��ִ��,�����ú���� return 0
	}
#endif 

	return 0;
}
