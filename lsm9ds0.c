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

/* LSM9DS0 Registers */
/*#define OUT_TEMP_L_XM	(0x05)    /* TEMPERATURE OUT LSB REG   *
#define OUT_TEMP_H_XM	(0x06)    /* TEMPERATURE OUT MSB REG   *
#define STATUS_REG_M	(0x07)    /* STATUS MAGNETOMETER       *
#define OUT_X_L_M	(0x08)    /* X AXIS OUT LSB REG MAG    *
#define OUT_X_H_M	(0x09)    /* X AXIS OUT MSB REG MAG    *
#define OUT_Y_L_M	(0x0A)    /* Y AXIS OUT LSB REG MAG    *
#define OUT_Y_H_M	(0x0B)    /* Y AXIS OUT MSB REG MAG    *
#define OUT_Z_L_M	(0x0C)    /* Z AXIS OUT LSB REG MAG    *
#define OUT_Z_H_M	(0x0D)    /* Z AXIS OUT MSB REG MAG    *
#define WHO_AM_I_G	(0x0F)    /* WHO AM I GYRO             *
#define WHO_AM_I_XM	(0x0F)    /* WHO AM I MAG AND ACC      *
#define INT_CTRL_REG_M  (0x12)    /* INTERRUPT CTRL REG MAG    *
#define INT_SRC_REG_M   (0x13)    /* INTERRUPT SOURCE REG MAG  *
#define INT_THS_L_M     (0x14)    /* INTERRUPT TSH REG MAG     *
#define INT_THS_H_M     (0x15)    /* INTERRUPT TSH REG MAG     *
#define OFFSET_X_L_M    (0x16)    /* X AXIS OFFSET LSB REG MAG *
#define OFFSET_X_H_M    (0x17)    /* X AXIS OFFSET MSB REG MAG /
#define OFFSET_Y_L_M    (0x18)    /* Y AXIS OFFSET LSB REG MAG *
#define OFFSET_Y_H_M    (0x19)    /* Y AXIS OFFSET MSB REG MAG /
#define OFFSET_Z_L_M    (0x1A)    /* Z AXIS OFFSET LSB REG MAG /
#define OFFSET_Z_H_M    (0x1B)    /* Z AXIS OFFSET MSB REG MAG /
#define REFERENCE_X     (0x1C)    /* REF X AXIS                *
#define REFERENCE_Y     (0x1D)    /* REF Y AXIS                *
#define REFERENCE_Z     (0x1E)    /* REF Z AXIS                /
#define CTRL_REG0_XM	(0x1F)    /* CTRL REG0 MAG AND ACC     /
#define CTRL_REG1_XM	(0x20)    /* CTRL REG1 MAG AND ACC     /
#define CTRL_REG1_G	(0x20)    /* CTRL REG1 GYRO            
#define CTRL_REG2_XM	(0x21)    /* CTRL REG2 MAG AND ACC     /
#define CTRL_REG2_G	(0x21)    /* CTRL REG2 GYRO            /
#define CTRL_REG3_XM	(0x22)    /* CTRL_REG3 MAG AND ACC    *
#define CTRL_REG3_G	(0x22)    /* CTRL REG3 GYRO           /
#define CTRL_REG4_XM	(0x23)    /* CTRL_REG4 MAG AND ACC    *
#define CTRL_REG4_G	(0x23)    /* CTRL REG4 GYRO           *
#define CTRL_REG5_XM	(0x24)    /* CTRL_REG5 MAG AND ACC    /
#define CTRL_REG5_G	(0x24)    /* CTRL REG5 GYRO           *
#define CTRL_REG6_XM	(0x25)    /* CTRL_REG6 MAG AND ACC     *
#define	REFERENCE_G	(0x25)    /* REFERENCE REG GYRO        *
#define CTRL_REG7_XM	(0x26)    /* CTRL_REG7 MAG AND ACC     *
#define STATUS_REG_G    (0x27)    /* STATUS REG GYRO           *
#define STATUS_REG_A    (0x27)    /* STATUS REG ACC            *
#define	OUT_X_L_G	(0x28)    /* X AXIS OUT LSB REG GYRO   *
#define	OUT_X_L_A	(0x28)    /* X AXIS OUT LSB REG ACC    *
#define	OUT_X_H_G	(0x29)    /* X AXIS OUT MSB REG GYRO   *
#define	OUT_X_H_A	(0x29)    /* X AXIS OUT MSB REG ACC    *
#define	OUT_Y_L_G	(0x2A)    /* Y AXIS OUT LSB REG GYRO   /
#define	OUT_Y_L_A	(0x2A)    /* Y AXIS OUT LSB REG ACC    /
#define	OUT_Y_H_G	(0x2B)    /* Y AXIS OUT MSB REG GYRO   /
#define	OUT_Y_H_A	(0x2B)    /* Y AXIS OUT MSB REG ACC    /
#define	OUT_Z_L_G	(0x2C)    /* Z AXIS OUT LSB REG GYRO   /
#define	OUT_Z_L_A	(0x2C)    /* Z AXIS OUT LSB REG ACC    /
#define	OUT_Z_H_G	(0x2D)    /* Z AXIS OUT MSB REG GYRO   *
#define	OUT_Z_H_A	(0x2D)    /* Z AXIS OUT MSB REG ACC    *
#define	FIFO_CTRL_REG	(0x2E)    /* FIFO CONTROL REGISTER     /
#define FIFO_SRC_REG	(0x2F)    /* FIFO SOURCE REGISTER      
#define	INT1_CFG 	(0x30)    /*  *
#define	INT_GEN_1_REG 	(0x30)    /*  *
#define	INT1_SRC	(0x31)    /*  *
#define	INT_GEN_1_SRC 	(0x31)    /*  *
#define	INT1_TSH_XH	(0x32)    /*  *
#define	INT_GEN_1_THS	(0x32)    /*  *
#define	INT1_TSH_XL	(0x33)    /*  /
#define	INT_GEN_1_DURATION   (0x33)   /*  *
#define	INT1_TSH_YH	(0x34)    /*  *
#define	INT_GEN_2_REG 	(0x34)    /*  *
#define	INT1_TSH_YL	(0x35)    /*  *
#define	INT_GEN_2_SRC 	(0x35)    /*  *
#define	INT1_TSH_ZH	(0x36)    /*  *
#define	INT_GEN_2_THS 	(0x36)    /*  *
#define	INT1_TSH_ZL	(0x37)    /*  
#define	INT_GEN_2_DURATION   (0x37)    /*  *
#define	INT1_DURATION	(0x38)    /*  *
#define	CLICK_CFG	(0x38)    /*  *
#define	CLICK_SRC	(0x39)    /*  *
#define	CLICK_THS	(0x3A)    /*  *
define	TIME_LIMIT	(0x3B)    /*  *
#define	TIME_LATENCY	(0x3C)    /*  *
#define	TIME_WINDOW	(0x3D)    /*  *
#define	Act_THS 	(0x3E)    /*  /
#define	Act_DUR 	(0x3F)    /*  /

#define Read            (0x01)
#define Write           (0x00)
#define Address_XM      (0x3A)     /* SAO_MX TO VDD  *
#define Address_G       (0xD6)     /* SAO_G TO VDD   *
//#define Address_XM      (0x3C)     /* SAO_MX TO GND  *
//#define Address_G       (0xD4)     /* SAO_G TO GND   */

