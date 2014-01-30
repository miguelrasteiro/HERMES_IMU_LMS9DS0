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

#define	GetPeripheralClock()		(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(SYS_FREQ)

// Constant Data
const char mainMenu[] =
{
    "LSM9DS0 I2C test.\r\n"\
    "Choose one:\r\n"\
    "1. Gyro raw data\r\n"\
    "2. Acc Magn raw data\r\n\r"
};

void initUART(void);

int main(void)
{
    UINT32  menu_choice;
    UINT8   buf[1024];

    initUART();

    SendDataBuffer(mainMenu, sizeof(mainMenu));

    while(1)
    {
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

        }
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
