gcc -Wall -o IPC_HostRead.exe IPC_HostRead.c -lm
gcc -Wall -o IPC_HostWrite.exe IPC_HostWrite.c -lm
gcc -Wall -o IPC_DeviceRead.exe IPC_DeviceRead.c -lm
gcc -Wall -o IPC_DeviceWrite.exe IPC_DeviceWrite.c -lm
(./IPC_HostWrite.exe&) ; ./IPC_DeviceRead.exe > H2D.dat
(./IPC_DeviceWrite.exe&) ; ./IPC_HostRead.exe > D2H.dat
