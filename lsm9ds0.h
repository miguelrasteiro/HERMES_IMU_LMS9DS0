// ----------------------------------------------------------------------------
/**
   @file     lsm9ds0.h
   A LSM9DS0 driver for PIC32MX7XX \n
   Language: C++ \n
   License:  GNU Public License
   @version  Version 1.0 Release 1
   @date     29 de Janeiro de 2014, 10:14

   \author Miguel Rasteiro \n\t
           EE-ESTG-IPLEIRIA \n\t
   E-Mail: 2100783@my.ipleiria.pt

   \brief Header file for LSM9DS0 ST MEMS

   Change History:
********************************************************************************
| VERSION      | DATE		| AUTHORS	  | DESCRIPTION                |
|:------------:|:--------------:|:----------------|:---------------------------|
| 1.0          | 29/1/2014	| MR              | First Release              |
// ---------------------------------------------------------------------------*/
#ifndef LSM9DS0_H
#define	LSM9DS0_H

#include <plib.h>
//  LSM9DS0 Registers
// \def MAADSDKdslkanfdslkddfsdfsdfdsfsdfsdfdsfdsf
#define OUT_TEMP_L_XM       (0x05)    // TEMPERATURE OUT LSB REGISTER
#define OUT_TEMP_H_XM       (0x06)    // TEMPERATURE OUT MSB REGISTER */
#define STATUS_REG_M        (0x07)    // STATUS MAGNETOMETER
#define OUT_X_L_M           (0x08)    // X AXIS OUT LSB REG MAG    
#define OUT_X_H_M           (0x09)    // X AXIS OUT MSB REG MAG
#define OUT_Y_L_M           (0x0A)    // Y AXIS OUT LSB REG MAG
#define OUT_Y_H_M           (0x0B)    // Y AXIS OUT MSB REG MAG
#define OUT_Z_L_M           (0x0C)    // Z AXIS OUT LSB REG MAG
#define OUT_Z_H_M           (0x0D)    // Z AXIS OUT MSB REG MAG
#define WHO_AM_I_G          (0x0F)    // WHO AM I GYRO
#define WHO_AM_I_XM         (0x0F)    // WHO AM I MAG AND ACC
#define INT_CTRL_REG_M      (0x12)    // INTERRUPT CTRL REG MAG
#define INT_SRC_REG_M       (0x13)    // INTERRUPT SOURCE REG MAG
#define INT_THS_L_M         (0x14)    // INTERRUPT TSH REG MAG
#define INT_THS_H_M         (0x15)    // INTERRUPT TSH REG MAG
#define OFFSET_X_L_M        (0x16)    // X AXIS OFFSET LSB REG MAG
#define OFFSET_X_H_M        (0x17)    // X AXIS OFFSET MSB REG MAG
#define OFFSET_Y_L_M        (0x18)    // Y AXIS OFFSET LSB REG MAG
#define OFFSET_Y_H_M        (0x19)    // Y AXIS OFFSET MSB REG MAG
#define OFFSET_Z_L_M        (0x1A)    // Z AXIS OFFSET LSB REG MAG
#define OFFSET_Z_H_M        (0x1B)    // Z AXIS OFFSET MSB REG MAG
#define REFERENCE_X         (0x1C)    // REF X AXIS
#define REFERENCE_Y         (0x1D)    // REF Y AXIS
#define REFERENCE_Z         (0x1E)    // REF Z AXIS
#define CTRL_REG0_XM        (0x1F)    // CTRL REG0 MAG AND ACC
#define CTRL_REG1_XM        (0x20)    // CTRL REG1 MAG AND ACC
#define CTRL_REG1_G         (0x20)    // CTRL REG1 GYRO
#define CTRL_REG2_XM        (0x21)    // CTRL REG2 MAG AND ACC
#define CTRL_REG2_G         (0x21)    // CTRL REG2 GYRO
#define CTRL_REG3_XM        (0x22)    // CTRL_REG3 MAG AND ACC
#define CTRL_REG3_G         (0x22)    // CTRL REG3 GYRO
#define CTRL_REG4_XM        (0x23)    // CTRL_REG4 MAG AND ACC
#define CTRL_REG4_G         (0x23)    // CTRL REG4 GYRO
#define CTRL_REG5_XM        (0x24)    // CTRL_REG5 MAG AND ACC
#define CTRL_REG5_G         (0x24)    // CTRL REG5 GYRO
#define CTRL_REG6_XM        (0x25)    // CTRL_REG6 MAG AND ACC
#define	REFERENCE_G         (0x25)    // REFERENCE REG GYRO
#define CTRL_REG7_XM        (0x26)    // CTRL_REG7 MAG AND ACC
#define STATUS_REG_G        (0x27)    // STATUS REG GYRO
#define STATUS_REG_A        (0x27)    // STATUS REG ACC
#define	OUT_X_L_G           (0x28)    // X AXIS OUT LSB REG GYRO
#define	OUT_X_L_A           (0x28)    // X AXIS OUT LSB REG ACC
#define	OUT_X_H_G           (0x29)    // X AXIS OUT MSB REG GYRO
#define	OUT_X_H_A           (0x29)    // X AXIS OUT MSB REG ACC
#define	OUT_Y_L_G           (0x2A)    // Y AXIS OUT LSB REG GYRO
#define	OUT_Y_L_A           (0x2A)    // Y AXIS OUT LSB REG ACC
#define	OUT_Y_H_G           (0x2B)    // Y AXIS OUT MSB REG GYRO
#define	OUT_Y_H_A           (0x2B)    // Y AXIS OUT MSB REG ACC
#define	OUT_Z_L_G           (0x2C)    // Z AXIS OUT LSB REG GYRO
#define	OUT_Z_L_A           (0x2C)    // Z AXIS OUT LSB REG ACC
#define	OUT_Z_H_G           (0x2D)    // Z AXIS OUT MSB REG GYRO
#define	OUT_Z_H_A           (0x2D)    // Z AXIS OUT MSB REG ACC
#define	FIFO_CTRL_REG       (0x2E)    // FIFO CONTROL REGISTER
#define FIFO_SRC_REG        (0x2F)    // FIFO SOURCE REGISTER
#define	INT1_CFG            (0x30)    //
#define	INT_GEN_1_REG       (0x30)    //
#define	INT1_SRC            (0x31)    //
#define	INT_GEN_1_SRC       (0x31)    //
#define	INT1_TSH_XH         (0x32)    //
#define	INT_GEN_1_THS       (0x32)    //
#define	INT1_TSH_XL         (0x33)    //
#define	INT_GEN_1_DURATION  (0x33)    //
#define	INT1_TSH_YH         (0x34)    //
#define	INT_GEN_2_REG       (0x34)    //
#define	INT1_TSH_YL         (0x35)    //
#define	INT_GEN_2_SRC       (0x35)    //
#define	INT1_TSH_ZH         (0x36)    //
#define	INT_GEN_2_THS       (0x36)    //
#define	INT1_TSH_ZL         (0x37)    //
#define	INT_GEN_2_DURATION  (0x37)    //
#define	INT1_DURATION       (0x38)    //
#define	CLICK_CFG           (0x38)    //
#define	CLICK_SRC           (0x39)    //
#define	CLICK_THS           (0x3A)    //
#define	TIME_LIMIT          (0x3B)    //
#define	TIME_LATENCY        (0x3C)    //
#define	TIME_WINDOW         (0x3D)    //
#define	Act_THS             (0x3E)    //
#define	Act_DUR             (0x3F)    //

