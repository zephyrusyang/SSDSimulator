/**
 * HostSim.h
 *
 */


#ifndef HOST_SIM_H
#define HOST_SIM_H

class HostSim{
public:
  HostSim();
  ~HostSim();
  void SendNCQ();
  void SendPIO();
  void SendDMA();
  void SendDownloadMicrocode();
  void SendSMART();
};

#endif
