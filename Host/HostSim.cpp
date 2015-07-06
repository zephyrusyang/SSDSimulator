#include "HostSim.h"
#include <stdio.h>

HostSim::HostSim(){
  printf("HostSim:Create!\n");
}

HostSim::~HostSim(){
  printf("HostSim:Destory!\n");
}

void HostSim::SendNCQ(){
  printf("SendNCQ!\n");
}

void HostSim::SendPIO(){
  printf("SendPIO!\n");
}

void HostSim::SendDMA(){
  printf("SendDMA!\n");
}

void HostSim::SendDownloadMicrocode(){
  printf("SendDownloadMicrocode!\n");
}

void HostSim::SendSMART(){
  printf("SendSMART!\n");
}


