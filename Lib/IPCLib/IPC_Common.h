#ifndef SHARE_MEMORY_COMMON_H
#define SHARE_MEMORY_COMMON_H

#define H2D_FILE_PATH "./H2D_MEM_FILE"
#define D2H_FILE_PATH "./D2H_MEM_FILE"
#define PROJ_CHAR    ((char)'x')

#define SHMSIZE      (2048*5)

typedef struct tagShareMemory_t{
  key_t tKey;
  int   uiShmId;
  char* pucShmAddr; 
}ShareMemory_t:

extern ShareMemory_t* IPC_GetShareMemory(char* pucShmPath, char ucProjChar, bool bIsReadOnly);

#endif /* SHARE_MEMORY_COMMON_H */
