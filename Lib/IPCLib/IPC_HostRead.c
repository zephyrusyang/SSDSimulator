/* 
   This program is one of the implementations for shared memory
   Host side
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "IPC_Common.h"

ShareMemory* s_ptD2H_ShareMemory;
ShareMemory* s_ptH2D_ShareMemory;

uint32_t HostIPC_Init(void){
  /* get H2D's ShareMemory for wirte */
  s_ptH2D_ShareMemory = IPC_GetShareMemory(H2D_FILE_PATH, PROJ_CHAR, false);
  if(NULL == s_ptH2D_ShareMemory){
    perror("H2D IPC_GetShareMemory()");
    return 1;
  }
  
  /* get D2H's ShareMemory for read */
  s_ptD2H_ShareMemory = IPC_GetShareMemory(D2H_FILE_PATH, PROJ_CHAR, true);
  if(NULL == s_ptD2H_ShareMemory){
    perror("D2H IPC_GetShareMemory()");
    return 1;
  }

  return 0;
}

void HostIPC_Destory(void){
  /* free H2D Memory */
  if(NULL != s_ptH2D_ShareMemory){
    free(s_ptH2D_ShareMemory);
    s_ptH2D_ShareMemory = NULL;
  }

  /* free D2H Memory */
  if(NULL != s_ptD2H_ShareMemory){
    free(s_ptD2H_ShareMemory);
    s_ptD2H_ShareMemory = NULL;
  }
}

static uint8_t s_pucReadBuf[SHMSIZE - sizeof(unint32_t)];
static void *ReadHandler_Main(){
  uint32_t uiReadSize;
  while(1){
      uiReadSize = HostIPC_Read(sizeof(s_pucReadBuf), s_pucReadBuf);
      print TBD
  }
}

uint32_t HostIPC_Start(){
  
  return 0;
}

uint32_t HostIPC_Write(uint32_t uiSize, uint8_t* pucBuf){
  uint32_t uiSentSize = 0;
  
  /* check data size */
  if((uiSize + sizeof(uint32_t)) > SHMSIZE){
    printf("HostIPC_Write's size error()");
    return 1;
  }

  /* TBD: Lock */

  /* check if the perivous data has been read */
  memscpy(&uiSendSize, s_ptH2D_ShareMemory.pucShmAddr, sizeof(uint32_t));
  if(0 != uiSentSize){
    return 2;
  }
  
  /* copy new size to shared memory */
  memcpy(s_ptH2D_ShareMemory.pucShmAddr, &uiSize, sizeof(uint32_t));

  /* copy new data to shared memory( TBD: make the share buffer into ring structure ) */
  uint32_t uiDataStartOfs = sizeof(uint32_t);
  int i;
  for(i; i<uiSize; i++){
    s_ptH2D_ShareMemory[uiDataStartOfs+i].pucShmAddr = pucBuf[i];
  }

  /* TBD: UnLock */

  return 0;
}


uint32_t HostIPC_Read(uint32_t uiSize, uint8_t* pucBuf){
  uint32_t uiReceivedSize;

  /* check data size */
  if(uiSize > (SHMSIZE - sizeof(uint32_t))){
    printf("HostIPC_Read's size error()");
    return 0;
  }

  /* TBD: Lock */

  /* copy size */
  memscpy(&uiReceivedSize, s_ptD2H_ShareMemory.pucShmAddr, sizeof(uint32_t));
  if(0 == uiReceivedSize){
    return 0;
  }

  /* copy data */
  uint32_t uiDataStartOfs = sizeof(uint32_t);
  int i;
  for(i; i<uiReceivedSize; i++){
    pucBuf[i] = s_ptD2H_ShareMemory[uiDataStartOfs+i].pucShmAddr;
  }

  /* clear memory */
  memset(s_ptD2H_ShareMemory.pucShmAddr, 0x00, SHMSIZE);

  /* TBD: UnLock */

  return uiReceivedSize;
}

