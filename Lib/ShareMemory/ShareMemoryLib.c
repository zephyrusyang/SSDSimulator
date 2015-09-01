#include "ShareMemoryLib.h"

/* MACRO */
#define SHM_SRAM_FILE        "../ShareFile/SHM_SRAM"
#define SHM_DRAM_ZONE1_FILE  "../ShareFile/SHM_DRAM_ZONE1"
#define SHM_DRAM_ZONE2_FILE  "../ShareFile/SHM_DRAM_ZONE2"
#define SHM_DRAM_ZONE3_FILE  "../ShareFile/SHM_DRAM_ZONE3"

#define PROJ_CHAR    ((char)'x')

#define SHMSIZE      (2048*5)

unsigned char g_pucBuf[SHMSIZE];

/* FUNCTION */
bool ShareMemory_CreateHandler(ShareMemoryType_e eShareMemoryType, bool bIsReadOnly, ShareMemory_t* ptShareMemory){
  key_t    tKey = -1;
  int      iShmId = -1;
  void*    pvShmAddr = NULL;
  uint32_t uiShmSize = 0;

  /*******************************/
  /* generation of key           */
  /*******************************/
  switch(eShareMemoryType){
    case SHM_TYPE_SRAM:
      tKey = ftok(SHM_SRAM_FILE, PROJ_CHAR);
      break;
    case SHM_TYPE_DRAM_ZONE1:
      tKey = ftok(SHM_DRAM_ZONE1_FILE, PROJ_CHAR);
      break;
    case SHM_TYPE_DRAM_ZONE2:
      tKey = ftok(SHM_DRAM_ZONE2_FILE, PROJ_CHAR);
      break;
    case SHM_TYPE_DRAM_ZONE3:
      tKey = ftok(SHM_DRAM_ZONE3_FILE, PROJ_CHAR);
      break;
    default:
      break;
  }
  if(-1 == tKey){
    perror("ftok()");
    return false;
  }

  /*******************************/
  /* get share memory's ID       */
  /*******************************/
  if(bIsReadOnly){
    iShmId = shmget(tKey, SHMSIZE, 0);
  }else{
    iShmId = shmget(tKey, SHMSIZE, IPC_CREAT|0600);
    if(-1 == iShmId){
        printf("can not create\n");
        iShmId = shmget(tKey, SHMSIZE, IPC_EXCL|0600);
    }
  }
  if(-1 == iShmId){
    perror("shmget()");
    return false;
  }

  /*******************************/
  /* get share memory's Address  */
  /*******************************/
  if(bIsReadOnly){
    pvShmAddr = shmat(iShmId, NULL, SHM_RDONLY);
  }else{
    pvShmAddr = shmat(iShmId, NULL, 0);
  }
  if((char*)-1 == pvShmAddr){
      perror("shmat()");
      return false;
  }

  /*******************************/
  /* Store Memory's Manage Data  */
  /*******************************/
  ptShareMemory->tKey = tKey;
  ptShareMemory->iShmId = iShmId;
  ptShareMemory->pvShmAddr= pvShmAddr;
  ptShareMemory->uiShmSize= SHMSIZE;

  return true;
}

void ShareMemory_RemoveHandler(ShareMemory_t* ptShareMemory){
  if(NULL == ptShareMemory){
    return;
  }
  if(-1 == shmctl(ptShareMemory->iShmId, IPC_RMID, NULL)){
    perror("shmctl()");
  }
  return;
}
