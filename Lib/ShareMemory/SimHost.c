/* 
   This program is one of the implementations for shared memory
   Host side
 */

#include "ShareMemoryLib.h"

int main(int argc, char* argv[]){
    ShareMemory_t tShareMemoryHandler;
    ShareMemory_CreateHandler(SHM_TYPE_DRAM_ZONE1, false, &tShareMemoryHandler);

    printf("hello\n");
    printf("Host => key:0x%x, shmid:0x%x, shmaddr:0x16%x, shmsize=%d\n",
           tShareMemoryHandler.tKey,
           tShareMemoryHandler.iShmId,
           tShareMemoryHandler.pvShmAddr,
           tShareMemoryHandler.uiShmSize);

    unsigned char* pucBuf = tShareMemoryHandler.pvShmAddr;

    int i, j;
    for(i = 0; i < 100; i++){
        pucBuf[0] = 1;
        for(j = 0; j <= i+1; j++){
            pucBuf[j+2] = j;
        }

        pucBuf[1] = i+1;

        /* wait for device read  */
        while(pucBuf[0]){
            sleep(5);
        }
    }

    ShareMemory_RemoveHandler(&tShareMemoryHandler);

    return 0;
}

