#define _POSIX_C_SOURCE 200809L
#include "CommThread_Types.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Utilities.h"

pthread_t Thread;
pthread_mutex_t Mutex;

void *CommThreadFunc(void *var);

extern uint32 cntr;

void *CommThreadFunc(void *var)
{
    pthread_mutex_t *Mutex = (pthread_mutex_t*)var;

    struct sockaddr_in Server;
    struct sockaddr_in client;
    Server.sin_family = AF_INET;
    Server.sin_port = Swap16(9999);
    Server.sin_addr.s_addr = Swap32(0xC0A80002);
    int s = 0;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s >= 0)
    {
        char buf[32];
        if(bind(s, (struct sockaddr *)&Server, sizeof(Server)) >= 0)
        {
            int Namelen = sizeof(Server);
            getsockname(s, (struct sockaddr *) &Server, &Namelen);
            printf("Port assigned is %d\n", ntohs(Server.sin_port));

            uint32 ClientAddrSize = sizeof(client);
            while(1){
            if(recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&client, &ClientAddrSize) >= 0)
            {
                printf("received: %s\n", buf);
            }
}
        }
        else printf("Problem with binding\n");
    }
    else printf("socket creating error: %d\n", s);



/*// while(1)
pthread_mutex_lock(Mutex);
    for(int i=0; i<5; i++)
    {
        for(int j = 0; j< 0x7ffffff; j++);
        printf("Comm thread is me, %d\n", cntr);
    }
pthread_mutex_unlock(Mutex);*/
    return 0;
}
