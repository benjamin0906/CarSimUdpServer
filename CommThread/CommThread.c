#include "CommThread_Types.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Utilities.h"
#include "Shared.h"

void *CommThreadFunc(void *var);

void *CommThreadFunc(void *var)
{
    struct sockaddr_in Server;
    struct sockaddr_in client;
    Server.sin_family = AF_INET;
    Server.sin_port = Swap16(9999);
    Server.sin_addr.s_addr = Swap32(0xC0A80002);
    int32 s = 0;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s >= 0)
    {
        if(bind(s, (struct sockaddr *)&Server, sizeof(Server)) >= 0)
        {
            int Namelen = sizeof(Server);
            getsockname(s, (struct sockaddr *) &Server, &Namelen);
            printf("Port assigned is %d\n", ntohs(Server.sin_port));

            uint32 ClientAddrSize = sizeof(client);
            uint8 buff[8];
            uint8 SeqCntr = 1;
            while(1)
            {
                uint32 RxLen = recvfrom(s, buff, sizeof(buff), 0, (struct sockaddr *)&client, &ClientAddrSize);
                if(RxLen > 0)
                {
                    for(int i=0; i < RxLen; i++) printf("%x ", buff[i]);
                    printf("\n");

                    /* Checking the sequence counter */
                    if(buff[1] != SeqCntr)
                    {
                        printf("SeqCntr is wrong\n");
                        SeqCntr = buff[1];
                    }
                    switch(buff[0])
                    {
                    case Msg_StateReq:
                    {
                        dtStateMsg Msg;
                        Msg.Fields.MsgType = Msg_State;
                        Msg.Fields.SeqCntr = SeqCntr;
                        Msg.Fields.Engaged = Shared_GetEngaged();
                        Msg.Fields.CurrentSpeed = Shared_GetCurrSpeed();
                        Msg.Fields.CurrentSWA = Shared_GetCurrSWA();
                        sendto(s, &Msg.Byte, sizeof(dtStateMsg), 0, (struct sockaddr *)&client, ClientAddrSize);
                        break;
                    }
                    case Msg_SetEngage:
                        
                        break;
                    case Msg_SetReferences:
                        
                        break;
                    default:
                        break;
                    }

                    /* Setting the SeqCntr to the next one */
                    SeqCntr++;
                    if(SeqCntr == 0) SeqCntr++;
                }
            }
        }
        else printf("Problem with binding\n");
    }
    else printf("socket creating error: %d\n", s);

    return 0;
}
