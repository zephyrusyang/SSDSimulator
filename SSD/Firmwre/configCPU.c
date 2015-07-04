#include "configCPU.h"

/* for test */
void CPU_00_main(void){
    printf("\nI am CPU 0!\n");
}
void CPU_01_main(void){
    printf("\nI am CPU 1!\n");
}
void CPU_02_main(void){
    printf("\nI am CPU 2!\n");
}
void CPU_03_main(void){
    printf("\nI am CPU 3!\n");
}
void CPU_04_main(void){
    printf("\nI am CPU 4!\n");
}
void CPU_05_main(void){
    printf("\nI am CPU 5!\n");
}
void CPU_06_main(void){
    printf("\nI am CPU 6!\n");
}
void CPU_07_main(void){
    printf("\nI am CPU 7!\n");
}
void CPU_08_main(void){
    printf("\nI am CPU 8!\n");
}
void CPU_09_main(void){
    printf("\nI am CPU 9!\n");
}
void CPU_10_main(void){
    printf("\nI am CPU 10!\n");
}
void CPU_11_main(void){
    printf("\nI am CPU 11!\n");
}

#define CPU_NUM  (12)

/* config every CPU's main function here */
void configCPU_load(uint8_t ucMaxCPUNum, CPUMainFunc_t* ptMainFunc, uint8_t* pucSetCPUNum){
    if((NULL == ptMainFunc)||(NULL == pucSetCPUNum)){
        printf("Error: configCPU ptMainFunc[0x%08x], pucSetCPUNum[0x%08x]!",ptMainFunc,pucSetCPUNum);
	return;
    }
    if(CPU_NUM > ucMaxCPUNum){
        printf("Error: Max CPU number less than %d!", CPU_NUM);
	return;
    }

    ptMainFunc[0]  = CPU_00_main;
    ptMainFunc[1]  = CPU_01_main;
    ptMainFunc[2]  = CPU_02_main;
    ptMainFunc[3]  = CPU_03_main;
    ptMainFunc[4]  = CPU_04_main;
    ptMainFunc[5]  = CPU_05_main;
    ptMainFunc[6]  = CPU_06_main;
    ptMainFunc[7]  = CPU_07_main;
    ptMainFunc[8]  = CPU_08_main;
    ptMainFunc[9]  = CPU_09_main;
    ptMainFunc[10] = CPU_10_main;
    ptMainFunc[11] = CPU_11_main;
    *pucSetCPUNum = 12;

    return;
}
