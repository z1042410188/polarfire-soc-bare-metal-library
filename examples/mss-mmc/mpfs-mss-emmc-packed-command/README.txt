================================================================================
    PolarFire SoC MSS eMMC packed command read and write application
================================================================================

This example project demonstrates the use of PolarFire SoC MSS eMMC with
packed command. To read several multiple blocks of data stored within the
eMMC device using the packed group of read commands and write several multiple
blocks of data to the eMMC device using the packed group of write commands.

The following project macros(defined in project settings) are used to configure
the system:

MSS_MMC_INTERNAL_APIS     - Define this to enable all internal APIs

The following software configuration is required to set in this project for
single hart or all harts debug session.

platform/config/software/mpfs_hal/mss_sw_config

Single hart(e51 hart0) -    MPFS_HAL_LAST_HART   0 - default

All harts -                 MPFS_HAL_LAST_HART   4 
--------------------------------------------------------------------------------
                            How to use this example
--------------------------------------------------------------------------------
Run the example project using a debugger. Place watches on buffers
g_mmc_tx_buff and g_mmc_rx_buff. You will then be able to observe the content
of g_mmc_tx_buff being written into the eMMC device and read back into the
g_mmc_rx_buff buffer.

--------------------------------------------------------------------------------
                                Target hardware
--------------------------------------------------------------------------------
This example project is targeted PolarFire SoC FPGA family hardware platforms
with the eMMC SD host controller.

There are configurations that needs to be set for this example project. The
configurations are categorized into hardware and software configurations and 
are respectively located in the following folders
    platform/config/hardware/hw_config
    platform/config/software/mpfs_hal/mss_sw_config

The "hw_config" defines the hardware configurations such as clocks. You must 
make sure that the configurations in this example project match the actual 
configurations of your target design you are using to test this example project.

The "sw_config" folder defines the software configurations such as HART 
configurations. These configurations have no dependency on the hardware
configurations that you use. If you change these configurations, you may have 
to change the software code to work according to the new configurations that 
you use.

## Executing project on PolarFire SoC hardware

Build the project and launch the debug configuration named 
mpfs-mss-emmc-packed-command Debug.launch which is configured for 
PolarFire SoC hardware platform.

