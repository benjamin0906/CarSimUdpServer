#include "types.h"

enum eMsgTypes
{
    Msg_StateReq,
    Msg_State,
    Msg_SetEngage,
    Msg_SetReferences
};

typedef union
{
    struct
    {
        uint8 MsgType;
        uint8 SeqCntr;
        uint8 Engaged;
        int16 CurrentSpeed;
        int16 CurrentSWA;
    } Fields;
    uint8 Byte;
} dtStateMsg;

typedef union
{
    struct
    {
        uint8 MsgType;
        uint8 SeqCntr;
        int16 RefSpeed;
        int16 RefSWA;
    } Fields;
    uint8 Byte;
} dtRefsMsg;
