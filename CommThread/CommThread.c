#include "CommThread_Types.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *CommThreadFunc(void *vargp);

void SetupThread(void)
{
    pthread_t Thread;
    pthread_create(&Thread, NULL, &CommThreadFunc, NULL);
    pthread_join(Thread, NULL);
}

void *CommThreadFunc(void *vargp)
{
    while(1)
{
    sleep(1);
    printf("This is from the thread\n");
}
    return 0;
}
