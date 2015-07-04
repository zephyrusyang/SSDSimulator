#ifndef CONFIG_CPU_H
#define CONFIG_CPU_H

#include "startup.h"

extern void configCPU_load(uint8_t ucMaxCPUNum, CPUMainFunc_t* ptMainFunc, uint8_t* pucSetCPUNum);

#endif /* CONFIG_CPU_H */
