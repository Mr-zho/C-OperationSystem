#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pthread_t tid = pthread_self();
	printf("tid = %ld\n", tid);	
	pid_t pid  = getpid();
	printf("pid = %d\n", pid);	
	
	return 0;
}
