/* 
   This program is one of the implementations for shared memory
   Device side
 */

#include "ShareMemoryLib.h"

int main(int argc, char* argv[]){
  ShareMemory_t tShareMemoryHandler;
  ShareMemory_CreateHandler(SHM_TYPE_DRAM_ZONE1, false, &tShareMemoryHandler);

  printf("Device => key:0x%x, shmid:0x%x, shmaddr:0x%16x, shmsize=%d\n", 
	 tShareMemoryHandler.tKey,
	 tShareMemoryHandler.iShmId,
     tShareMemoryHandler.pvShmAddr,
	 tShareMemoryHandler.uiShmSize);

  unsigned char* pucBuf = tShareMemoryHandler.pvShmAddr;

  int i, j;
  while(1){
      if( 0 != pucBuf[0] && 0 != pucBuf[1]){
          printf("round %d:\n", pucBuf[1]);
          for(i = 0; i <= pucBuf[1]; i++){
              printf("%d\n", pucBuf[i+2]);
          }
          printf("\n");
          if(100 == pucBuf[1]){
              break;
          }else{
              pucBuf[0] = 0;
              pucBuf[1] = 0;
          }
      }else{
          sleep(5);
      }
  }

  ShareMemory_RemoveHandler(&tShareMemoryHandler);

  return 0;
}

