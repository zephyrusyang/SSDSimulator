# SSDSimulator
A Simulator for SSD development

* This simulator will provide a simulate hardware environment for SSD Firmware's development.
* Gmock will be used to link the sim-hareware I/F to make it easier to test the Firmware
* Python Script will be used to perform SATA/NVMe base interaction with Firmware.

# SSD Interface:
* NVMe, SATA, PCIe, eMMC will be support

# Common Hardwares:
* CPU: the CPU number and cache size can be set
* DRAM: the size of DRAM can be set
* SRAM: the size of SRAM can be set
* NVME Controler: handle the NVMe procotol
* SATA Controler: handle the SATA procotol
* PCIe Controler: handle the PCIe procotol
* eMMC Controler: handle the eMMC procotol
* Data Search Engine: A hardware engine to search host data that in the DRAM
* ECC Engine

# NAND chip:
We can set the following paramater of NAND packet
* bank number:
* chancel number:
* plane number:
* page size:
* type:SLC/MLC/TLC/3D
* cache in NAND: page number
* performance:tErase, tProgram
* Limitation time of the NAND: ??k

# Reference
[VSSIM: Virtual Machine based SSD Simulator](https://www.computer.org/csdl/proceedings/msst/2013/0217/00/06558443.pdf)


