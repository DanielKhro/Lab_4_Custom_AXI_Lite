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

#include "platform.h"
#include "xil_io.h"
#include "xil_printf.h"

#define FIFO_BASE       0x43C00000U

#define REV_REG         0x00U
#define RESET_REG       0x04U
#define WRITE_REG       0x08U
#define READ_REQ_REG    0x0CU
#define READ_DATA_REG   0x10U
#define STATUS_REG      0x14U
#define COUNT_REG       0x18U
#define CONFIG_REG      0x1CU
#define THRESHOLD_REG   0x20U

#define RD_VALID        0x10U

int main(void)
{
    const u32 expected[2] = {0xAAAAU, 0xBBBBU};
    u32 data;
    u32 count;
    u32 timeout;
    int passed = 1;
    int i;

    init_platform();

    xil_printf("\r\nStarting FIFO board test\r\n");

    xil_printf("Revision:   %08x\r\n",
               Xil_In32(FIFO_BASE + REV_REG));
    xil_printf("Config:     %08x\r\n",
               Xil_In32(FIFO_BASE + CONFIG_REG));
    xil_printf("Thresholds: %08x\r\n",
               Xil_In32(FIFO_BASE + THRESHOLD_REG));

    /* Reset the FIFO. */
    Xil_Out32(FIFO_BASE + RESET_REG, 1U);

    if (Xil_In32(FIFO_BASE + COUNT_REG) != 0U ||
        Xil_In32(FIFO_BASE + STATUS_REG) != 0x05U) {
        xil_printf("FAIL: incorrect reset state\r\n");
        passed = 0;
    }

    /* Push two words. */
    Xil_Out32(FIFO_BASE + WRITE_REG, expected[0]);
    Xil_Out32(FIFO_BASE + WRITE_REG, expected[1]);

    count = Xil_In32(FIFO_BASE + COUNT_REG);
    xil_printf("Count after writes: %u (expected 2)\r\n", count);

    if (count != 2U)
        passed = 0;

    /* Request and check each word. */
    for (i = 0; i < 2; i++) {
        Xil_Out32(FIFO_BASE + READ_REQ_REG, 1U);

        /* Wait for the wrapper to capture the FIFO output. */
        for (timeout = 0; timeout < 100000U; timeout++) {
            if (Xil_In32(FIFO_BASE + STATUS_REG) & RD_VALID)
                break;
        }

        if (timeout == 100000U) {
            xil_printf("FAIL: timed out waiting for RD_VALID\r\n");
            passed = 0;
            break;
        }

        data = Xil_In32(FIFO_BASE + READ_DATA_REG);

        xil_printf("Read: %08x, expected: %08x\r\n",
                   data, expected[i]);

        if (data != expected[i])
            passed = 0;
    }

    count = Xil_In32(FIFO_BASE + COUNT_REG);
    xil_printf("Count after reads: %u (expected 0)\r\n", count);

    if (count != 0U)
        passed = 0;

    /* Check that software reset clears a queued word and RD_VALID. */
    Xil_Out32(FIFO_BASE + WRITE_REG, 0xCCCCU);
    Xil_Out32(FIFO_BASE + RESET_REG, 1U);

    if (Xil_In32(FIFO_BASE + COUNT_REG) != 0U ||
        Xil_In32(FIFO_BASE + STATUS_REG) != 0x05U ||
        Xil_In32(FIFO_BASE + READ_DATA_REG) != 0U) {
        xil_printf("FAIL: software reset\r\n");
        passed = 0;
    }

    if (passed)
        xil_printf("PASS: basic FIFO board test completed.\r\n");
    else
        xil_printf("FAIL: FIFO board test.\r\n");

    cleanup_platform();
    return passed ? 0 : 1;
}
