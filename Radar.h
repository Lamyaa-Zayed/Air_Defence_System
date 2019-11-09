#ifndef _Radar_H_
#define _Radar_H_

#include <mega16.h>
#include <stdio.h>
#include <delay.h>

typedef struct 
    {
    unsigned char x;
    unsigned char y;
    unsigned char z;
    } Coordinates;    

extern void Radar_Conf();
extern void Radar_init();
//extern void Radar_Coordinates();
//extern void Flash_LED();
extern void SPI_Master_Driver(Coordinates *Target);
extern void LCD_Display(void);

#endif 