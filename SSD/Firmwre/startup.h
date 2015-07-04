#ifndef STARTUP_H
#define STARTUP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <semaphore.h>
#include <pthread.h>

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long long uint64_t;

typedef void (*CPUMainFunc_t)(void);

typedef struct tagCPU_Sim_Thread_t{
    char           letter;
    pid_t          process_id;
    pthread_t      thread_id;
    CPUMainFunc_t  ptMainFunc;
    sem_t          sync;
    sem_t          start;
    uint32_t       DCCM_Size;
    uint8_t*       DCCM_StartAddr;
    uint32_t       ICCM_Size;
    uint8_t*       ICCM_StartAddr;
    uint8_t*       IPC;
}CPU_Sim_Thread_t;

#endif /* STARTUP_H */
