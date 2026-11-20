/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_io.h"

#define MULT_BASE_ADDR		(0x43C00000)
#define MULT_BASE_ADDR_BRAM (0x40000000)
#define A_REG_ADDR			(MULT_BASE_ADDR + 0x00)
#define B_REG_ADDR			(MULT_BASE_ADDR + 0x04)
#define P_REG_ADDR			(MULT_BASE_ADDR + 0x08)
#define BRAM_ENTRY(k)		(MULT_BASE_ADDR_BRAM + ((k)*4))


int main()
{
		init_platform();
		xil_printf("Custom AXI IP Lab - Daniel Khrlobian\n");
	    xil_printf("Start of Multiplier + BRAM Test\n");

	    for (int i = 1; i <= 32; i++){
	    	Xil_Out32(A_REG_ADDR, i);
	    	Xil_Out32(B_REG_ADDR, i);

	    	uint32_t product = Xil_In32(P_REG_ADDR);
	    	Xil_Out32(BRAM_ENTRY(i - 1), product);
	    }

	    for (int k = 0; k < 32; k++){
	    	uint32_t product = Xil_In32(BRAM_ENTRY(k));
	    	xil_printf("Stored: %d x %d = %d at BRAM[%d]\r\n", k+1, k+1, (int)product, k);
	    }

	    xil_printf("End of Multiplier Test\n");

	    cleanup_platform();
	    return 0;
}

