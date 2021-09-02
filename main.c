#include <stdio.h>
#include "types.h"
#include <pthread.h>
#include <signal.h>

extern void *CommThreadFunc(void* var);


int main()
{
    pthread_t CommThread;
    pthread_mutex_t Mutex;

    if(pthread_mutex_init(&Mutex, NULL) == 0)
    {
    	pthread_create(&CommThread, NULL, &CommThreadFunc, &Mutex);
	pthread_detach(CommThread);
	pthread_join(CommThread, NULL);
	sleep(30);
    }

    return 0;
}
