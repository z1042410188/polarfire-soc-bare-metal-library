/*******************************************************************************
 * Copyright 2019 Microchip Corporation.
 *
 * SPDX-License-Identifier: MIT
 *
 * MPFS HAL Embedded Software example
 *
 */
/*******************************************************************************
 *
 * Code running on U54 hart 1
 *
 * SVN $Revision: 10516 $
 * SVN $Date: 2018-11-08 18:09:23 +0000 (Thu, 08 Nov 2018) $
 */
#include <stdio.h>
#include <string.h>
#include "mpfs_hal/mss_hal.h"
#include <drivers/mss_uart/mss_uart.h>
#include <mpfs_hal/mss_ints.h>


volatile uint32_t count_sw_ints_h1 = 0U;
extern uint64_t uart_lock;

/* Main function for the HART1(U54_1 processor).
 * Application code running on HART1 is placed here
 *
 * The HART1 goes into WFI. HART0 brings it out of WFI when it raises the first
 * Software interrupt to this HART
 */
void u54_1(void)
{
    uint8_t info_string[100];
    uint64_t hartid = read_csr(mhartid);
    volatile uint32_t icount = 0U;

    /*Clear pending software interrupt in case there was any.
      Enable only the software interrupt so that the E51 core can bring this
      core out of WFI by raising a software interrupt.*/
    clear_soft_interrupt();
    set_csr(mie, MIP_MSIP);

    /*Put this hart into WFI.*/
    do
    {
        __asm("wfi");
    }while(0 == (read_csr(mip) & MIP_MSIP));

    /*The hart is out of WFI, clear the SW interrupt. Hear onwards Application
     * can enable and use any interrupts as required*/
    clear_soft_interrupt();

    __enable_irq();

    mss_take_mutex((uint64_t)&uart_lock);
    MSS_UART_polled_tx_string(&g_mss_uart0_lo,
            "Hello World from u54 core 1 - hart1.\r\n");
    mss_release_mutex((uint64_t)&uart_lock);

    while (1U)
    {
        icount++;
        if (0x100000U == icount)
        {
            icount = 0U;
            sprintf(info_string,"Hart %d\r\n", hartid);
            mss_take_mutex((uint64_t)&uart_lock);
            MSS_UART_polled_tx(&g_mss_uart0_lo, info_string, strlen(info_string));
            mss_release_mutex((uint64_t)&uart_lock);
        }
    }
    /* never return */
}

/* HART1 Software interrupt handler */
void Software_h1_IRQHandler(void)
{
    uint64_t hart_id = read_csr(mhartid);
    count_sw_ints_h1++;
}
