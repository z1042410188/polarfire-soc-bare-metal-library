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
 * Code running on U54 second hart
 *
 * SVN $Revision: 10516 $
 * SVN $Date: 2018-11-08 18:09:23 +0000 (Thu, 08 Nov 2018) $
 */

#include "mpfs_hal/mss_clint.h"
#include "drivers/mss_watchdog/mss_watchdog.h"
#include "drivers/mss_uart/mss_uart.h"

volatile uint32_t count_sw_ints_h2 = 0;
extern uint64_t wd_lock, uart_lock;

extern void uart_tx_with_mutex (mss_uart_instance_t * this_uart,
                                uint64_t mutex_addr,
                                const uint8_t * pbuff);

mss_watchdog_config_t wd2lo_config;

/* Main function for the HART2(U54_2 processor).
 * Application code running on HART2 is placed here
 *
 * The HART2 goes into WFI. HART0 brings it out of WFI when it raises the first
 * Software interrupt to this HART.
 */
void u54_2(void)
{


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
     *can enable and use any interrupts as required*/
    clear_soft_interrupt();
    /*Enable Watchdog MVRP interrupt*/

    /* Set WD1 such that the MVRP interrupt will happen after 10 seconds after
     * reset and the Trigger interrupt will happen after 25 Sec*/
    wd2lo_config.forbidden_en = MSS_WDOG_DISABLE;
    wd2lo_config.timeout_val = 0x3e0u;
    wd2lo_config.mvrp_val = 0xBEBC2u ;
    wd2lo_config.time_val = 0xBEBC2u + 0xBEBC2u; /*MVRP interrupt after 25 Sec*/

    mss_take_mutex((uint64_t)&wd_lock);
    MSS_WD_configure(MSS_WDOG2_LO, &wd2lo_config);
    MSS_WD_reload(MSS_WDOG2_LO);
    MSS_WD_enable_mvrp_irq(MSS_WDOG2_LO);
    mss_release_mutex((uint64_t)&wd_lock);

    __enable_irq();

    /*Enable Watchdog Timeout and MVRP interrupts as local interrupts on E51
     * Timeout interrupt is enabled by default in MSS Watchdog*/
    __enable_local_irq(WDOGx_MVRP_U54_INT);
    __enable_local_irq(WDOGx_TOUT_U54_INT);

    PLIC_init();

    /* Enable MVRP Interrupt on PLIC */
    PLIC_SetPriority(WDOG2_MRVP_PLIC, 2);
    PLIC_EnableIRQ(WDOG2_MRVP_PLIC);

    /* Enable MVRP Interrupt on PLIC */
    PLIC_SetPriority(WDOG2_TOUT_PLIC, 2);
    PLIC_EnableIRQ(WDOG2_TOUT_PLIC);

    uart_tx_with_mutex (&g_mss_uart0_lo,  (uint64_t)&uart_lock, "\r\nMSS Watchdog2 Configured \r\n");

    while (1u)
    {
        icount++;
        if (0x100000u == icount)
        {
            icount = 0u;
        }
    }
}

/* HART2 Software interrupt handler */
void Software_h2_IRQHandler(void)
{
    uint64_t hart_id = read_csr(mhartid);
    count_sw_ints_h2++;
}
