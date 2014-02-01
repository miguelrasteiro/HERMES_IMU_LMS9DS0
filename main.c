/*
 * File:   main.c
 * Author: MiguelRasteiro
 *
 * Created on 29 de Janeiro de 2014, 10:14
 */

#include <p32xxxx.h>
#include <plib.h>
#include "pic_config.h"
#include "lsm9ds0.h"
#include "uart.h"

// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 80 MHz (SYSCLK / FPBDIV)
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1

#define SYS_FREQ (80000000L)
#define	GetPeripheralClock()	(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()	(SYS_FREQ)
#define PBCLK       SYS_FREQ/2
#define Fsck        375000
#define BRG         100000//(PBCLK/2/Fsck)

// Constant Data
const char mainMenu[] = {
    "LSM9DS0 I2C test.\r\n"\
    "Choose one:\r\n"\
    "1. Gyro raw data\r\n"\
    "2. Acc Magn raw data\r\n\r"
};

// Function Prototypes
void initUART(void);

int main(void)
{
    // UART Variables
    UINT32  menu_choice;
    UINT8   buf[1024];
    sensor_raw gyro_raw, 
               acc_raw,
               mag_raw;
    short temp;


    initUART();
    OpenI2C1( I2C_EN, BRG );    //Enable I2C channel

    //activate accelerometer
    WriteRegister ( Address_XM, CTRL_REG1_XM, 0B00110111 ); // acc odr 12.5 Hz, continuous update, axis enable
    WriteRegister ( Address_XM, CTRL_REG2_XM, 0B00001000 ); // ±4 g
    WriteRegister ( Address_XM, CTRL_REG5_XM, 0B11101000 ); // temperature enable, mag high resolution, mag odr 12.5 hz
    WriteRegister ( Address_XM, CTRL_REG6_XM, 0B00100000 ); // ±4 gauss
    WriteRegister ( Address_XM, CTRL_REG7_XM, 0B00000000 ); // continuos Mag conversion
    //activate gyro
    WriteRegister ( Address_G, CTRL_REG1_G, 0B00001111 );   // gyro enable
    WriteRegister ( Address_G, CTRL_REG4_G, 0B00010000 );   // 500 dps

    SendDataBuffer(mainMenu, sizeof(mainMenu));

    while(1)
    {
    ReadGyro ( & gyro_raw );
    ReadAcc  ( & acc_raw  );
    ReadMag  ( & mag_raw  );
    ReadTemp ( & temp  );

    sprintf(buf, " G_X: %.1f G_Y: %.1f G_Z: %.1f",(float) (gyro_raw.x-385)*0.0175,(float) (gyro_raw.y-50)*0.0175,(float) (gyro_raw.z-125)*0.0175 );
    SendDataBuffer(buf, strlen(buf));
    sprintf(buf, " A_X: %.1f A_Y: %.1f A_Z: %.1f",(float) acc_raw.x*0.000122,(float) acc_raw.y*0.000122,(float) acc_raw.z*0.000122 );
    SendDataBuffer(buf, strlen(buf));
    sprintf(buf, " M_X: %.1f M_Y: %.1f M_Z: %.1f",(float) mag_raw.x*0.016,(float) mag_raw.y*0.016,(float) mag_raw.z*0.016 );
    SendDataBuffer(buf, strlen(buf));
    sprintf(buf, " Temp: %d \n", temp );
    SendDataBuffer(buf, strlen(buf));


/*
        menu_choice = GetMenuChoice();

        switch(menu_choice)
        {
        case 1:
            sprintf(buf, "Actual Baud Rate: %ld\r\n\r\n", UARTGetDataRate(UART_MODULE_ID, GetPeripheralClock()));
            SendDataBuffer(buf, strlen(buf));
            break;

        case 2:
            SendDataBuffer("choise number 2\r\n", strlen("Press 'U' to allow AUTO BAUD to sync\r\n"));
            break;

        default:
            SendDataBuffer(mainMenu, sizeof(mainMenu));

        }*/
    }

    return -1;
}

void initUART(void){
    UARTConfigure(UART_MODULE_ID, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UART_MODULE_ID, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART_MODULE_ID, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART_MODULE_ID, GetPeripheralClock(), 57600);
    UARTEnable(UART_MODULE_ID, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
}