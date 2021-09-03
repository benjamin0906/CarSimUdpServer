#include <pthread.h>
#include "Shared.h"

pthread_mutex_t MutexEngaged;
pthread_mutex_t MutexRefSpeed;
pthread_mutex_t MutexRefSWA;
pthread_mutex_t MutexCurrSpeed;
pthread_mutex_t MutexCurrSWA;

static uint8 Engaged;
static int16 CurrentSpeed;
static int16 CurrentSWA;
static int16 RefSpeed;
static int16 RefSWA;

void Shared_Init(void);
uint8 Shared_GetEngaged(void);
int16 Shared_GetCurrSpeed(void);
int16 Shared_GetCurrSWA(void);
int16 Shared_GetRefSpeed(void);
int16 Shared_GetRefSWA(void);

void Shared_SetEngaged(uint8);
void Shared_SetCurrSpeed(int16);
void Shared_SetCurrSWA(int16);
void Shared_SetRefSpeed(int16);
void Shared_SetRefSWA(int16);


void Shared_Init(void)
{
    pthread_mutex_init(&MutexEngaged, NULL);
    pthread_mutex_init(&MutexRefSpeed, NULL);
    pthread_mutex_init(&MutexRefSWA, NULL);
    pthread_mutex_init(&MutexCurrSpeed, NULL);
    pthread_mutex_init(&MutexCurrSWA, NULL);
}


uint8 Shared_GetEngaged(void)
{
    uint8 Ret;
    pthread_mutex_lock(&MutexEngaged);
    Ret = Engaged;
    pthread_mutex_unlock(&MutexEngaged);
    return Ret;
}

int16 Shared_GetCurrSpeed(void)
{
    int16 Ret;
    pthread_mutex_lock(&MutexCurrSpeed);
    Ret = CurrentSpeed;
    pthread_mutex_unlock(&MutexCurrSpeed);
    return Ret;
}

int16 Shared_GetCurrSWA(void)
{
    int16 Ret;
    pthread_mutex_lock(&MutexCurrSWA);
    Ret = CurrentSWA;
    pthread_mutex_unlock(&MutexCurrSWA);
    return Ret;
}

int16 Shared_GetRefSpeed(void)
{
    int16 Ret;
    pthread_mutex_lock(&MutexRefSpeed);
    Ret = RefSpeed;
    pthread_mutex_unlock(&MutexRefSpeed);
    return Ret;
}

int16 Shared_GetRefSWA(void)
{
    int16 Ret;
    pthread_mutex_lock(&MutexRefSWA);
    Ret = RefSWA;
    pthread_mutex_unlock(&MutexRefSWA);
    return Ret;
}

void Shared_SetEngaged(uint8 ArgEngaged)
{
    pthread_mutex_lock(&MutexEngaged);
    Engaged = ArgEngaged;
    pthread_mutex_unlock(&MutexEngaged);
}

void Shared_SetCurrSpeed(int16 Speed)
{
    pthread_mutex_lock(&MutexCurrSpeed);
    CurrentSpeed = Speed;
    pthread_mutex_unlock(&MutexCurrSpeed);
}

void Shared_SetCurrSWA(int16 SWA)
{
    pthread_mutex_lock(&MutexCurrSWA);
    CurrentSWA = SWA;
    pthread_mutex_unlock(&MutexCurrSWA);
}

void Shared_SetRefSpeed(int16 Speed)
{
    pthread_mutex_lock(&MutexRefSpeed);
    RefSpeed = Speed;
    pthread_mutex_unlock(&MutexRefSpeed);
}

void Shared_SetRefSWA(int16 SWA)
{
    pthread_mutex_lock(&MutexRefSWA);
    RefSWA = SWA;
    pthread_mutex_unlock(&MutexRefSWA);
}

