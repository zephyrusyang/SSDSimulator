#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <semaphore.h>
#include <pthread.h>

#include "startup.h"
#include "configCPU.h"

void *CPUSimThread_Func(void *ptCPU_Sim_Thread){
    CPU_Sim_Thread_t *ptRiv = (CPU_Sim_Thread_t*)ptCPU_Sim_Thread;

    /* get process id and thread id */
    ptRiv->process_id = getpid();
    ptRiv->thread_id = pthread_self();

    /* sync: tell parent thread that I am ready to Initialize */
    sem_post(&ptRiv->sync);

    /* Init stage: write my letter */
    sem_wait(&ptRiv->start);
    printf("new CPU[%03d][%03d] created!\n", ptRiv->process_id, ptRiv->thread_id);
    putchar(ptRiv->letter);
    putchar('\n');
    ptRiv->ptMainFunc();

    /* sync: tell parent thread that I amd ready to start */
    sem_post(&ptRiv->sync);

    /* start stage: run CPU main */
    //    sem_wait(&ptRiv->start);
    //    putchar(ptRiv->letter);

    /* done */
    return (void*) NULL;
}

#define CPU_MAX (16)
CPUMainFunc_t g_ptCPUMainFunc[CPU_MAX];

int main(void){
    int               ret, i;
    CPU_Sim_Thread_t* ptCPU_Sim_Thread;
    char              cHello[128] = "Hello World!\n";

    /* Load CPU configure */
    uint8_t ucCPUNum = 0;
    memset(g_ptCPUMainFunc, 0x00, sizeof(g_ptCPUMainFunc));
    configCPU_load(sizeof(g_ptCPUMainFunc)/sizeof(CPUMainFunc_t), 
		   g_ptCPUMainFunc, 
                   &ucCPUNum);

    /* Initialize thread data */
    printf("create %d CPU Sim threads!\n", ucCPUNum);
    ptCPU_Sim_Thread = calloc(sizeof(CPU_Sim_Thread_t), ucCPUNum);
    if(NULL == ptCPU_Sim_Thread){
        perror("calloc()");
	exit(EXIT_FAILURE);
    }

    for(i = 0; i < ucCPUNum; i++){
        ptCPU_Sim_Thread[i].letter = cHello[i];
        ptCPU_Sim_Thread[i].ptMainFunc = g_ptCPUMainFunc[i];
	sem_init(&ptCPU_Sim_Thread[i].sync, 0, 0);
	sem_init(&ptCPU_Sim_Thread[i].start, 0, 0);
	ret = pthread_create(&ptCPU_Sim_Thread[i].thread_id, NULL, CPUSimThread_Func, (void *)(&ptCPU_Sim_Thread[i]));
	if(0 != ret){
	    fprintf(stderr, "pthread_create() #%0d failed for %i", i, ret);
	    exit(EXIT_FAILURE);
	}
    }

    /* synchronization */
    for(i = 0; i < strlen(cHello); i++){
	sem_wait(&ptCPU_Sim_Thread[i].sync);
    }

    /* let thread do his job */
    for(i = 0; i < strlen(cHello); i++){
	sem_post(&ptCPU_Sim_Thread[i].start);
	sem_wait(&ptCPU_Sim_Thread[i].sync);
    }

    /* join */
    for(i = 0; i < strlen(cHello); i++){
        pthread_join(ptCPU_Sim_Thread[i].thread_id, NULL);
	sem_destroy(&ptCPU_Sim_Thread[i].sync);
	sem_destroy(&ptCPU_Sim_Thread[i].start);
    }

    free(ptCPU_Sim_Thread);
    exit(EXIT_SUCCESS);
}
