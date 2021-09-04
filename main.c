#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include <pthread.h>
#include <unistd.h>
#include "Shared.h"
#include <math.h>

extern void *CommThreadFunc(void* var);

int main(uint32 argc, uint8 **argv)
{
    /* Check if there is an argument which at least the first charackter is a number */
    if((argc == 2) && ((*argv[1] >= '0') && (*argv[1] <= '9')))
    {
        uint16 Speed = round((float32)atoi(argv[1])*250/9);
        printf("%d, %d\n", Speed, atoi(argv[1])*250/9);
        pthread_t CommThread;

        pthread_create(&CommThread, NULL, &CommThreadFunc, NULL);
        pthread_detach(CommThread);
        pthread_join(CommThread, NULL);
        sleep(30);
        printf("RefSpeed:%i RefSWA:%i\n", Shared_GetRefSpeed(), Shared_GetRefSWA());
    }
    else
    {
        printf("Wrong argument!\n");
        return -1;
    }
    return 0;
}
