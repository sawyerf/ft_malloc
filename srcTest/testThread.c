#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <pthread.h>
 
int g = 0;
 
void *myThreadFun(void *vargp)
{
	void *addr;

	for (int i = 0; i < 50; i++) {
		addr = malloc(50);
		bzero(addr, 50);
		addr = realloc(addr, 50 + i % 10);
		bzero(addr, 50 + i % 10);
		if (!(i % 3)) free(addr);
		addr = calloc(50, sizeof(int));
		bzero(addr, 50);
		//addr = reallocarray(addr, 50 + i % 10, sizeof(int));
		//bzero(addr, 50 + i % 10);
		printf("Thread: index=%d\n", i);
	}
}
 
int main()
{
	int i;
	pthread_t tid;

	for (i = 0; i < 5; i++)
		pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
		pthread_exit(NULL);
	return 0;
}
