/*******************************************************************************
 * (c) Copyright 2019 Microchip FPGA Embedded Systems Solutions.
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 * 
 * Register bit offsets and masks definitions for PolarFire SoC(PSE) MSS I2C.
 * 
 * This driver is based on SmartFusion2 I2C driver v2.1.100
 *
 * SVN $Revision: 11366 $
 * SVN $Date: 2019-06-06 12:26:30 +0530 (Thu, 06 Jun 2019) $
 */
#ifndef MSS_I2C_REGS_H_
#define MSS_I2C_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 Register Bit definitions
 */
#define CR0                         (uint8_t)0u
#define CR1                         (uint8_t)1u
#define AA                          (uint8_t)2u
#define SI                          (uint8_t)3u
#define STO                         (uint8_t)4u
#define STA                         (uint8_t)5u
#define ENS1                        (uint8_t)6u
#define CR2                         (uint8_t)7u

#define CR0_MASK                    (uint8_t)(0x01)
#define CR1_MASK                    (uint8_t)(0x02)
#define AA_MASK                     (uint8_t)(0x04)
#define SI_MASK                     (uint8_t)(0x08)
#define STO_MASK                    (uint8_t)(0x10)
#define STA_MASK                    (uint8_t)(0x20)


#define ENS1_MASK                   (uint8_t)(0x40)
#define CR2_MASK                    (uint8_t)(0x80)
#define DATA_DIR                    0u
#define DATA_DIR_MASK               (0x01)

#define ADDR_GC                     0u

#define ADDR_GC_MASK                (uint8_t)0x01

#define SMBALERT_IE                 (uint8_t)0u
#define SMBSUS_IE                   (uint8_t)1u
#define SMB_IPMI_EN                 2u
#define SMBALERT_NI                 3u
#define SMBALERT_NO                 4u
#define SMBSUS_NI                   5u
#define SMBSUS_NO                   (uint8_t)6u
#define SMBUS_RESET                 (uint8_t)7u

#define SMBALERT_IE_MASK            (uint8_t)(0x01)
#define SMBSUS_IE_MASK              (uint8_t)(0x02)
#define SMB_IPMI_EN_MASK            (0x01 << SMB_IPMI_EN)
#define SMBALERT_NI_MASK            (0x01 << SMBALERT_NI)
#define SMBALERT_NO_MASK            (uint8_t)(0x10)
#define SMBSUS_NI_MASK              (0x01 << SMBSUS_NI)
#define SMBSUS_NO_MASK              (uint8_t)(0x40)
#define SMBUS_RESET_MASK            (uint8_t)(0x80)

#ifdef __cplusplus
}
#endif

#endif /* MSS_I2C_REGS_H_ */
