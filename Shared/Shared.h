#include "types.h"

extern void Shared_Init(void);
extern uint8 Shared_GetEngaged(void);
extern int16 Shared_GetCurrSpeed(void);
extern int16 Shared_GetCurrSWA(void);
extern int16 Shared_GetRefSpeed(void);
extern int16 Shared_GetRefSWA(void);

extern void Shared_SetEngaged(uint8);
extern void Shared_SetCurrSpeed(int16);
extern void Shared_SetCurrSWA(int16);
extern void Shared_SetRefSpeed(int16);
extern void Shared_SetRefSWA(int16);
