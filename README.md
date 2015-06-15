# SSDSimulator
A Simulator for SSD development

A SSD is design on the following hareware.
This simulator provide a common hardware environment for SSD controler's development.
This simulator will link the hareware I/F with gmock in order to test the fireware
Interaction between host and device will be set by python script

# For the frontend
NVMe Proccessor: Handle the NVMe protocol
SATA/ATA/AHCI Proccessor: Handle the SATA/ATA Protocol
PCIe Proccessor: Handle the PCIe protocol
EMMc Proccessor: Handle the PCIe protocol

# CPU
CPU: We can set the core number of CPU

# DRAM
DRAM: We can set the size of DRAM 
SRAM: We can set the size of SRAM
Data Search Engine: A hardware engine to search host data that in the DRAM

# ECC
TBD

# NAND
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


