/***************************** EE-ESTG-IPLEIRA *********************************
*
* File Name		: lsm9ds0.h
* Author		: Miguel Rasteiro
* Version		: V 1.0
* Date			: 29 de Janeiro de 2014, 10:14
* Description		: LSM9DS0 header
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

#ifndef LSM9DS0_H
#define	LSM9DS0_H

/* LSM9DS0 Registers */
#define OUT_TEMP_L_XM	(0x05)    /* TEMPERATURE OUT LSB REG   */
#define OUT_TEMP_H_XM	(0x06)    /* TEMPERATURE OUT MSB REG   */
#define STATUS_REG_M	(0x07)    /* STATUS MAGNETOMETER       */
#define OUT_X_L_M	(0x08)    /* X AXIS OUT LSB REG MAG    */
#define OUT_X_H_M	(0x09)    /* X AXIS OUT MSB REG MAG    */
#define OUT_Y_L_M	(0x0A)    /* Y AXIS OUT LSB REG MAG    */
#define OUT_Y_H_M	(0x0B)    /* Y AXIS OUT MSB REG MAG    */
#define OUT_Z_L_M	(0x0C)    /* Z AXIS OUT LSB REG MAG    */
#define OUT_Z_H_M	(0x0D)    /* Z AXIS OUT MSB REG MAG    */
#define WHO_AM_I_G	(0x0F)    /* WHO AM I GYRO             */
#define WHO_AM_I_XM	(0x0F)    /* WHO AM I MAG AND ACC      */
#define INT_CTRL_REG_M  (0x12)    /* INTERRUPT CTRL REG MAG    */
#define INT_SRC_REG_M   (0x13)    /* INTERRUPT SOURCE REG MAG  */
#define INT_THS_L_M     (0x14)    /* INTERRUPT TSH REG MAG     */
#define INT_THS_H_M     (0x15)    /* INTERRUPT TSH REG MAG     */
#define OFFSET_X_L_M    (0x16)    /* X AXIS OFFSET LSB REG MAG */
#define OFFSET_X_H_M    (0x17)    /* X AXIS OFFSET MSB REG MAG */
#define OFFSET_Y_L_M    (0x18)    /* Y AXIS OFFSET LSB REG MAG */
#define OFFSET_Y_H_M    (0x19)    /* Y AXIS OFFSET MSB REG MAG */
#define OFFSET_Z_L_M    (0x1A)    /* Z AXIS OFFSET LSB REG MAG */
#define OFFSET_Z_H_M    (0x1B)    /* Z AXIS OFFSET MSB REG MAG */
#define REFERENCE_X     (0x1C)    /* REF X AXIS                */
#define REFERENCE_Y     (0x1D)    /* REF Y AXIS                */
#define REFERENCE_Z     (0x1E)    /* REF Z AXIS                */
#define CTRL_REG0_XM	(0x1F)    /* CTRL REG0 MAG AND ACC     */
#define CTRL_REG1_XM	(0x20)    /* CTRL REG1 MAG AND ACC     */
#define CTRL_REG1_G	(0x20)    /* CTRL REG1 GYRO            */
#define CTRL_REG2_XM	(0x21)    /* CTRL REG2 MAG AND ACC     */
#define CTRL_REG2_G	(0x21)    /* CTRL REG2 GYRO            */
#define CTRL_REG3_XM	(0x22)    /* CTRL_REG3 MAG AND ACC     */
#define CTRL_REG3_G	(0x22)    /* CTRL REG3 GYRO            */
#define CTRL_REG4_XM	(0x23)    /* CTRL_REG4 MAG AND ACC     */
#define CTRL_REG4_G	(0x23)    /* CTRL REG4 GYRO            */
#define CTRL_REG5_XM	(0x24)    /* CTRL_REG5 MAG AND ACC     */
#define CTRL_REG5_G	(0x24)    /* CTRL REG5 GYRO            */
#define CTRL_REG6_XM	(0x25)    /* CTRL_REG6 MAG AND ACC     */
#define	REFERENCE_G	(0x25)    /* REFERENCE REG GYRO        */
#define CTRL_REG7_XM	(0x26)    /* CTRL_REG7 MAG AND ACC     */
#define STATUS_REG_G    (0x27)    /* STATUS REG GYRO           */
#define STATUS_REG_A    (0x27)    /* STATUS REG ACC            */
#define	OUT_X_L_G	(0x28)    /* X AXIS OUT LSB REG GYRO   */
#define	OUT_X_L_A	(0x28)    /* X AXIS OUT LSB REG ACC    */
#define	OUT_X_H_G	(0x29)    /* X AXIS OUT MSB REG GYRO   */
#define	OUT_X_H_A	(0x29)    /* X AXIS OUT MSB REG ACC    */
#define	OUT_Y_L_G	(0x2A)    /* Y AXIS OUT LSB REG GYRO   */
#define	OUT_Y_L_A	(0x2A)    /* Y AXIS OUT LSB REG ACC    */
#define	OUT_Y_H_G	(0x2B)    /* Y AXIS OUT MSB REG GYRO   */
#define	OUT_Y_H_A	(0x2B)    /* Y AXIS OUT MSB REG ACC    */
#define	OUT_Z_L_G	(0x2C)    /* Z AXIS OUT LSB REG GYRO   */
#define	OUT_Z_L_A	(0x2C)    /* Z AXIS OUT LSB REG ACC    */
#define	OUT_Z_H_G	(0x2D)    /* Z AXIS OUT MSB REG GYRO   */
#define	OUT_Z_H_A	(0x2D)    /* Z AXIS OUT MSB REG ACC    */
#define	FIFO_CTRL_REG	(0x2E)    /* FIFO CONTROL REGISTER     */
#define FIFO_SRC_REG	(0x2F)    /* FIFO SOURCE REGISTER      */
#define	INT1_CFG 	(0x30)    /*  */
#define	INT_GEN_1_REG 	(0x30)    /*  */
#define	INT1_SRC	(0x31)    /*  */
#define	INT_GEN_1_SRC 	(0x31)    /*  */
#define	INT1_TSH_XH	(0x32)    /*  */
#define	INT_GEN_1_THS	(0x32)    /*  */
#define	INT1_TSH_XL	(0x33)    /*  */
#define	INT_GEN_1_DURATION   (0x33)    /*  */
#define	INT1_TSH_YH	(0x34)    /*  */
#define	INT_GEN_2_REG 	(0x34)    /*  */
#define	INT1_TSH_YL	(0x35)    /*  */
#define	INT_GEN_2_SRC 	(0x35)    /*  */
#define	INT1_TSH_ZH	(0x36)    /*  */
#define	INT_GEN_2_THS 	(0x36)    /*  */
#define	INT1_TSH_ZL	(0x37)    /*  */
#define	INT_GEN_2_DURATION   (0x37)    /*  */
#define	INT1_DURATION	(0x38)    /*  */
#define	CLICK_CFG	(0x38)    /*  */
#define	CLICK_SRC	(0x39)    /*  */
#define	CLICK_THS	(0x3A)    /*  */
#define	TIME_LIMIT	(0x3B)    /*  */
#define	TIME_LATENCY	(0x3C)    /*  */
#define	TIME_WINDOW	(0x3D)    /*  */
#define	Act_THS 	(0x3E)    /*  */
#define	Act_DUR 	(0x3F)    /*  */

#define Read            (0x01)
#define Write           (0x00)
#define Address_XM      (0x3A)     /* SAO_MX TO VDD  */
#define Address_G       (0xD6)     /* SAO_G TO VDD   */
//#define Address_XM      (0x3C)     /* SAO_MX TO GND  */
//#define Address_G       (0xD4)     /* SAO_G TO GND   */

/* VAR */
typedef struct {
   short  	x,	 /* x-axis angular rate data. */
                y,	 /* y-axis angluar rate data. */
                z;	 /* z-axis angular rate data. */
}sensor_raw ;

short temperature;

/* FUNCTIONS */
//void  WriteRegister ( UINT8 add, UINT8 reg, UINT8 data );
//void  ReadRegister  ( UINT8 add, UINT8 reg, UINT8* data);
void  ReadGyro      ( sensor_raw* raw );
void  ReadAcc       ( sensor_raw* raw );
void  ReadMag       ( sensor_raw* raw );
void  ReadTemp      ( short* temperature );



#endif	/* LSM9DS0_H */
