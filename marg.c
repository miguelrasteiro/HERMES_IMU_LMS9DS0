#include "lsm9ds0.h"
#include "marg.h"

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
//    short temp = 0;           //COrriggir para poder funcionar sem correcçao de temperatura
//    float x, y, z;

    ReadAccRaw   ( &reading );
//    ReadTemp  ( & temp  );
    // Offset removal
    data->x = (float) reading.x - acc_offsets[0] ;
    data->y = (float) reading.y - acc_offsets[1] ;
    data->z = (float) reading.z - acc_offsets[2] + (float) Gravity ;
/*    x = (float) reading.x - acc_offsets[0] ;
    y = (float) reading.y - acc_offsets[1] ;
    z = (float) reading.z - acc_offsets[2] + (float) Gravity ;
    // Temperature correction
    data->x = x - x * temp * 0.015 / 8;
    data->y = y - y * temp * 0.015 / 8; // ao da resultado!!! nao e assim que e afetada a leitura
    data->z = z - z * temp * 0.015 / 8;*/
}

void CalibrateAcc ( void ) {

    sensor_xyz cal_readings;
    float cal_sum[3]={0,0,0};
    int i;

    for ( i=0; i<128; i++ ) {           // Take a number of readings and average them
                                        // to calculate any bias the accelerometer may have.
        ReadAccRaw ( &cal_readings );

        cal_sum[0] += (float) cal_readings.x;
        cal_sum[1] += (float) cal_readings.y;
        cal_sum[2] += (float) cal_readings.z;
    }
    acc_offsets[0] = cal_sum[0] / 128.0;
    acc_offsets[1] = cal_sum[1] / 128.0;
    acc_offsets[2] = cal_sum[2] / 128.0;
}

void CalibrateGyro ( void ) {

    sensor_xyz cal_readings;
    float cal_sum[3]={0,0,0};
    int i;
/*
    for ( i=0; i<128; i++ ) {         // training readings for warming
        ReadGyroRaw ( &cal_readings );
    }
*/
    for ( i=0; i<128; i++ ) {

        ReadGyroRaw ( &cal_readings );

        cal_sum[0] += (float) cal_readings.x;
        cal_sum[1] += (float) cal_readings.y;
        cal_sum[2] += (float) cal_readings.z;
    }
    gyro_offsets[0] = cal_sum[0] / 128.0;
    gyro_offsets[1] = cal_sum[1] / 128.0;
    gyro_offsets[2] = cal_sum[2] / 128.0;
}

void InitMARG ( void ){

    MagEnableConfig ( TEMP_EN | HIGH_MAG_RES | M_ODR50, FS_4_GAUSS );
    AccEnableConfig ( CONTINUOUS_UPDATE | ENABLE_ALL_AXES | A_ODR50, ABW50 | FS_4_G );
    GyroEnable      ( G_ODR380 | BW10 | GYRO_ON | ENABLE_ALL_AXES );
    GyroConfig      ( CONTINUOUS_UPDATE | FS_500_DPS | LITTLE_ENDIAN);

    CalibrateGyro ();
    CalibrateAcc  ();
}