/* CTRL_REG1 */
/*#define ALL_ZEROES	(0x00)
#define PM_OFF		(0x00)
#define PM_NORMAL	(0x08)
#define ENABLE_ALL_AXES	(0x07)
#define ENABLE_NO_AXES	(0x00)
#define BW00		(0x00)
#define BW01		(0x10)
#define BW10		(0x20)
#define BW11		(0x30)
#define ODR095		(0x00)  /* ODR =  95Hz *
#define ODR190		(0x40)  /* ODR = 190Hz *
#define ODR380		(0x80)  /* ODR = 380Hz *
#define ODR760		(0xC0)  /* ODR = 760Hz *

/* CTRL_REG2 *
#define NORMAL_MODE_RR	(0x00)  /* Normal mode (reset reading HP_RESET_FILTER*
#define RF_FILT		(0x10)  /* Reference signal for filtering*
#define NORMAL_MODE	(0x20)
#define AUTORST_INT	(0x30)  /* Autoreset on interrupt event*
                         /* ODR |  95 Hz  |  190Hz  |  380Hz  |  720Hz  |*
#define HPCF_00  	(0x00)/*|   7.2   |   13.5  |   27    |   51.4  |*
#define HPCF_01		(0x01)/*|   3.5   |   7.2   |   13.5  |   27    |*
#define HPCF_02		(0x02)/*|   1.8   |   3.5   |   7.2   |   13.5  |*
#define HPCF_03		(0x03)/*|   0.9   |   1.8   |   3.5   |   7.2   |*
#define HPCF_04		(0x04)/*|   0.45  |   0.9   |   1.8   |   3.5   |*
#define HPCF_05		(0x05)/*|   0.18  |   0.45  |   0.9   |   1.8   |*
#define HPCF_06		(0x06)/*|   0.09  |   0.18  |   0.45  |   0.9   |*
#define HPCF_07		(0x07)/*|   0.045 |   0.09  |   0.18  |   0.45  |*
#define HPCF_0A		(0x0A)/*|   0.018 |   0.045 |   0.09  |   0.18  |*
#define HPCF_0B		(0x0B)/*|   0.009 |   0.018 |   0.045 |   0.09  |*

/* CTRL_REG3 bits *
#define	I2_DRDY		(0x08)  /* Data-ready on DRDY_G*
#define	I2_WTM		(0x04)
#define	I2_OVRUN	(0x02)
#define	I2_EMPTY	(0x01)
#define	I2_NONE		(0x00)
#define	I2_MASK		(0x0F)

/* CTRL_REG4 bits *
#define	FS_MASK		(0x30)
#define	BDU_ENABLE	(0x80)  /* Block data update. Output registers not updated until MSb and LSb read*

/* CTRL_REG5 bits *
#define	FIFO_ENABLE	(0x40)
#define HPF_ENALBE	(0x11)

/* FIFO_CTRL_REG bits *
#define	FIFO_MODE_MASK		(0xE0)
#define	FIFO_MODE_BYPASS	(0x00)
#define	FIFO_MODE_FIFO		(0x20)
#define	FIFO_MODE_STREAM	(0x40)
#define	FIFO_MODE_STR2FIFO	(0x60)
#define	FIFO_MODE_BYPASS2STR	(0x80)
#define	FIFO_WATERMARK_MASK	(0x1F)

#define FIFO_STORED_DATA_MASK	(0x1F)

#define I2C_AUTO_INCREMENT	(0x80)  /* For multiple byte read*/

