#ifndef SHARE_MEMORY_COMMON_H
#define SHARE_MEMORY_COMMON_H


#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include "stdio.h"

typedef unsigned int uint32_t;

typedef enum tagShareMemoryType_e{
  SHM_TYPE_DCCM_CPU0,
  SHM_TYPE_DCCM_CPU1,
  SHM_TYPE_DCCM_CPU2,
  SHM_TYPE_DCCM_CPU3,
  SHM_TYPE_DCCM_CPU4,
  SHM_TYPE_DCCM_CPU5,
  SHM_TYPE_DCCM_CPU6,
  SHM_TYPE_DCCM_CPU7,
  SHM_TYPE_SRAM_AON,
  SHM_TYPE_SRAM_POFF,
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
