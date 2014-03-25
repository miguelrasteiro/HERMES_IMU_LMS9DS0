 /**
  * \addtogroup uart
  * \{
  * \file uart.h
  * \brief Modified example from <https://www.microchip.com/CodeExamplesByFunc.aspx> \n
  * \author Microchip Technology Inc. \n\t
  * \date 30 January de 2014, 15:38 \n\n
  * \ref license_microchip \n\n
  *    Change History:
  * *********************************
  * | VERSION      | DATE	    | 
  * |:------------:|:--------------:|
  * | 1.0          |   30/1/2014    |
  */
#include <plib.h>

#ifndef UART_H
#define	UART_H


#define UART_MODULE_ID UART1 // PIM is connected to Explorer through UART2 module

void SendDataBuffer(const char *buffer, UINT32 size);
UINT32 GetMenuChoice(void);

#endif	/* UART_H */
/** \} */
