/*******************************************************************************
 * (c) Copyright 2016-2018 Microsemi Corporation.  All rights reserved.
 *
 * Platform definitions
 * Version based on requirements of MPFS MSS
 *
 */
 /*=========================================================================*//**
  @mainpage Sample file detailing how hw_platform.h should be constructed for 
    the MPFS MSS

    @section intro_sec Introduction
    The  hw_platform.h is to be located in the project ./config/hw_config/ directory.
    Currently this file must be hand crafted when using the MPFS MSS.
    
    You can use this file as sample.
    Rename this file from sample_hw_platform.h to hw_platform.h and store it in
    the ./config/hw_config/ folder of your project. Then customize it per your HW design.

    @section driver_configuration Project configuration Instructions
    1. Change MPFS MSS CLOCK DEFINITIONS to match design used.
    2  Add all other core BASE addresses
    3. Add peripheral Core Interrupt to CoreRISCV_AXI4 interrupt mappings
    4. Define MSCC_STDIO_UART_BASE_ADDR if you want a CoreUARTapb mapped to STDIO
*//*=========================================================================*/

#ifndef HW_PLATFORM_H
#define HW_PLATFORM_H

/***************************************************************************//**
 * MPFS MSS CLOCK DEFINITIONS
 */
#ifndef SIFIVE_HIFIVE_UNLEASHED
#define MSS_COREPLEX_CPU_CLK            50000000UL
#define MSS_AXI_SWITCH_CLK              25000000UL
//#define MSS_COREPLEX_CPU_CLK            20000000UL
//#define MSS_SYSTEM_CLK                  20000000UL   /* PLIC,CLINT,DEBUG,PORTS  */
#define MSS_RTC_TOGGLE_CLK              10000000UL   /* RTC clk input, must run at less than 1/2 rate of MSS_SYSTEM_CLK  */
//#define MSS_AXI_SWITCH_CLK              20000000UL
#define MSS_AHB_APB_CLK                 10000000UL
#else
#define MSS_COREPLEX_CPU_CLK            50000000UL
#define MSS_RTC_TOGGLE_CLK              10000000UL   /* RTC clk input, must run at less than 1/2 rate of MSS_SYSTEM_CLK  */
#define MSS_AXI_SWITCH_CLK              25000000UL
#endif

/***************************************************************************//**
 * Non-memory Peripheral base addresses
 * Format of define is:
 * <corename>_<instance>_BASE_ADDR
 */

#define COREUARTAPB0_BASE_ADDR          0x70001000UL
#define COREGPIO_BASE_ADDR              0x70002000UL
#define COREGPIO_IN_BASE_ADDR           0x70002000UL
#define CORETIMER0_BASE_ADDR            0x70003000UL
#define CORETIMER1_BASE_ADDR            0x70004000UL
#define COREGPIO_OUT_BASE_ADDR          0x70005000UL
#define FLASH_CORE_SPI_BASE             0x70006000UL
#define CORE16550_BASE_ADDR             0x70007000UL

/***************************************************************************//**
 * DDR defines
 * Format of define is:
 * <DDR_CONTROLLER>_<instance>_SIZE
 */
#define MSS_CTL_DDR_SIZE (0x10000000ul)

/***************************************************************************//**
 * Peripheral Interrupts are mapped to the corresponding CoreRISCV_AXI4 interrupt
 * from the Libero design.
 * There can be up to 31 external interrupts (IRQ[30:0] pins) on the CoreRISCV_AXI4
 * The CoreRISCV_AXI4 external interrupts are defined in the riscv_CoreplexE31.h
 * These are of the form
 * typedef enum
{
    NoInterrupt_IRQn = 0,
    External_1_IRQn  = 1,
    External_2_IRQn  = 2,
    .
    .
    .
    External_31_IRQn = 31
} IRQn_Type;
 
 The interrupt 0 on RISC-V processor is not used. The pin IRQ[0] should map to
 External_1_IRQn likewise IRQ[30] should map to External_31_IRQn
 * Format of define is:
 * <corename>_<instance>_<core interrupt name>
 */

#define TIMER0_IRQn                     External_30_IRQn
#define TIMER1_IRQn                     External_31_IRQn

/****************************************************************************
 * Baud value to achieve a 115200 baud rate with a 83MHz system clock.
 * This value is calculated using the following equation:
 *      BAUD_VALUE = (CLOCK / (16 * BAUD_RATE)) - 1
 *****************************************************************************/
#define BAUD_VALUE_115200   			44

/***************************************************************************//**
 * User edit section- Edit sections below if required
 */
#ifdef MSCC_STDIO_THRU_CORE_UART_APB
/*
 * A base address mapping for the STDIO printf/scanf mapping to CortUARTapb
 * must be provided if it is being used
 *
 * e.g. #define MSCC_STDIO_UART_BASE_ADDR COREUARTAPB1_BASE_ADDR
 */
#define MSCC_STDIO_UART_BASE_ADDR COREUARTAPB0_BASE_ADDR

#ifndef MSCC_STDIO_UART_BASE_ADDR
#error MSCC_STDIO_UART_BASE_ADDR not defined- e.g. #define MSCC_STDIO_UART_BASE_ADDR COREUARTAPB1_BASE_ADDR
#endif

#ifndef MSCC_STDIO_BAUD_VALUE
/*
 * The MSCC_STDIO_BAUD_VALUE define should be set in your project's settings to
 * specify the baud value used by the standard output CoreUARTapb instance for
 * generating the UART's baud rate if you want a different baud rate from the
 * default of 115200 baud
 */
#define MSCC_STDIO_BAUD_VALUE           115200
#endif  /*MSCC_STDIO_BAUD_VALUE*/

#endif  /* end of MSCC_STDIO_THRU_CORE_UART_APB */
/*******************************************************************************
 * End of user edit section
 */
#endif /* HW_PLATFORM_H */