/** Registers Contents */
#define WHOAMI_LSM9DS0_GYR	(0xD4)  /* Expected content for WAI register*/

/*******************************************************************************
 * Function Name	: WriteRegister
 * Description		: Generic Writing function.
 * Input		: Sensor Address, Register Address, Data to be written
 * Output		: None
 * Return		: None
 *******************************************************************************/
void WriteRegister ( UINT8 add, UINT8 reg, UINT8 data ) {

    StartI2C1();                //Send the Start Bit
    IdleI2C1();                 //Wait to complete
    MasterWriteI2C1 (add );
    IdleI2C1();                 //Wait to complete
    MasterWriteI2C1 (reg );
    IdleI2C1();                 //Wait to complete
    MasterWriteI2C1 (data);
    IdleI2C1();                 //Wait to complete
    StopI2C1();                 //Send the Stop condition
    IdleI2C1();                 //Wait to complete
}

/*******************************************************************************
* Function Name		: ReadRegister
* Description		: Generic Reading function.
* Input			: Sensor Address, Register Address
* Output		: Data Read
* Return		: None
*******************************************************************************/
void ReadRegister  ( UINT8 add, UINT8 reg, UINT8* data ) {

    StartI2C1();                        //Send the Start Bit
    IdleI2C1();                         //Wait to complete
    MasterWriteI2C1 (( add|Write ));
    IdleI2C1();                         //Wait to complete
    MasterWriteI2C1 ( reg );            //transmit read command
    IdleI2C1();                         //Wait to complete
    StartI2C1();                        //Send the Start Bit
    IdleI2C1();                         //Wait to complete
    MasterWriteI2C1 (( add|Read ));
    IdleI2C1();                         //Wait to complete
    *data = MasterReadI2C1 ();
    IdleI2C1();                         //Wait to complete
    StopI2C1();                         //Send the Stop condition
    IdleI2C1();                         //Wait to complete
}

