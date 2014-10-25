 /**
  *
  * \addtogroup marg
  * \{
  * \file marg.h
  * \author Miguel Rasteiro \n\t
  * \brief Sensor data treatment library
  * \version  Version 1.0 Release 1 \n
  * \date     1 de February de 2014, 21:14 \n\n
  * \ref license \n\n
  *    Change History:
  * ************************************************************************
  * | VERSION      | DATE	    | AUTHORS	  | DESCRIPTION            |
  * |:------------:|:--------------:|:------------|:-----------------------|
  * | 1.0          |    1/2/2014    | MR          | First Release          |
  */
#ifndef MARG_H
#define	MARG_H

/** @details Saves calibrated data for all axis. */
typedef struct {
            /// x-axis treated data.
   float  	x,
            /// y-axis treadted data.
                y,
            /// z-axis treated data.
                z;
}data_xyz ;

/************ VARIABLES ************/
float gyro_offsets[3];          /**< Saves gyroscope offsets in a vector --> position [0,1,2] = [x,y,z] data. */
float acc_offsets [3];          /**< Saves accelerometer offsets in a vector --> position [0,1,2] = [x,y,z] data. */
float acc_cal_matrix [3][3];    /**< Calibration matrix for the accelerometer. Obtained in the extended calibration of
                                 * the accelerometer. Otherwise use the identity matrix 3x3  */
float mag_offsets [3];          /**< Saves magnetometer offsets in a vector --> position [0,1,2] = [x,y,z] data. */
float mag_cal_matrix [3][3];    /**< Calibration matrix for the magnetometer. Obtained in the extended calibration of
                                 * the magnetometer. Otherwise use the identity matrix 3x3  */

/************ FUNCTIONS ************/
/** \fn     void  ReadGyroXYZ (data_xyz *data)
 * \brief      Read gyroscope removing offsets.
 * \param      [in/out] struct data_xyz pointer (type float (32bits)).
 */
void  ReadGyroXYZ       ( data_xyz*  data  );
/** \fn     void  ReadAccXYZ (data_xyz *data)
 * \brief      Read accelerometer compensating distortion and removing offsets if using calibration matrix.
 * \param      [in/out] struct data_xyz pointer (type float (32bits)).
 */
void  ReadAccXYZ        ( data_xyz*  data  );
/** \fn     void  ReadMagXYZ (data_xyz *data)
 * \brief      Read magnetometer compensating distortion and removing offsets if using calibration matrix.
 * \param      [in/out] struct data_xyz pointer (type float (32bits)).
 */
void  ReadMagXYZ        ( data_xyz*  data  );
/** \fn     void InitMARG_DataReadyMeasurementMode ( void )
 *  \brief  Inicialization of the MARG with default values.
 *  \details By default:
 *                         \n For magnetometer inicialization:
 *            \n\t\t            TEMP_EN          \t - Enables temperature module
 *            \n\t\t            HIGH_MAG_RES     \t - High magnetic resolution
 *            \n\t\t            M_ODR100         \t - ODR = 100Hz
 *            \n\t\t            FS_2_GAUSS       \t - 2 gauss Full-scale
 *                         \n For accelerometer inicialization:
 *            \n\t\t            CONTINUOUS_UPDATE\t - Continuous block update
 *            \n\t\t            ENABLE_ALL_AXES  \t - Enable all Acc axis
 *            \n\t\t            A_ODR100         \t - ODR = 100Hz
 *            \n\t\t            ABW362           \t - Anti-alias filter Bw = 362Hz
 *            \n\t\t            FS_4_G           \t - 4 g Full-scale
 *                         \n For gyroscope inicialization:
 *            \n\t\t            G_ODR190         \t - ODR = 190Hz
 *            \n\t\t            BW10             \t - Defines cut-off according to ODR
 *            \n\t\t            GYRO_ON          \t - Normal Power mode
 *            \n\t\t            ENABLE_ALL_AXES  \t - Enable all Gyro axis
 *            \n\t\t            FS_500_DPS       \t - 500 dps Full-scale
 *            \n\t\t            LITTLE_ENDIAN    \t - Little Endian Data Output
 *            \n\t\t            CONTINUOUS_UPDATE\t - Continuous Block Update
 */
void  InitMARG_ContinuousMeasurementMode  ( void );
/** \fn     void AutoCalibrateAcc ( void )
 * \brief   Takes a number off readings to calculate accelerometer offsets
 */
void  AutoCalibrateAcc  ( void );
/** \fn     void AutoCalibrateGyro ( void )
 * \brief   Takes a number off readings to calculate gyroscope offsets
 */
void  AutoCalibrateGyro ( void );
/** \fn     void UpdateGyroBias ( void )
 * \brief   Can be used to ajust gyroscope offsets with time
 * \details Use carefully, you have to guarantee that the gyro is stationary to update mean
 */
void  UpdateGyroBias    ( void );
/** \fn     void UpdateAccBias ( void )
 * \brief   Can be used to ajust accelerometer offsets with time
 * \details Use carefully, you have to guarantee that the acc is stationary and z axis
 * is pointing down to update mean
 */
void  UpdateAccBias     ( void );

#endif	/* MARG_H */
/**\}*/