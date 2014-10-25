/**
 * \addtogroup main
 * \{
 * \file main.c
 *
  * \author Miguel Rasteiro \n\t
  *         EE-ESTG-IPLEIRIA \n\t
  * E-Mail: <2130904@my.ipleiria.pt> \n
 * \version 1.0 \n\n
 * \ref license \n\n
 *
 * \date Created on 29 January 2014, 10:14 \n
 *
 * \brief Implemented for PIC32MX7XX
 * \section maincode Main Source Code
 * \code
 */
#include <p32xxxx.h>
#include <plib.h>
//#include "pic_config.h"
#include "lsm9ds0.h"
#include "marg.h"
#include "uart.h"

/** Configuration Bit settings
 * SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
 * PBCLK = 80 MHz (SYSCLK / FPBDIV)
 * Primary Osc w/PLL (XT+,HS+,EC+PLL)
 * WDT OFF
 * Other options are don't care
 */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1

#define SYS_FREQ                (80000000L)                                       /**< CPU clock frequency */
#define	GetPeripheralClock()	(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()	(SYS_FREQ)                         /**< Instructions frequency */
#define UART_BAUDRATE             230400
#define PBCLK                    SYS_FREQ
#define I2Cclk                    100000
#define BRG                  (PBCLK/I2Cclk)/2-2 //(PBCLK/2/Fsck)                         /**< I2C frequency */
#define TIMER_1_INT_VECTOR 4                                       /**< Interruption Vector */

#define ACC_EXT_CAL 1                   /**< 1 - Using Calibrated Matrix; 0 - Default */
#define MAG_EXT_CAL 0                   /**< 1 - Using Calibrated Matrix; 0 - Default */

#define PI          3.14159265358979    /**< Define gyro sensitivity in use */
#define Gyrodps     SENSITIVITY_500DPS  /**< Define gyro sensitivity in use */
#define GyroRad     Gyrodps*PI/180      /**< Define gyro sensitivity in use in rad/s */
#define AccG        SENSITIVITY_ACC_4G  /**< Define acc sensitivity in use */
#define MagGauss    SENSITIVITY_MAG_2G  /**< Define mag sensitivity in use */
#define Gravity     1/AccG              /**< Define gravity value in bits */


/*================================================================
                 G L O B A L   V A R I A B L E S
================================================================*/
UINT8 T1overflow = 1;

#if !ACC_EXT_CAL                    /**< Identity matrix if not using external calibration data. */
float acc_offsets [3] = {0, 0, 0};
float acc_cal_matrix [3][3] = {{1, 0, 0 },
			       {0, 1, 0 },
			       {0, 0, 1 }};
#else
float gyro_offsets [3] = {0,0,0};                                       /// initial values
float acc_offsets [3] = { -1257.74, 11.2751, 42.5782 };                 /// from a calibration example
float acc_cal_matrix [3][3] = {{ 1.00597,    0.00134498, 0.00820683 },  /// from a calibration example
			       { 0.024164,   0.991093,   0.01471    },
			       {-0.00926287, 0.0128528,  1.05978    }};
#endif
#if !MAG_EXT_CAL                    /**< Identity matrix if not using external calibration data. */
float mag_offsets [3] = {0, 0, 0};
float mag_cal_matrix [3][3] = {{1, 0, 0 },
			       {0, 1, 0 },
			       {0, 0, 1 }};
#else
float mag_offsets [3] = { 2891.56, 3676.46, -963.728 };                 /// from a calibration example
float mag_cal_matrix [3][3] = {{ 0.868755,    0.0237516, -0.00292102 }, /// from a calibration example
                               { 0.0237516,   0.989378,  -0.0124555  },
			       {-0.00292102, -0.0124555,  0.973275   }};
#endif

/*================================================================
             F U N C T I O N S   P R O T O T Y P E S
================================================================*/

void InitUART (void);
void InitTimer1 (void);

/**
 * Timer 1 ISR
 *  Interrupt Priority Level = 2
 *  Vector 4
 */
void __ISR(TIMER_1_INT_VECTOR, ipl2) _Timer1Handler(void) {
    // Clear the interrupt flag
    mT1ClearIntFlag();
    // Protection to timer overflow
    T1overflow ++;
}