#define Read                (0x01)
#define Write               (0x00)
#define Address_XM          (0x3A)    // SAO_MX TO VDD  */
#define Address_G           (0xD6)    // SAO_G TO VDD   */
//#define Address_XM          (0x3C)    // SAO_MX TO GND  */
//#define Address_G           (0xD4)    // SAO_G TO GND   */

// CTRL_GYRO_REG1 
#define GYRO_OFF            (0x00)  // Off
#define PM_OFF              (0x00)  // Power-down mode 
#define PM_NORMAL           (0x08)  // Normal Power mode 
#define ENABLE_ALL_AXES     (0x07)  // Enable all Gyro axis
#define X_ENABLE            (0x02)  // Enable X Gyro axis
#define Y_ENABLE            (0x01)  // Enable Y Gyro axis
#define Z_ENABLE            (0x04)  // Enable Z Gyro axis
#define BW00                (0x00)  // Defines cut-off according to ODR
#define BW01                (0x10)  // Defines cut-off according to ODR
#define BW10                (0x20)  // Defines cut-off according to ODR
#define BW11                (0x30)  // Defines cut-off according to ODR
#define G_ODR95             (0x00)  // ODR =  95Hz
#define G_ODR190            (0x40)  // ODR = 190Hz
#define G_ODR380            (0x80)  // ODR = 380Hz
#define G_ODR760            (0xC0)  // ODR = 760Hz

