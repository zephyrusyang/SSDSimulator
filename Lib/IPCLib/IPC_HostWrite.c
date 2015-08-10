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

