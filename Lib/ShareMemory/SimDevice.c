/* 
   This program is one of the implementations for shared memory
   Device side
 */

#include "ShareMemoryLib.h"

int main(int argc, char* argv[]){
  ShareMemory_t tShareMemoryHandler;
  ShareMemory_CreateHandler(SHM_TYPE_DRAM_ZONE1, false, &tShareMemoryHandler);

  printf("Device => key:0x%x, shmid:0x%x, shmaddr:0x%x, shmsize=%d\n", 
	 tShareMemoryHandler.tKey,
	 tShareMemoryHandler.iShmId,
	 tShareMemoryHandler.pvShmAddr,
	 tShareMemoryHandler.uiShmSize);

  ShareMemory_RemoveHandler(&tShareMemoryHandler);

  return 0;
}

