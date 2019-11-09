/*******************************************************

Project : Radar
Version : 1.1
Date    : 05/11/2019
Author  : Lamyaa Zayed
Company : Just Dream
Comments: 
Air Defence System contains: Radar, Wind_Speed meter, Missile_Launcher as inputs and Target_Serine, Alarm_Serine as outputs. 
Radar gives you the number of detected target, Wind_Speed meter gives you analog signal which is propotional to the measured wind speed, 
Missile_Launcher has 8 missiles; reads a digital value to determine which missile out of 8 should be launched. 
when radar detects target, sys immediately activates the Target_Serine. 
If the reading of radar indicates more than 8 targets; sys activates Alarm_Serine.


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include "Radar.h"

// SPI functions
#include <spi.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
#define Target_Launched 0
static unsigned char i,j;
static unsigned char count;
static Coordinates Target[10];

/*typedef struct 
    {
    unsigned char x;
    unsigned char y;
    unsigned char z;
    } Coordinates; */   

//static Coordinates valueToSend; 
/* void Radar_Coordinates()
 {
    
    for (i=1;i<=10;i++)
    {
        (Target[i].x = i*3.5);
        (Target[i].y = i*3.5);
        (Target[i].z = i*3.5);
        delay_ms(1000);
        //return Target[i];
    }  
    
 } */ 
 
// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
    SPI_Master_Driver(Target);
    LCD_Display();
}

void Radar_init()
 {
    PORTC&=~(1<<Target_Launched); 
 } 

void SPI_Master_Driver(Coordinates *Target)
 {
        Target[j].x = j*2.5;
        SPDR =Target[j].x;
        while(!(SPSR & (1<<SPIF)));         
        count++;
        delay_ms(100); 
        Target[j].y = j*3.5;       
        SPDR =Target[j].y;
        while(!(SPSR & (1<<SPIF)));
        count++;
        delay_ms(100);
        Target[j].z = j*4.5;
        SPDR =Target[j].z;
        while(!(SPSR & (1<<SPIF)));
        count++;
        delay_ms(100); 
        
        j++;
        j=j%10;
        
    if(count%3==0)
    {
        PORTC|=(1<<Target_Launched);
        delay_ms(300);
        PORTC&=~(1<<Target_Launched);
    }
 }  
 
void LCD_Display(void)
 {
   unsigned char Str[6]="     ";
   if(j==0) 
   i=9;
   else
   i=j-1;
     
     lcd_gotoxy(0,0);
     lcd_puts("Coordinates #");
     
     lcd_gotoxy(0,13);
     lcd_putchar((i|0x30));
     
     lcd_gotoxy(11,1);
     lcd_puts(" Axis");
     
     lcd_gotoxy(0,1);
     lcd_puts(Str); 
     lcd_gotoxy(0,1);
 
     sprintf(Str,"%dX ",Target[i].x);
     lcd_puts(Str);
     sprintf(Str,"%dY ",Target[i].y);
     lcd_puts(Str);
     sprintf(Str,"%dZ",Target[i].z);
     lcd_puts(Str);
 /*   
    delay_ms(100);
     lcd_gotoxy(2,1);
     lcd_puts(Str); 
     lcd_gotoxy(2,1);
     sprintf(Str,"%d Y",Target[j].y);
     lcd_puts(Str);
     delay_ms(100);
     lcd_gotoxy(2,1);
     lcd_puts(Str); 
     lcd_gotoxy(2,1);
     sprintf(Str,"%d Z",Target[i].z);
     lcd_puts(Str);
     delay_ms(100);
*/
     
 }   

void main(void)
{
// Declare your local variables here
   Radar_Conf();
   Radar_init();
   lcd_init(16);
   //Radar_Coordinates();
   
   // Global enable interrupts
#asm("sei")

    while (1)
      {
      // Place your code here
        //Flash_LED(); 
        //MCUCR=(1<<SE);
        //MCUCR&=~((1<<SM0)|(1<<SM1)|(1<<SM2));
        
      }
}