// CTRL_GYRO_REG2
#define NORMAL_MODE_RR      (0x00)  // Normal mode (reset reading HP_RESET_FILTER
#define RF_FILT             (0x10)  // Reference signal for filtering
#define NORMAL_MODE         (0x20)
#define AUTORST_INT         (0x30)  // Autoreset on interrupt event
                               // ODR |  95 Hz  |  190Hz  |  380Hz  |  720Hz  |
#define HPCF_00             (0x00)  //|   7.2   |   13.5  |   27    |   51.4  |
#define HPCF_01             (0x01)  //|   3.5   |   7.2   |   13.5  |   27    |
#define HPCF_02             (0x02)  //|   1.8   |   3.5   |   7.2   |   13.5  |
#define HPCF_03             (0x03)  //|   0.9   |   1.8   |   3.5   |   7.2   |
#define HPCF_04             (0x04)  //|   0.45  |   0.9   |   1.8   |   3.5   |
#define HPCF_05             (0x05)  //|   0.18  |   0.45  |   0.9   |   1.8   |
#define HPCF_06             (0x06)  //|   0.09  |   0.18  |   0.45  |   0.9   |
#define HPCF_07             (0x07)  //|   0.045 |   0.09  |   0.18  |   0.45  |
#define HPCF_0A             (0x0A)  //|   0.018 |   0.045 |   0.09  |   0.18  |
#define HPCF_0B             (0x0B)  //|   0.009 |   0.018 |   0.045 |   0.09  |

// CTRL_GYRO_REG4
#define	FS_245_DPS          (0x00)  // 245  dps Full-scale
#define	FS_500_DPS          (0x10)  // 500  dps Full-scale
#define	FS_2000_DPS         (0x20)  // 2000 dps Full-scale
#define	LITTLE_ENDIAN       (0x00)  // Little Endian Output
#define	BIG_ENDIAN          (0x40)  // Big Endian Output
#define	CONTINUOUS_UPDATE   (0x00)  // Continuous block update
#define	BDU_G_ENABLE        (0x80)  // Block data update. Output registers not updated until MSb and LSb read

// CTRL_XM_REG1 
#define ACC_OFF             (0x00)  // OFF
#define A_ODR3_125          (0x10)  // ODR = 3.125Hz
#define A_ODR6_25           (0x20)  // ODR = 6.25Hz
#define A_ODR12_5           (0x30)  // ODR = 12.5Hz
#define A_ODR25             (0x40)  // ODR = 25Hz
#define A_ODR50             (0x50)  // ODR = 50Hz
#define A_ODR100            (0x60)  // ODR = 100Hz
#define A_ODR200            (0x70)  // ODR = 200Hz
#define A_ODR400            (0x80)  // ODR = 400Hz
#define A_ODR800            (0x90)  // ODR = 800Hz
#define A_ODR1600           (0xA0)  // ODR = 1200Hz
#define	CONTINUOUS_UPDATE   (0x00)  // Continuous block update
#define	BDU_A_ENABLE        (0x08)  // Output registers not updated until MSb and LSb read

// CTRL_XM_REG2
#define	ABW773              (0x00)  // Anti-alias filter Bw = 773Hz
#define	ABW194              (0x40)  // Anti-alias filter Bw = 194Hz
#define	ABW362              (0x80)  // Anti-alias filter Bw = 362Hz
#define	ABW50               (0xC0)  // Anti-alias filter Bw = 50 Hz
#define	FS_2_G              (0x00)  // 2 g Full-scale
#define	FS_4_G              (0x08)  // 4 g Full-scale
#define	FS_6_G              (0x10)  // 6 g Full-scale
#define	FS_8_G              (0x18)  // 8 g Full-scale
#define	FS_16_G             (0x20)  // 16g Full-scale

// CTRL_XM_REG5
#define	HIGH_MAG_RES        (0x60)  // High magnetic resolution
#define	LOW_MAG_RES         (0x00)  // Low magnetic resolution
#define M_ODR3_125          (0x00)  // ODR = 3.125Hz
#define M_ODR6_25           (0x04)  // ODR = 6.25Hz
#define M_ODR12_5           (0x08)  // ODR = 12.5Hz
#define M_ODR25             (0x0C)  // ODR = 25Hz
#define M_ODR50             (0x10)  // ODR = 50Hz
#define M_ODR100            (0x14)  // ODR = 100Hz
#define TEMP_EN             (0x80)  // Temperature sensor enable

