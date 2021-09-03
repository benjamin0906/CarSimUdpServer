#include <stdio.h>
#include "types.h"
#include <pthread.h>
#include <unistd.h>
#include "Shared.h"

extern void *CommThreadFunc(void* var);

int main()
{
    pthread_t CommThread;

    pthread_create(&CommThread, NULL, &CommThreadFunc, NULL);
    pthread_detach(CommThread);
    pthread_join(CommThread, NULL);
    sleep(30);
    printf("RefSpeed:%i RefSWA:%i\n", Shared_GetRefSpeed(), Shared_GetRefSWA());

    return 0;
}
