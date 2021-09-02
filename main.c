#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "types.h"

typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed int int32;
extern void SetupThread(void);
uint16 Swap16(uint16 Num)
{
    return (Num >> 8 | Num << 8);
}

uint32 Swap32(uint32 Num)
{
    uint32 ret = Num << 24;
    ret |= (Num << 8)&0x00FF0000;
    ret |= (Num >> 8)&0x0000FF00;
    ret |= (Num >> 24)&0x000000FF;
    return ret;
}

int main()
{
    SetupThread();
/*
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
*/
    return 0;
}
