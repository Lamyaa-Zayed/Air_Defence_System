/*******************************************************

Project : Missile_Launcher
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

#include <mega16.h>
#include "Missile_Launcher.h"
// Alphanumeric LCD functions
#include <alcd.h>
#include <delay.h>
// Standard Input/Output functions
#include <stdio.h>

// Declare your global variables here
//static unsigned char Missile_Launcher;
unsigned char LEDs_NUM=0;
static Coordinates Target;
static unsigned char Count;

void Missile_Launcher_init()
 {
    PORTB&=~(1<<Launcher_1)|(1<<Launcher_2)|(1<<Launcher_3)|(1<<Launcher_4)|(1<<Launcher_5)|(1<<Launcher_6)|(1<<Launcher_7)|(1<<Launcher_8);;
 }  
 
 Coordinates UART_Slave_Driver(void)     //read (receive) uart msg
 {
    unsigned char i;
    while(!(UCSRA & (1<<RXC)));
   //Count++;
   Target.ID=UDR; 
   while(!(UCSRA & (1<<RXC)));
   Count++;
   Target.x=UDR;
    while(!(UCSRA & (1<<RXC)));
   Count++;
   Target.y=UDR;
    while(!(UCSRA & (1<<RXC)));
   Count++;
   Target.z=UDR;
   
   LEDs_NUM=Count/3;
   if(LEDs_NUM !=0)
   {
     for(i=0;i<LEDs_NUM;i++)
    {
        if(Target.ID==i)
        PORTB|=(1<<i);
    }
    }
   else
   {
        PORTB=0;
   }  
   return (Target);
 }  
 
 
void LCD_Display()
 {  
   unsigned char Str1[17]="                ";
   //unsigned char CHR;
   static unsigned char CH = '0';
   
   // void _lcd_write_data(Missile_Launcher)
    // void char lcd_init(unsigned char lcd_columns)
     //lcd_clear();
     lcd_gotoxy(0,0);
     lcd_puts("Launched M #");
       
     lcd_gotoxy(14,0);
     lcd_puts("AT");
     
     lcd_gotoxy(12,0);
     lcd_putchar(CH+LEDs_NUM);
     
     lcd_gotoxy(0,1);
     lcd_puts(Str1);
      
     lcd_gotoxy(0,1);
     sprintf(Str1,"%dID ",Target.ID);
     lcd_puts(Str1); 
     sprintf(Str1,"%dX",Target.x);
     lcd_puts(Str1);  
     sprintf(Str1," %dY",Target.y);
     lcd_puts(Str1);
     sprintf(Str1," %dZ",Target.z);
     lcd_puts(Str1);
     
    /* lcd_gotoxy(7,1);
     lcd_puts(Str2); 
     lcd_gotoxy(7,1);
     lcd_putchar(CH++); */
     //delay_ms(2000);
    //char lcd_buffer[16];
    //sprintf(lcd_buffer,"Uadc=%4umV",read_adc());
      //lcd_clear();
      //lcd_puts(lcd_buffer);
 }
   
 /*void Launcher_Indicator()
 {
   
 } */ 
 
void main(void)
{
// Declare your local variables here
    Missile_Launcher_Conf();
    Missile_Launcher_init();
    lcd_init(16);

    while (1)
        {
        // Place your code here
           UART_Slave_Driver();
           LCD_Display();
          // Launcher_Indicator();
        }
}
