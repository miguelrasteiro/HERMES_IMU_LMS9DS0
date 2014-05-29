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

#define SYS_FREQ (80000000L)                                       /**< CPU clock frequency */
#define	GetPeripheralClock()	(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()	(SYS_FREQ)                         /**< Instructions frequency */
#define PBCLK       SYS_FREQ/2
#define Fsck        375000
#define BRG         100000//(PBCLK/2/Fsck)                         /**< I2C frequency */
#define TIMER_1_INT_VECTOR 4                                       /**< Interruption Vector */

#define ACC_EXT_CAL 0                   /**< 1 - Using Calibrated Matrix; 0 - Default */
#define MAG_EXT_CAL 0                   /**< 1 - Using Calibrated Matrix; 0 - Default */

#define Gyrodps     SENSITIVITY_500DPS  /**< Define gyro sensitivity in use */
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
    // Read RawValues
    
    sensor_xyz gyro_raw,
               acc_raw,
               mag_raw;
    //
    data_xyz gyro,
             acc,
             mag;

    float time_elapsed = 0;
    unsigned int temptime;
    short temp;
    UINT8 test;
    float x,y,z;


    InitUART();
    OpenI2C1( I2C_EN, BRG );    //Enable I2C channel
    InitMARG ();
    AutoCalibrateGyro();
    // AutoCalibrateAcc();
    InitTimer1();
    WriteTimer1(0x00);  // Timer set to 0
    while(1)
    {
        ReadGyroXYZ  ( & gyro );
        ReadAccXYZ   ( & acc  );
        ReadMagXYZ   ( & mag  );
//        ReadGyroRaw   ( & gyro_raw  );

        temptime = ReadTimer1(); // Reads time elapsed
        WriteTimer1(0x00);  // Timer set to 0
        time_elapsed = time_elapsed + (float)((double) (temptime * T1overflow * 256 * 2) / PBCLK); // tempo = valortimer*overflow*prescaler*2/fosc ;
        T1overflow = 1;

        sprintf(buf," %f %f %f",(float) gyro.x*Gyrodps,(float) gyro.y*Gyrodps,(float) gyro.z*Gyrodps );
        SendDataBuffer(buf, strlen(buf));
//        sprintf(buf," %f %f %f",(float) gyro_raw.x*Gyrodps,(float) gyro_raw.y*Gyrodps,(float) gyro_raw.z*Gyrodps );
//        SendDataBuffer(buf, strlen(buf));
        sprintf(buf," %f %f %f",(float) acc.x*AccG,(float) acc.y*AccG,(float) acc.z*AccG );//,(float) acc_raw.x,(float) acc_raw.y,(float) acc_raw.z );//
        SendDataBuffer(buf, strlen(buf));
        sprintf(buf," %f %f %f",(float) mag.x*MagGauss,(float) mag.y*MagGauss,(float) mag.z*MagGauss );
        SendDataBuffer(buf, strlen(buf));
        sprintf(buf, " %f\n", time_elapsed );
        SendDataBuffer(buf, strlen(buf));

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
    UARTSetDataRate(UART_MODULE_ID, GetPeripheralClock(), 115200);
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