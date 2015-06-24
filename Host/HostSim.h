/**
 * HostSim.h
 *
 */


#ifndef HOST_SIM_H
#define HOST_SIM_H

class HostSim{
public:
  HostSim(void){};
  ~HostSim(void){};

  void SendNCQ(){};
  void SendPIO(){};
  void SendDMA(){};
  void SendDownloadMircocode(){};
  void SendSMART(){};
}

#endif
