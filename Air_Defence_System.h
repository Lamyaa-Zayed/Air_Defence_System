#ifndef _Air__Defence_System_H_
#define _Sir_Defence_System_H_

#include <mega16.h>
#include <delay.h>
#include <stdio.h>
#include <string.h> 
             
 typedef struct 
    {
    unsigned char x;
    unsigned char y;
    unsigned char z;
    } Coordinates;      

//typedef enum {False=0,True} boolean;
extern void Air_Defence_System_configuration();
extern void Air_Defence_init();
extern void Target_Serine_Gen();
extern void Alarm_Serine_Gen();
extern void LCD_Display();
extern void SPI_Slave_Driver();
extern void UART_Master_Driver();

// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

#endif 