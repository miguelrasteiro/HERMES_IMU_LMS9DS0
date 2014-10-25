 /**
  * \addtogroup marg
  * \{
  * \file marg.c
  * \author Miguel Rasteiro \n\t
  * \brief Sensor data treatment library \n
  * \version  Version 1.0 Release 1 \n
  * \date     1 de February de 2014, 21:14 \n\n
  * \ref license \n\n
  *    Change History:
  * ************************************************************************
  * | VERSION      | DATE	    | AUTHORS	  | DESCRIPTION            |
  * |:------------:|:--------------:|:------------|:-----------------------|
  * | 1.0          |    1/2/2014    | MR          | First Release          |
  *\n\n
  * \section margcode MARG Source Code
  * \code
  */
#include "lsm9ds0.h"
#include "marg.h"

#define WARMUP_READINGS  256.0    /**< Number of warmup readings for sensors calibration */
#define AVERAGE_READINGS  256.0  /**< Number of readings for average sensors offsets */
#define AccG        SENSITIVITY_ACC_4G  /**< Define acc sensitivity in use */
#define Gravity     1/AccG              /**< Define gravity value in bits */

/*******************************************************************************
* Function Name  : ReadGyroXYZ
* Description    : Read the angular velocity treated data
* Input          : Gyro axis storage variable (data_xyz type)
* Output         : x,y,z data
* Return         : None
*******************************************************************************/
void ReadGyroXYZ ( data_xyz* data ) {

    sensor_xyz reading;
 //   short temp;

    ReadGyroRaw ( &reading );
 //   ReadTemp     ( & temp  );
    data->x = (float) reading.x - gyro_offsets[0];
    data->y = (float) reading.y - gyro_offsets[1];
    data->z = (float) reading.z - gyro_offsets[2];
}
void ReadAccXYZ ( data_xyz* data ) {

    sensor_xyz reading;

    ReadAccRaw   ( &reading );

//    data->x = (float) ((float)reading.x * acc_cal_matrix[0][0] +
//                       (float)reading.y * acc_cal_matrix[0][1] +
//                       (float)reading.z * acc_cal_matrix[0][2] - acc_offsets [0]) ;
//    data->y = (float) ((float)reading.x * acc_cal_matrix[1][0] +
//                       (float)reading.y * acc_cal_matrix[1][1] +
//                       (float)reading.z * acc_cal_matrix[1][2] - acc_offsets [1]) ;
//    data->z = (float) ((float)reading.x * acc_cal_matrix[2][0] +
//                       (float)reading.y * acc_cal_matrix[2][1] +
//                       (float)reading.z * acc_cal_matrix[2][2] - acc_offsets [2]) ;
//
    data->x = ((float)reading.x * acc_cal_matrix[0][0] +
               (float)reading.y * acc_cal_matrix[1][0] +
               (float)reading.z * acc_cal_matrix[2][0] - acc_offsets [0]) ;
    data->y = ((float)reading.x * acc_cal_matrix[0][1] +
               (float)reading.y * acc_cal_matrix[1][1] +
               (float)reading.z * acc_cal_matrix[2][1] - acc_offsets [1]) ;
    data->z = ((float)reading.x * acc_cal_matrix[0][2] +
               (float)reading.y * acc_cal_matrix[1][2] +
               (float)reading.z * acc_cal_matrix[2][2] - acc_offsets [2]) ;
}
void ReadMagXYZ ( data_xyz* data ) {

    sensor_xyz reading;

    ReadMagRaw   ( &reading );

//    data->x = (float) ((float)reading.x * mag_cal_matrix[0][0] +
//                       (float)reading.y * mag_cal_matrix[0][1] +
//                       (float)reading.z * mag_cal_matrix[0][2] - mag_offsets [0]) ;
//    data->y = (float) ((float)reading.x * mag_cal_matrix[1][0] +
//                       (float)reading.y * mag_cal_matrix[1][1] +
//                       (float)reading.z * mag_cal_matrix[1][2] - mag_offsets [1]) ;
//    data->z = (float) ((float)reading.x * mag_cal_matrix[2][0] +
//                       (float)reading.y * mag_cal_matrix[2][1] +
//                       (float)reading.z * mag_cal_matrix[2][2] - mag_offsets [2]) ;
    data->x =((float)reading.x * mag_cal_matrix[0][0] +
              (float)reading.y * mag_cal_matrix[1][0] +
              (float)reading.z * mag_cal_matrix[2][0] - mag_offsets [0]) ;
    data->y =((float)reading.x * mag_cal_matrix[0][1] +
              (float)reading.y * mag_cal_matrix[1][1] +
              (float)reading.z * mag_cal_matrix[2][1] - mag_offsets [1]) ;
    data->z =((float)reading.x * mag_cal_matrix[0][2] +
              (float)reading.y * mag_cal_matrix[1][2] +
              (float)reading.z * mag_cal_matrix[2][2] - mag_offsets [2]) ;
}
void AutoCalibrateAcc ( void ) {

    sensor_xyz cal_readings;
    float cal_sum[3]={0,0,0};
    int i;

    for ( i=0; i<WARMUP_READINGS; i++ ) {            // Take a number of readings to warm up
        ReadAccRaw ( &cal_readings );
    }

    for ( i=0; i<AVERAGE_READINGS; i++ ) {           // Take a number of readings and average them
                                        // to calculate any bias the accelerometer may have.
        ReadAccRaw ( &cal_readings );

        cal_sum[0] += (float) cal_readings.x;
        cal_sum[1] += (float) cal_readings.y;
        cal_sum[2] += (float) cal_readings.z;
    }
    acc_offsets[0] = cal_sum[0] / AVERAGE_READINGS;
    acc_offsets[1] = cal_sum[1] / AVERAGE_READINGS;
    acc_offsets[2] = cal_sum[2] / AVERAGE_READINGS - Gravity;
}
void AutoCalibrateGyro ( void ) {

    sensor_xyz cal_readings;
    float cal_sum[3]={0,0,0};
    int i;

    for ( i=0; i<WARMUP_READINGS; i++ ) {            // Take a number of readings to warm up
        ReadGyroRaw ( &cal_readings );
    }

    for ( i=0; i<AVERAGE_READINGS; i++ ) {           // Take a number of readings and average them
                                                     // to calculate the bias of the gyroscope may have.
        ReadGyroRaw ( &cal_readings );

        cal_sum[0] += (float) cal_readings.x;
        cal_sum[1] += (float) cal_readings.y;
        cal_sum[2] += (float) cal_readings.z;
    }
    gyro_offsets[0] = cal_sum[0] / AVERAGE_READINGS;
    gyro_offsets[1] = cal_sum[1] / AVERAGE_READINGS;
    gyro_offsets[2] = cal_sum[2] / AVERAGE_READINGS;
}
void UpdateGyroBias ( void ) {          // Use carefully, you have to guarantee that the gyro is stationary to update mean
                                        // Updates gyro offsets each reading weighs 1/AVERAGE_READINGS
    sensor_xyz cal_readings;

    ReadGyroRaw ( &cal_readings );

    gyro_offsets[0] = gyro_offsets[0] + (((float) cal_readings.x - gyro_offsets[0]) / (AVERAGE_READINGS));
    gyro_offsets[1] = gyro_offsets[1] + (((float) cal_readings.y - gyro_offsets[1]) / (AVERAGE_READINGS));
    gyro_offsets[2] = gyro_offsets[2] + (((float) cal_readings.z - gyro_offsets[2]) / (AVERAGE_READINGS));
}
void UpdateAccBias ( void ) {          // Use carefully, you have to guarantee that the acc is stationary and z axis is pointing down to update mean
                                       // Updates acc offsets, each reading weighs 1/AVERAGE_READINGS
    sensor_xyz cal_readings;

    ReadAccRaw ( &cal_readings );

    acc_offsets[0] = acc_offsets[0] + (((float) cal_readings.x - acc_offsets[0]) / (AVERAGE_READINGS));
    acc_offsets[1] = acc_offsets[1] + (((float) cal_readings.y - acc_offsets[1]) / (AVERAGE_READINGS));
    acc_offsets[2] = acc_offsets[2] + (((float) cal_readings.z - acc_offsets[2]) / (AVERAGE_READINGS));
}