/*******************************************************************************
* Function Name  : ReadGyro
* Description    : Read the angular velocity values Output Registers
* Input          : Raw_gyro axis
* Output         : x,y,z raw_data
* Return         : None
*******************************************************************************/
void ReadGyro ( sensor_raw* raw ) {

    UINT8   L_value, H_value;

    ReadRegister ( Address_G, OUT_X_L_G, &L_value );
    ReadRegister ( Address_G, OUT_X_H_G, &H_value );
    raw->x = ( H_value <<8 | L_value );

    ReadRegister ( Address_G, OUT_Y_L_G, &L_value );
    ReadRegister ( Address_G, OUT_Y_H_G, &H_value );
    raw->y = ( H_value <<8 | L_value );

    ReadRegister ( Address_G, OUT_Z_L_G, &L_value );
    ReadRegister ( Address_G, OUT_Z_H_G, &H_value );
    raw->z = ( H_value <<8 | L_value );
}

/*******************************************************************************
* Function Name  : ReadAcc
* Description    : Read the accelaration values Output Registers
* Input          : Raw_acc axis
* Output         : x,y,z raw_data
* Return         : None
*******************************************************************************/
void ReadAcc  ( sensor_raw* raw ) {

    UINT8   L_value, H_value;

    ReadRegister ( Address_XM, OUT_X_L_A, &L_value );
    ReadRegister ( Address_XM, OUT_X_H_A, &H_value );
    raw->x = ( H_value <<8 | L_value );

    ReadRegister ( Address_XM, OUT_Y_L_A, &L_value );
    ReadRegister ( Address_XM, OUT_Y_H_A, &H_value );
    raw->y = ( H_value <<8 | L_value );

    ReadRegister ( Address_XM, OUT_Z_L_A, &L_value );
    ReadRegister ( Address_XM, OUT_Z_H_A, &H_value );
    raw->z = ( H_value <<8 | L_value );
}

/*******************************************************************************
* Function Name  : ReadMag
* Description    : Read the magnetic values Output Registers
* Input          : Raw_mag axis
* Output         : x,y,z raw_data
* Return         : None
*******************************************************************************/
void ReadMag  ( sensor_raw* raw ) {

    UINT8   L_value, H_value;

    ReadRegister ( Address_XM, OUT_X_L_M, &L_value );
    ReadRegister ( Address_XM, OUT_X_H_M, &H_value );
    raw->x = ( H_value <<8 | L_value );

    ReadRegister ( Address_XM, OUT_Y_L_M, &L_value );
    ReadRegister ( Address_XM, OUT_Y_H_M, &H_value );
    raw->y = ( H_value <<8 | L_value );

    ReadRegister ( Address_XM, OUT_Z_L_M, &L_value );
    ReadRegister ( Address_XM, OUT_Z_H_M, &H_value );
    raw->z = ( H_value <<8 | L_value );
}

/*******************************************************************************
* Function Name  : ReadTemp
* Description    : Read the temperature values Output Registers
* Input          : Temperature pointer
* Output         : Temperature_raw
* Return         : None
*******************************************************************************/
void ReadTemp ( short* temp ) {

    UINT8   L_value, H_value;

    ReadRegister ( Address_XM, OUT_TEMP_L_XM, &L_value );
    ReadRegister ( Address_XM, OUT_TEMP_H_XM, &H_value );
    * temp = ( H_value <<8 | L_value );
}