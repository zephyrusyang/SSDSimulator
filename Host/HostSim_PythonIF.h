#ifdef __cplusplus
extern "C"{
#endif
  void* HostSim_Create();
  void HostSim_Delete(void* p);
  void HostSim_SendNCQ(void *p);
  void HostSim_SendDMA(void *p);
  void HostSim_SendPIO(void *p);
  void HostSim_SendDownloadMicrocode(void *p);
  void HostSim_SendSMART(void *p);
#ifdef __cplusplus
}
#endif