void InitMARG_ContinuousMeasurementMode ( void ){

    MagEnableConfig ( TEMP_EN | HIGH_MAG_RES | M_ODR100, FS_2_GAUSS );
    AccEnableConfig ( CONTINUOUS_UPDATE | ENABLE_ALL_AXES | A_ODR100, ABW50 | FS_4_G );
    GyroEnable      ( G_ODR190 | BW00 | GYRO_ON | ENABLE_ALL_AXES );  // ODR 190Hz Cutoff 12.5 Hz
    GyroConfig      ( CONTINUOUS_UPDATE | FS_500_DPS | LITTLE_ENDIAN);

    // Warmup readings
    sensor_xyz some_readings;
    int i;

    for ( i=0; i<WARMUP_READINGS; i++ ) {            // Take a number of readings to warm up
        ReadGyroRaw ( &some_readings );
        ReadAccRaw  ( &some_readings );
        ReadMagRaw  ( &some_readings );
    }
}

void InitMARG_DataReadyMeasurementMode ( void ){

    UINT8 data[1];

    MagEnableConfig ( TEMP_EN | LOW_MAG_RES | M_ODR100, FS_2_GAUSS );
    AccEnableConfig ( CONTINUOUS_UPDATE | ENABLE_ALL_AXES | A_ODR100, ABW50 | FS_2_G );
    GyroEnable      ( G_ODR95 | BW00 | GYRO_ON | ENABLE_ALL_AXES );  // ODR 190Hz Cutoff 12.5 Hz
    GyroConfig      ( CONTINUOUS_UPDATE | FS_500_DPS | LITTLE_ENDIAN);
    WriteRegister   ( Address_G, CTRL_REG3_G , 0x01 );
    ReadRegister   ( Address_G, CTRL_REG3_G , data );
    WriteRegister   ( Address_G, CTRL_REG3_G , 0x08 );
    WriteRegister   ( Address_XM,CTRL_REG3_XM, 0x04);
    WriteRegister   ( Address_XM,CTRL_REG4_XM, 0x04);

////GYRO
//    GyroEnable ( G_ODR95 | BW00 | GYRO_ON | ENABLE_ALL_AXES );
//	/* CTRL_REG3_G sets up interrupt and DRDY_G pins
//	Bits[7:0]: I1_IINT1 I1_BOOT H_LACTIVE PP_OD I2_DRDY I2_WTM I2_ORUN I2_EMPTY
//	I1_INT1 - Interrupt enable on INT_G pin (0=disable, 1=enable)
//	I1_BOOT - Boot status available on INT_G (0=disable, 1=enable)
//	H_LACTIVE - Interrupt active configuration on INT_G (0:high, 1:low)
//	PP_OD - Push-pull/open-drain (0=push-pull, 1=open-drain)
//	I2_DRDY - Data ready on DRDY_G (0=disable, 1=enable)
//	I2_WTM - FIFO watermark interrupt on DRDY_G (0=disable 1=enable)
//	I2_ORUN - FIFO overrun interrupt on DRDY_G (0=disable 1=enable)
//	I2_EMPTY - FIFO empty interrupt on DRDY_G (0=disable 1=enable) */
//	// Int1 enabled (pp, active low), data read on DRDY_G:
//    WriteRegister ( Address_G, CTRL_REG4_G, 0x08 );
//    GyroConfig    ( CONTINUOUS_UPDATE | FS_500_DPS | LITTLE_ENDIAN);
////ACC
//    AccEnableConfig ( CONTINUOUS_UPDATE | ENABLE_ALL_AXES | A_ODR50, ABW773 | FS_2_G );
//	/* CTRL_REG3_XM is used to set interrupt generators on INT1_XM
//	Bits (7-0): P1_BOOT P1_TAP P1_INT1 P1_INT2 P1_INTM P1_DRDYA P1_DRDYM P1_EMPTY
//	*/
//	// Accelerometer data ready on INT1_XM (0x04)
//    WriteRegister(Address_XM,CTRL_REG3_XM, 0x04);
////MAG
//    MagEnableConfig ( TEMP_EN | LOW_MAG_RES | M_ODR100, FS_2_GAUSS );
//	/* CTRL_REG4_XM is used to set interrupt generators on INT2_XM
//	Bits (7-0): P2_TAP P2_INT1 P2_INT2 P2_INTM P2_DRDYA P2_DRDYM P2_Overrun P2_WTM
//	*/
//	WriteRegister(Address_XM,CTRL_REG4_XM, 0x04); // Magnetometer data ready on INT2_XM (0x08)
//	/* INT_CTRL_REG_M to set push-pull/open drain, and active-low/high
//	Bits[7:0] - XMIEN YMIEN ZMIEN PP_OD IEA IEL 4D MIEN
//	XMIEN, YMIEN, ZMIEN - Enable interrupt recognition on axis for mag data
//	PP_OD - Push-pull/open-drain interrupt configuration (0=push-pull, 1=od)
//	IEA - Interrupt polarity for accel and magneto
//		0=active-low, 1=active-high
//	IEL - Latch interrupt request for accel and magneto
//		0=irq not latched, 1=irq latched
//	4D - 4D enable. 4D detection is enabled when 6D bit in INT_GEN1_REG is set
//	MIEN - Enable interrupt generation for magnetic data
//		0=disable, 1=enable) */
//	WriteRegister(Address_XM, INT_CTRL_REG_M, 0xE1); // Enable interrupts for mag, active-low, push-pull

    // Warmup readings
    sensor_xyz some_readings;
    int i;

    for ( i=0; i<WARMUP_READINGS; i++ ) {            // Take a number of readings to warm up
        ReadGyroRaw ( &some_readings );
        ReadAccRaw  ( &some_readings );
        ReadMagRaw  ( &some_readings );
    }
}
/**\endcode \}*/