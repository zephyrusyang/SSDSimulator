/* 
   This program is one of the implementations for shared memory
   Write side
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "IPC_Common.h"

int main(int argc, char* argv[]){
  key_t key;
  int   shmid;
  char* shmaddr;
  int i;

  /* generation of key */
  key = ftok(D2H_FILE_PATH,PROJ_CHAR);
  if(-1 == key){
    perror("write ftok()");
    return 1;
  }

  shmid = shmget(key, SHMSIZE, IPC_CREAT|IPC_EXCL|0600);
  if(-1 == shmid){
    perror("shmget()");
    return 1;
  }

  shmaddr = shmat(shmid, NULL, 0);
  if((char*)-1 == shmaddr){
    perror("shmat()");
    return 1;
  }

  for(i=0; i<SHMSIZE; i++){
    shmaddr[i] = i;
  }

  sleep(2);

  if(-1 == shmctl(shmid, IPC_RMID, NULL)){
    perror("shmctl()");
    return 1;
  }
  return 0;
}

