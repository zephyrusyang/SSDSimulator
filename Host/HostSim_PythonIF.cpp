#include "HostSim_PythonIF.h"
#include "HostSim.h"

void* HostSim_Create(){
  return (void*)new HostSim();
}

void HostSim_Delete(void* p){
  delete (HostSim*)p;
}

void HostSim_SendNCQ(void *p){
  ((HostSim*)p)->SendNCQ();
}

void HostSim_SendDMA(void *p){
  ((HostSim*)p)->SendDMA();
}

void HostSim_SendPIO(void *p){
  ((HostSim*)p)->SendPIO();
}

void HostSim_SendDownloadMicrocode(void *p){
  ((HostSim*)p)->SendDownloadMicrocode();
}

void HostSim_SendSMART(void *p){
  ((HostSim*)p)->SendSMART();
}
