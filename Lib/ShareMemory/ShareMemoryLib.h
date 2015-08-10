#ifndef SHARE_MEMORY_COMMON_H
#define SHARE_MEMORY_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

typedef enum tagShareMemoryType_e{
  SHM_TYPE_SRAM,
  SHM_TYPE_DRAM_ZONE1,
  SHM_TYPE_DRAM_ZONE2,
  SHM_TYPE_DRAM_ZONE3,
}ShareMemoryType_e;

typedef struct tagShareMemory_t{
  ShareMemoryType_e eShareMemory_t;
  key_t             tKey;
  int               iShmId;
  void*             pvShmAddr; 
  uint32_t          uiShmSize;
}ShareMemory_t;

extern bool ShareMemory_CreateHandler(ShareMemoryType_e eShareMemoryType, bool bIsReadOnly, ShareMemory_t* ptShareMemory);
extern void ShareMemory_RemoveHandler(ShareMemory_t* ptShareMemory);

#endif /* SHARE_MEMORY_COMMON_H */
