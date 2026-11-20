# CSUN ECE 520 Lab 4 Custom AXI Lite

# Overview
Designed and implemented a custom AXI4-Lite peripheral using Verilog and Vivado to interface a Zynq processor with a 32-entry FIFO implemented in FPGA programmable logic. Integrated the hardware with the processor through AXI memory-mapped registers and developed a C application in Vitis to verify FIFO read/write operations, status monitoring, and reset functionality. All the hardware is defined through parameters for easy updating of data.

# Design Summary
<img width="549" height="285" alt="image" src="https://github.com/user-attachments/assets/c2843ddc-11a5-4210-9acd-8d7f1f650e46" />

The AXI4-Lite FIFO project implements a custom memory-mapped peripheral to enable communication between the Processing System (PS) and Programmable Logic (PL) of a Zynq SoC.

The design consists of a 32-entry FIFO implemented in Verilog and integrated into the Vivado block design through a custom AXI4-Lite IP. The AXI interface allows the processor to perform read and write operations, while the FIFO manages data storage using first-in, first-out ordering.

The hardware design was synthesized and implemented in Vivado, and a bitstream was generated for FPGA configuration. A C application developed in Vitis was used to communicate with the peripheral, test data transfers, and verify the functionality of the integrated hardware system.

# Verification and Results
After successfully generating the FPGA bitstream, a C application was developed in Vitis to test communication between the Processing System (PS) and Programmable Logic (PL).

Verification was performed by writing multiple 32-bit data words into the FIFO through the AXI4-Lite interface and reading them back. The Vitis terminal displayed the transmitted and received values, confirming successful data transfers and proper first-in, first-out ordering.

<img width="224" height="74" alt="image" src="https://github.com/user-attachments/assets/6bd33900-8405-4cba-ab4b-69b9272d4c9a" />
Usage of BRAM

<img width="626" height="152" alt="image" src="https://github.com/user-attachments/assets/22417bac-80cb-4abf-973e-2f4478a489fc" />
Timing Summary

# Known Issues or Limitations
Having to set the drivers to none to utilize the Xil functions in Vitis was a mistake I overlooked. The FIFO was already verified to work in previous labs, but I couldn't test the overall system until I figured out my driver settings for the system.

# References
- Creating and Packaging Custom IP User Guide
- Lab 4 PDF
