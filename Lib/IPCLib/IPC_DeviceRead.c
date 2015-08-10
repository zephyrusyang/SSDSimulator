/* 
   This program is one of the implementations for shared memory
   Read side
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

int main(int argc, char* argv[]){
  key_t key;
  int   shmid;
  char* shmaddr;
  int i;

  /* generation of key */
  key = ftok(H2D_FILE_PATH, PROJ_CHAR);
  if(-1 == key){
    perror("ftok()");
    return 1;
  }

  shmid = shmget(key, SHMSIZE, 0);
  if(-1 == shmid){
    perror("shmget()");
    return 1;
  }

  shmaddr = shmat(shmid, NULL, SHM_RDONLY);
  if((char*)-1 == shmaddr){
    perror("shmat()");
    return 1;
  }

  for(i=0; i<SHMSIZE; i++){
    printf("Device Received From Host:%d!\n",(int)(shmaddr[i]));
  }

  return 0;
}

