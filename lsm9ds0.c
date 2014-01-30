/***************************** EE-ESTG-IPLEIRA *********************************
*
* File Name		: lsm9ds0_gyro.c
* Author		: Miguel Rasteiro
* Version		: V 1.0
* Date			: 29 de Janeiro de 2014, 10:14
* Description		: LSM9DS0 digital output gyroscope sensor
 *
********************************************************************************
*
*
********************************************************************************
* REVISON HISTORY
*
| VERSION	| DATE		| AUTHORS	  | DESCRIPTION
|               |               |                 |
| 1.0		| 29/1/2014	| MR              | First Release
|               |               |                 |
*******************************************************************************/


#include "lsm9ds0.h"
#include <plib.h>

/* lsm9ds0 gyroscope registers */
#define WHO_AM_I	(0x0F)

#define SENSITIVITY_250	 8750	  /*(micro)dps/LSB */
#define SENSITIVITY_500	 17500    /*	  udps/LSB */
#define SENSITIVITY_2000 70000	  /*	  udps/LSB */

#define CTRL_REG1	(0x20)    /* CTRL REG1 */
#define CTRL_REG2	(0x21)    /* CTRL REG2 */
#define CTRL_REG3	(0x22)    /* CTRL_REG3 */
#define CTRL_REG4	(0x23)    /* CTRL_REG4 */
#define CTRL_REG5	(0x24)    /* CTRL_REG5 */
#define	REFERENCE	(0x25)    /* REFERENCE REG */
#define	FIFO_CTRL_REG	(0x2E)    /* FIFO CONTROL REGISTER */
#define FIFO_SRC_REG	(0x2F)    /* FIFO SOURCE REGISTER */
#define	OUT_X_L		(0x28)    /* 1st AXIS OUT REG of 6 */

#define AXISDATA_REG	OUT_X_L

/* CTRL_REG1 */
#define ALL_ZEROES	(0x00)
#define PM_OFF		(0x00)
#define PM_NORMAL	(0x08)
#define ENABLE_ALL_AXES	(0x07)
#define ENABLE_NO_AXES	(0x00)
#define BW00		(0x00)
#define BW01		(0x10)
#define BW10		(0x20)
#define BW11		(0x30)
#define ODR095		(0x00)  /* ODR =  95Hz */
#define ODR190		(0x40)  /* ODR = 190Hz */
#define ODR380		(0x80)  /* ODR = 380Hz */
#define ODR760		(0xC0)  /* ODR = 760Hz */

/* CTRL_REG2 */
#define NORMAL_MODE_RR	(0x00)  /* Normal mode (reset reading HP_RESET_FILTER*/
#define RF_FILT		(0x10)  /* Reference signal for filtering*/
#define NORMAL_MODE	(0x20)
#define AUTORST_INT	(0x30)  /* Autoreset on interrupt event*/
                         /* ODR |  95 Hz  |  190Hz  |  380Hz  |  720Hz  |*/
#define HPCF_00  	(0x00)/*|   7.2   |   13.5  |   27    |   51.4  |*/
#define HPCF_01		(0x01)/*|   3.5   |   7.2   |   13.5  |   27    |*/
#define HPCF_02		(0x02)/*|   1.8   |   3.5   |   7.2   |   13.5  |*/
#define HPCF_03		(0x03)/*|   0.9   |   1.8   |   3.5   |   7.2   |*/
#define HPCF_04		(0x04)/*|   0.45  |   0.9   |   1.8   |   3.5   |*/
#define HPCF_05		(0x05)/*|   0.18  |   0.45  |   0.9   |   1.8   |*/
#define HPCF_06		(0x06)/*|   0.09  |   0.18  |   0.45  |   0.9   |*/
#define HPCF_07		(0x07)/*|   0.045 |   0.09  |   0.18  |   0.45  |*/
#define HPCF_0A		(0x0A)/*|   0.018 |   0.045 |   0.09  |   0.18  |*/
#define HPCF_0B		(0x0B)/*|   0.009 |   0.018 |   0.045 |   0.09  |*/

/* CTRL_REG3 bits */
#define	I2_DRDY		(0x08)  /* Data-ready on DRDY_G*/
#define	I2_WTM		(0x04)
#define	I2_OVRUN	(0x02)
#define	I2_EMPTY	(0x01)
#define	I2_NONE		(0x00)
#define	I2_MASK		(0x0F)

/* CTRL_REG4 bits */
#define	FS_MASK		(0x30)
#define	BDU_ENABLE	(0x80)  /* Block data update. Output registers not updated until MSb and LSb read*/

/* CTRL_REG5 bits */
#define	FIFO_ENABLE	(0x40)
#define HPF_ENALBE	(0x11)

/* FIFO_CTRL_REG bits */
#define	FIFO_MODE_MASK		(0xE0)
#define	FIFO_MODE_BYPASS	(0x00)
#define	FIFO_MODE_FIFO		(0x20)
#define	FIFO_MODE_STREAM	(0x40)
#define	FIFO_MODE_STR2FIFO	(0x60)
#define	FIFO_MODE_BYPASS2STR	(0x80)
#define	FIFO_WATERMARK_MASK	(0x1F)

#define FIFO_STORED_DATA_MASK	(0x1F)

#define I2C_AUTO_INCREMENT	(0x80)  /* For multiple byte read*/

/* RESUME STATE INDICES 
#define	RES_CTRL_REG1		0
#define	RES_CTRL_REG2		1
#define	RES_CTRL_REG3		2
#define	RES_CTRL_REG4		3
#define	RES_CTRL_REG5		4
#define	RES_FIFO_CTRL_REG	5
#define	RESUME_ENTRIES		6


/** Registers Contents */
#define WHOAMI_LSM9DS0_GYR	(0xD4)  /* Expected content for WAI register*/


struct lsm9ds0_gyr_triple {
	INT32	x,	/* x-axis angular rate data. */
		y,	/* y-axis angluar rate data. */
		z;	/* z-axis angular rate data. */
};
