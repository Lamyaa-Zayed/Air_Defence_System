#ifndef _Missile_Launcher_H_
#define _Missile_Launcher_H_

extern void Missile_Launcher_Conf();
extern void Missile_Launcher_init();
//extern void Launcher_Indicator();
extern void LCD_Display();

typedef struct 
    {             
    unsigned char ID;
    unsigned char x;
    unsigned char y;
    unsigned char z;
    } Coordinates;  

extern Coordinates UART_Slave_Driver();
    
#define Launcher_1 0
#define Launcher_2 1
#define Launcher_3 2
#define Launcher_4 3
#define Launcher_5 4
#define Launcher_6 5
#define Launcher_7 6
#define Launcher_8 7


#endif 