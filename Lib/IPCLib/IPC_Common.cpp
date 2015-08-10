#include "IPC_Common.h"


ShareMemory_t* IPC_GetShareMemory(char* pucShmPath, char ucProjChar, bool bIsReadOnly){
  ShareMemory* ptShareMemory;
  key_t key;
  int   shmid;
  char* shmaddr;

  /* generation of key */
  key = ftok(pucShmPath, ucProjChar);
  if(-1 == key){
    perror("ftok()");
    return NULL;
  }

  /* get share memory's ID */
  if(bIsReadOnly){
    sleep(2); /* wait for write side */
    shmid = shmget(key, SHMSIZE, 0);
  }else{
    shmid = shmget(key, SHMSIZE, IPC_CREAT|IPC_EXCL|0600);
  }
  if(-1 == shmid){
    perror("shmget()");
    return NULL;
  }
  /* get share memory's Address */
  if(bIsReadOnly){
    shmaddr = shmat(shmid, NULL, SHM_RDONLY);
  }else{
    shmaddr = shmat(shmid, NULL, 0);
    sleep(2); /* wait for read side*/
  }
  if((char*)-1 == shmaddr){
    perror("shmat()");
    return NULL;
  }

  /* get memory for Manage Data's share memory */
  ptShareMemory = calloc(sizeof(ShareMemory_t), 1);
  if(NULL == ptShareMemory){
    perror("calloc()");
    return NULL;  
  }

  ptShareMemory->tKey = key;
  ptShareMemory->uiShmId = shmid;
  ptShareMemory->pucShmAddr= shmaddr;

  return ptShareMemory;
}

