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

#define WARMUP_READINGS  64.0    /**< Number of warmup readings for sensors calibration */
#define AVERAGE_READINGS  128.0  /**< Number of readings for average sensors offsets */

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

    data->x = (float) ((float)reading.x * acc_cal_matrix[0][0] +
                       (float)reading.y * acc_cal_matrix[0][1] +
                       (float)reading.z * acc_cal_matrix[0][2] - acc_offsets [0]) ;
    data->y = (float) ((float)reading.x * acc_cal_matrix[1][0] +
                       (float)reading.y * acc_cal_matrix[1][1] +
                       (float)reading.z * acc_cal_matrix[1][2] - acc_offsets [1]) ;
    data->z = (float) ((float)reading.x * acc_cal_matrix[2][0] +
                       (float)reading.y * acc_cal_matrix[2][1] +
                       (float)reading.z * acc_cal_matrix[2][2] - acc_offsets [2]) ;
}
void ReadMagXYZ ( data_xyz* data ) {

    sensor_xyz reading;

    ReadMagRaw   ( &reading );

    data->x = (float) ((float)reading.x * mag_cal_matrix[0][0] +
                       (float)reading.y * mag_cal_matrix[0][1] +
                       (float)reading.z * mag_cal_matrix[0][2] - mag_offsets [0]) ;
    data->y = (float) ((float)reading.x * mag_cal_matrix[1][0] +
                       (float)reading.y * mag_cal_matrix[1][1] +
                       (float)reading.z * mag_cal_matrix[1][2] - mag_offsets [1]) ;
    data->z = (float) ((float)reading.x * mag_cal_matrix[2][0] +
                       (float)reading.y * mag_cal_matrix[2][1] +
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
    acc_offsets[2] = cal_sum[2] / AVERAGE_READINGS;
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

void InitMARG ( void ){

    MagEnableConfig ( TEMP_EN | HIGH_MAG_RES | M_ODR100, FS_2_GAUSS );
    AccEnableConfig ( CONTINUOUS_UPDATE | ENABLE_ALL_AXES | A_ODR100, ABW362 | FS_4_G );
    GyroEnable      ( G_ODR190 | BW10 | GYRO_ON | ENABLE_ALL_AXES );  // ODR 190Hz Cutoff 50 Hz
    GyroConfig      ( CONTINUOUS_UPDATE | FS_500_DPS | LITTLE_ENDIAN);
}
/**\endcode \}*/