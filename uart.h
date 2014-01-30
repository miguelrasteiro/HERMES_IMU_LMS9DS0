/* 
 * File:   uart.h
 * Author: MiguelRasteiro
 *
 * Created on 30 de Janeiro de 2014, 15:38
 */

#include <plib.h>

#ifndef UART_H
#define	UART_H

#define UART_MODULE_ID UART1 // PIM is connected to Explorer through UART2 module

// Function Prototypes
void SendDataBuffer(const char *buffer, UINT32 size);
UINT32 GetMenuChoice(void);


#endif	/* UART_H */

