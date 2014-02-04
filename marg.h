/* 
 * File:   marg.h
 * Author: MiguelRasteiro
 *
 * Created on 1 de Fevereiro de 2014, 21:45
 */

#ifndef MARG_H
#define	MARG_H

#define Gravity 8192    // 1g value = 2^15/Acc_FullScale

typedef struct {
   float  	x,	 // x-axis treated data.
                y,	 // y-axis treadted data.
                z;	 // z-axis treated data.
}data_xyz ;

float gyro_offsets[3];
float acc_offsets [3];

// Functions
void  ReadGyroXYZ     ( data_xyz*  data  );
void  ReadAccXYZ      ( data_xyz*  data  );
void  InitMARG        ( void );
void  CalibrateAcc    ( void );
void  CalibrateGyro   ( void );

#endif	/* MARG_H */