// CTRL_XM_REG6
#define	FS_2_GAUSS          (0x00)  // 2 gauss Full-scale
#define	FS_4_GAUSS          (0x20)  // 4 gauss Full-scale
#define	FS_8_GAUSS          (0x40)  // 8 gauss Full-scale
#define	FS_16_GAUSS         (0x60)  // 16gauss Full-scale


#define I2C_AUTO_INCREMENT	(0x80)  // For multiple byte read

/* Registers Contents */
#define WHOAMI_LSM9DS0_GYR	(0xD4)  // Expected content for WAI register
#define WHOAMI_LSM9DS0_XM	(0x49)  // Expected content for WAI register

/*************** VAR ****************/
typedef struct {
   short  	x,	 // x-axis data.
                y,	 // y-axis data.
                z;	 // z-axis data.
}sensor_xyz ;

UINT8 buff[2];  //NAO POSSO DECLARAR NO HEADER?
/************ FUNCTIONS ************/
/** \fn     void  ReadGyro_raw (sensor_xyz*  raw)
\brief      Read raw gyro data.
\param      [out] struct sensor_xyz pointer (type short (16bits)).
\return     None. */
void  ReadGyro_raw    ( sensor_xyz*  raw   );
/** \fn     void  ReadAcc (sensor_xyz*  raw)
\brief      Read raw accelerometer data.
\param      [out] struct sensor_xyz pointer (type short (16bits)).
\return     None. */
void  ReadAcc         ( sensor_xyz*  raw   );
/** \fn     void  ReadMag (sensor_xyz*  raw)
\brief      Read raw magnetometer data.
\param      [out] struct sensor_xyz pointer (type short (16bits)).
\return     None. */
void  ReadMag         ( sensor_xyz*  raw   );
/** \fn     void  ReadTemp (short*  temperature)
\brief      Read temperature raw data.
\param      [out] temperature pointer (type short (16bits)).
\return     None. */
void  ReadTemp        ( short* temperature );
/** \fn     void  GyroEnable (char command)
\brief      Enable Gyro sensor.
\param      [in] command Configures CTRL_GYRO_REG1.
\return     None. */
void  GyroEnable      ( char command );
/** \fn     void  GyroConfig (char command)
\brief      Configure Gyro sensor.
\param      [in] command Configures CTRL_GYRO_REG4.
\return     None. */
void  GyroConfig      ( char command );
/** \fn     void  AccEnableConfig (char command1, char command2)
\brief      Enable and Configure Acc sensor.
\param      [in] command1 Configures CTRL_XM_REG1.
\param      [in] command2 Configures CTRL_XM_REG2.
\return     None. */
void  AccEnableConfig ( char command1, char command2 );
/** \fn     void  MagEnableConfig (char command1, char command2)
\brief      Enable and Configure Acc sensor.
\param      [in] command1 Configures CTRL_XM_REG5.
            \n Command1     : M_ODR3_125     - Magnetometer Data Rate = 3.125Hz
            \n                M_ODR6_25      - ODR = 6.25Hz
            \n                M_ODR12_5      - ODR = 12.5Hz
            \n                M_ODR25        - ODR = 25Hz
            \n                M_ODR50        - ODR = 50Hz
            \n                M_ODR100       - ODR = 100Hz Only if Accelerometer ODR>50Hz
            \n                HIGH_MAG_RES   - High magnetic resolution
            \n                LOW_MAG_RES    - LOW magnetic resolution
            \n                TEMP_EN        - Enable Temperature sensor
            \n         --> OR condition between command type
\param      [in] command2 Configures CTRL_XM_REG6.
            \n Command2     : FS_2_GAUSS       - Set 2 gauss Full-scale
            \n                FS_4_GAUSS       - Set 4 gauss Full-scale
            \n                FS_8_GAUSS       - Set 6 gauss Full-scale
            \n                FS_16_GAUSS      - Set 16gauss Full-scale
            \n         --> OR condition between command type
\return     None. */
void  MagEnableConfig ( char command1, char command2 );

UINT8 GetGyroAddr   ( void );
UINT8 GetAccMagAddr ( void );

/* Private */
//void  WriteRegister ( UINT8 add, UINT8 reg, UINT8 data );
//void  ReadRegister  ( UINT8 add, UINT8 reg, UINT8* data);

#endif	/* LSM9DS0_H */
