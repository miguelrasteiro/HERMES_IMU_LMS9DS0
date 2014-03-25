 /**
  * \addtogroup uart
  * \{
  * \file uart.c
  * \brief Modified example from <https://www.microchip.com/CodeExamplesByFunc.aspx> \n
  * \author Microchip Technology Inc. \n\t
  * \date     30 January de 2014, 15:38 \n\n
  * \ref license_microchip \n\n
  *    Change History:
  * *********************************
  * | VERSION      | DATE	    |
  * |:------------:|:--------------:|
  * | 1.0          |   30/1/2014    |
  * \n\n
  *
  * \section uartcode UART Source Code
  * \code
  */
/*********************************************************************
 *
 *      PIC32MX UART Library Interface Example
 *
 *********************************************************************
 * FileName:        uart_basic.c
 * Dependencies:    plib.h
 *
 * Processor:       PIC32MX
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc.
 *
 * The purpose of this example code is to demonstrate the PIC32MX
 * peripheral library macros and functions supporting the UART
 * module and its various features.
 *
 * Platform: Explorer-16 with PIC32MX PIM
 *
 * Features demonstrated:
 *    - UART perepheral library usage
 *
 * Description:
 *      This program uses the UART library to communicate through
 *      the serial port on the Explorer-16. With an RS232 cable
 *      attatched to the Explorer-16 and a pc, the program will
 *      output text and recieve input using a terminal program.
 *
 * Notes:
 *    - PIC32MX 2xx PIMS are unconnected to the Explorer-16 DB9
 *      connector. It must be soldered to the test points on top of
 *      the PIM for proper functionality. The README file contains
 *      a list of the connections that need to be made.
 ********************************************************************/
#include "uart.h"

// *****************************************************************************
// void UARTTxBuffer(char *buffer, UINT32 size)
// *****************************************************************************
void SendDataBuffer(const char *buffer, UINT32 size)
{
    while(size)
    {
        while(!UARTTransmitterIsReady(UART_MODULE_ID))
            ;

        UARTSendDataByte(UART_MODULE_ID, *buffer);

        buffer++;
        size--;
    }

    while(!UARTTransmissionHasCompleted(UART_MODULE_ID))
        ;
}

// *****************************************************************************
// UINT32 GetMenuChoice(void)
// *****************************************************************************
UINT32 GetMenuChoice(void)
{
    UINT8  menu_item;

    while(!UARTReceivedDataIsAvailable(UART_MODULE_ID))
        ;

    menu_item = UARTGetDataByte(UART_MODULE_ID);

    menu_item -= '0';

    return (UINT32)menu_item;
}
/**\endcode */