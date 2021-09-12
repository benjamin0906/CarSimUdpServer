#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include <pthread.h>
#include <unistd.h>
#include "Shared.h"
#include <math.h>
#include <time.h>

static const uint16 Accel = 100; //100 cm/(s^2) = 1m/(s^2)
static const uint16 SWAVel = 698; //40°/s = 2000pi/9 mrad/s
static const uint16 SWAOscAmp = 1047; // 60° = 1047 mrad
static const uint16 SWAOscT = 1200; // [ms]

extern void *CommThreadFunc(void* var);

void SpeedHandler(void);
void SWAHandler(uint8 Engaged);

int main(uint32 argc, uint8 **argv)
{
    /* Check if there is an argument which at least the first charackter is a number */
    if((argc == 2) && ((*argv[1] >= '0') && (*argv[1] <= '9')))
    {
        int16 Speed = round((float32)atoi(argv[1])*250/9);
        uint32 LastRefFlagTime=0;

        Shared_SetRefSpeed(Speed);

        /* Initialize and start the thread that communicates via UDP */
        pthread_t CommThread;
        pthread_create(&CommThread, NULL, &CommThreadFunc, NULL);
        pthread_detach(CommThread);
        pthread_join(CommThread, NULL);
        while(1)
        {
            uint8 Engaged = Shared_GetEngaged();
            uint32 CurrTime = (uint32)((float32)clock()/(CLOCKS_PER_SEC/1000));
            if((Shared_GetRefFlag() != 0) || (Engaged == 0))
            {
                LastRefFlagTime = CurrTime;
                Shared_SetRefFlag(0);
            }
            if((CurrTime - LastRefFlagTime) > 2000)
            {
                fprintf(stderr, "Reference is late\n");
                Shared_SetEngaged(0);
                LastRefFlagTime = CurrTime;
            }
            SpeedHandler();
            SWAHandler(Engaged);
        }
    }
    else
    {
        printf("Wrong argument!\n");
        return -1;
    }
    return 0;
}

void SpeedHandler(void)
{
    static uint32 PrevTimestamp;

    /* Calculating the time difference from the last timestamp to now in [ms] */
    uint32 ClockDiff = (uint32)((float32)(clock() - PrevTimestamp)/(CLOCKS_PER_SEC/1000));

    /* Calculation the speed changing from the last timestamp */
    uint16 ChangedSpeed = ((uint32)Accel*ClockDiff)/1000;

    if(ChangedSpeed != 0)
    {
        int16 Spd = Shared_GetCurrSpeed();
        int16 RefSpd = Shared_GetRefSpeed();

        if(Spd > RefSpd) Spd -= ChangedSpeed;
        else Spd += ChangedSpeed;

        Shared_SetCurrSpeed(Spd);

        //printf("Speed: %d\n", Spd);
        /* Due to the discrete sampling and the number representation, a second ClockDiff is calculated
         * based on the ChangedSpeed. The Previous timestamp will be the "current time" whick is the sum
         * of the previous timestamp and the calculated time difference.
         */
        PrevTimestamp += ((uint32)ChangedSpeed*1000/Accel)*(CLOCKS_PER_SEC/1000);
    }
}

void SWAHandler(uint8 Engaged)
{
    static uint32 PrevTimestamp;

    /* Calculating the current time in [ms] */
    uint32 Clock = (uint32)((float32)clock()/(CLOCKS_PER_SEC/1000));

    /* To reduce the cycles that results the same, it calculates only if the time differs */
    if(PrevTimestamp != Clock)
    {
        int16 CurrSWA = Shared_GetCurrSWA();
        int16 CalcSWA = CurrSWA;

        if(Engaged == 0)
        {
            /* Because of the finite number representation with time the input for the sin() function would overflow
             * To prevent this only the remainder will be considered */
            uint32 TimeRemainder = Clock % SWAOscT;

            CalcSWA = (int16)SWAOscAmp*sinf(TimeRemainder*2*M_PI/SWAOscT);
        }
        else
        {
            int16 RefSWA = Shared_GetRefSWA();              //[mrad]
            uint32 TimeDiff = Clock - PrevTimestamp;        //[ms]
            int16 SWADiff = (uint32)SWAVel*TimeDiff/1000;  //[mrad]

            if(SWADiff > 0)
            {
                if(CurrSWA > RefSWA) CalcSWA = CurrSWA - SWADiff;
                else CalcSWA = CurrSWA + SWADiff;
            }
        }
        if(CalcSWA != CurrSWA)
        {
            Shared_SetCurrSWA(CalcSWA);
            PrevTimestamp = Clock;
        }
    }
}
