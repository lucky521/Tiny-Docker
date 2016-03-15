#include <unistd.h>
#include <stdio.h>
int main()
{
	int pid = fork();
	if(pid == 0)
	{
		printf("child process %d start.\n", getpid());
		for(;;);
		printf("child process %d stop.\n", getpid());
	}
	printf("parent process %d start.\n", getpid());
	for(;;);
	printf("parent process %d stop.\n", getpid());
	return 0;
}