/*================================================================
                   E N T R Y   P O I N T
================================================================*/
int main(void)
{
    // Variables
    UINT8   buf[1024];
    UINT8   rd [3];
    // Read RawValues
    
    sensor_xyz gyro_raw,
               acc_raw,
               mag_raw;
    //
    data_xyz gyro,
             acc,
             mag;


    unsigned int temptime;
    short temp;
    UINT8 test;
    float x,y,z;
    float cycle_time, time_elapsed = 0;

    InitUART ();
//      OpenI2C1(I2C_EN,98);

	I2CConfigure ( I2C1, I2C_ENABLE_SLAVE_CLOCK_STRETCHING);
	I2CSetFrequency ( I2C1, GetPeripheralClock(), I2Cclk);
	I2CEnable(I2C1, TRUE);
//    InitMARG_DataReadyMeasurementMode ();
    InitMARG_ContinuousMeasurementMode ();
    AutoCalibrateGyro();
    AutoCalibrateAcc();
    InitTimer1();
    WriteTimer1(0x00);  // Timer set to 0

    TRISAbits.TRISA2 = 0;
    LATAbits.LATA2 = 0;	// set RA2 out
    while(1)
    {
//        ReadRegister (Address_G, STATUS_REG_G , &rd[0] );
//        ReadRegister (Address_XM, STATUS_REG_A, &rd[1] );
//        ReadRegister (Address_XM, STATUS_REG_M, &rd[2] );
//
//        if (rd[0]&0x08 && rd[1]&0x08 && rd[2]&0x08) {
//
//            LATAbits.LATA2 = 1;	// set RA2 out
//
//            temptime = ReadTimer1(); // Reads time elapsed
//            WriteTimer1(0x00);  // Timer set to 0
//            T1overflow = 1;
//            cycle_time = (float)((double) (temptime * T1overflow * 256) / PBCLK );// tempo = valortimer*overflow*prescaler*4/fosc ;
//            time_elapsed = time_elapsed + cycle_time;
//
//            ReadGyroXYZ ( & gyro);
//            ReadAccXYZ  ( & acc );
//            ReadMagXYZ  ( & mag );
//            gyro.x *=GyroRad; gyro.y *=GyroRad; gyro.z *=GyroRad;
//             acc.x *=AccG;     acc.y *=AccG;     acc.z *=AccG;
//             mag.x *=MagGauss; mag.y *=MagGauss; mag.z *=MagGauss;
//
//            sprintf(buf,"I %f %f %f %f %f %f %f %f %f %.4f\n",
//                                            gyro.x, gyro.y, gyro.z,
//                                             acc.x,  acc.y,  acc.z,
//                                             mag.x,  mag.y,  -mag.z,
//                                            cycle_time);
//                SendDataBuffer(buf, strlen(buf));
//
//            LATAbits.LATA2 = 0;	// set RA2 out
//        }

        // Colocar em função
        temptime = ReadTimer1(); // Reads time elapsed
        cycle_time = (float)((double) (temptime * T1overflow * 256) / PBCLK );// tempo = valortimer*overflow*prescaler*4/fosc ;

        if (cycle_time >= 0.01)
        {
             LATAbits.LATA2 = 1;	// set RA2 out
            time_elapsed = time_elapsed + cycle_time;
            WriteTimer1(0x00);  // Timer set to 0
            T1overflow = 1;
            //sampleFreq = 1/cycle_time;

            ReadGyroXYZ  ( & gyro );
            ReadAccXYZ   ( & acc  );
            ReadMagXYZ   ( & mag  );

            gyro.x *=GyroRad; gyro.y *=GyroRad; gyro.z *=GyroRad;
             acc.x *=AccG;     acc.y *=AccG;     acc.z *=AccG;
             mag.x *=MagGauss; mag.y *=MagGauss; mag.z *=MagGauss;


            sprintf(buf,"I %f %f %f %f %f %f %f %f %f %.4f\n",
                                            gyro.x, gyro.y, gyro.z,
                                             acc.x,  acc.y,  acc.z,
                                             mag.x,  mag.y,  -mag.z,
                                            cycle_time);
                SendDataBuffer(buf, strlen(buf));
                 LATAbits.LATA2 = 0;	// set RA2 out
        }
    }
    return -1;
}

/** \fn     void InitUART (void)
 * \brief   Inicialize UART
 * \details By Default: \n
 *          Interrupts OFF \n
 *          Baudrate - 115200 \n
 *          Number of bits - 8 \n
 *          No parity bit \n
 *          1 stop bits
 */
void InitUART(void){
    UARTConfigure(UART_MODULE_ID, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UART_MODULE_ID, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART_MODULE_ID, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART_MODULE_ID, GetPeripheralClock(), UART_BAUDRATE);
    UARTEnable(UART_MODULE_ID, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
}

/** \fn     void InitTimer1 (void)
 * \brief   Inicialize Timer 1 to measure sampling time
 * \details By Default: \n
 *          PreScaler - 256 \n
 *          Interrupts ON \n
 *          Priority - 2 \n
 *          SubPriority - 0 \n
 *          Also Enables System MultiVectoredInterrupts
 */
void InitTimer1 (void){
    OpenTimer1(T1_ON | T1_PS_1_256, 0xFFFF);
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_2 | T1_INT_SUB_PRIOR_0);// Set up the core timer interrupt with a priority of 2 and zero sub-priority
    INTEnableSystemMultiVectoredInt(); // STEP 3. enable multi-vector interrupts
}
/**\endcode \} */