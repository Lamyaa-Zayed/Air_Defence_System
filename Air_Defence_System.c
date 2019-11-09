/*******************************************************

Project : Air Defence System
Version : 1.1
Date    : 04/11/2019
Author  : Lamyaa Zayed
Company : Just Dream
Comments: 
Air Defence System contains: (Three micro-controllers Atmega16) Radar, Wind_Speed meter, Missile_Launcher as inputs and Target_Serine, Alarm_Serine as outputs. 
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


#include "Air_Defence_System.h"

// Alphanumeric LCD functions
#include <alcd.h>
// Standard Input/Output functions
#include <stdio.h>
// SPI functions
#include <spi.h>

// Declare your global variables here
#define Target_Serine 0
#define Alarm_Serine 1
#define Check_LED 3

 static unsigned int Wind_Speed_Reading;
 //static unsigned char Detected_Target;
 static unsigned char SPDR_Count;
 static unsigned char Missile_NUM;
 static Coordinates Target;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Reinitialize Timer 0 value
TCNT0=0x83;
// Place your code here

}


// ADC interrupt service routine
interrupt [ADC_INT] void adc_isr(void)
{
unsigned int adc_data;
// Read the AD conversion result
adc_data=ADCW;
// Place your code here
/*unsigned char adc_data;
// Read the 8 most significant bits
// of the AD conversion result
adc_data=ADCH;
// Place your code here*/
     //ADMUX=0;            //select channel 0
    ADCSRA |= (1<<ADSC)| (1<<ADATE); 
    Wind_Speed_Reading = adc_data; 
  
}

 void LCD_Display(void)
 {   
    unsigned char Str[6]="     ";
    /*
      lcd_gotoxy(0,1);
     lcd_puts(Str); 
     lcd_gotoxy(0,1);
    
     sprintf(Str,"%dX ",Target.x);
     lcd_puts(Str);
     sprintf(Str,"%dY ",Target.y);
     lcd_puts(Str);
     sprintf(Str,"%dZ",Target.z);
     lcd_puts(Str);
    */
     lcd_gotoxy(0,0);
     lcd_puts("Wind_Speed is: ");
     lcd_gotoxy(9,1);
     lcd_puts("RPM ");
     lcd_gotoxy(3,1);
     lcd_puts(Str); 
     lcd_gotoxy(3,1);
     sprintf(Str,"%d",Wind_Speed_Reading);
     lcd_puts(Str);   
 }  
 
void Air_Defence_init()
 {
      PORTB&=~(1<<Target_Serine);
      PORTB&=~(1<<Alarm_Serine);
          
 } 
 
 void SPI_Slave_Driver()      //read (receive) spi meg
 {  
    while(!(SPSR & (1<<SPIF)));
    Target.x=SPDR;
    SPDR_Count++;
    while(!(SPSR & (1<<SPIF)));
    Target.y=SPDR;
    SPDR_Count++;
    while(!(SPSR & (1<<SPIF)));
    Target.z=SPDR;
    SPDR_Count++;

      
 }  
 
 void Target_Serine_Gen()
 {
    if(SPDR_Count%3==0)
    PORTB|=(1<<Target_Serine);
 }
 
 void Alarm_Serine_Gen()
 {
  if(SPDR_Count>24)
  PORTB|=(1<<Alarm_Serine);  
 }
 
 void UART_Master_Driver(void)     //write (transmitt) uart msg
 {
   static unsigned char i;
   Target.ID=i;
   UDR=Target.ID;
   while(!(UCSRA & (1<<TXC)));
   delay_ms(100);
   UDR=Target.x;
   while(!(UCSRA & (1<<TXC)));
   Missile_NUM++;
   delay_ms(100);
   UDR=Target.y;
   while(!(UCSRA & (1<<TXC)));
   Missile_NUM++;
   delay_ms(100);
   UDR=Target.z;
   while(!(UCSRA & (1<<TXC)));
   Missile_NUM++;
   delay_ms(100);
   i++;
   i=i%10; 
 } 
 
 void Stop_Missile_Sender(void)
 {
   if(Missile_NUM>24)
   UCSRB&=~(1<<TXEN); 
 } 
 
 void Flasher(void)
 {
 PORTA|=(1<<Check_LED);
 delay_ms(250);
 PORTA&=~(1<<Check_LED);
 delay_ms(250);
 }
 
void main(void)
 {
    Air_Defence_System_configuration();
    lcd_init(16);
    Air_Defence_init();
    //unsigned char Data;
    // Global enable interrupts
    #asm("sei")
    while (1)
         {                         
         // Place your code here
          LCD_Display();
          SPI_Slave_Driver(); 
          Target_Serine_Gen();
          Alarm_Serine_Gen();
          UART_Master_Driver();
          Stop_Missile_Sender();
          Flasher();
          
          //MCUCR |=(1<<SE);
        }
 }
