#include <16F887.h>
#device adc = 10
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay (clock = 4M)
#define use_portb_lcd TRUE
#include <lcd.c>

int16 a0;
int16 a1;

void read_and_print()
{
   set_adc_channel(0);
   delay_us(10);
   a0 = read_adc();
   set_adc_channel(1);
   delay_us(10);
   a1 = read_adc();
   printf(lcd_putc,"\f\fA0:%lu\nA1:%lu", a0, a1);
   delay_ms(200);
}

int overflow = 0;

#INT_TIMER1
void timer1_interrupt()
{
   clear_interrupt(INT_TIMER1);
   set_timer1(1536);
   
   overflow++;
   if (overflow == 5)
   {
      read_and_print();
      overflow = 0;
   }  
}

void main()
{
   lcd_init();
   
   setup_adc_ports(sAN0 | sAN1);
   setup_adc(ADC_CLOCK_DIV_32);
   
   //Enable timer1 interrupt
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
   clear_interrupt(INT_TIMER1);
   
   //T1 increase every 8us max from 1536 to 65536
   //T1 overflow every 0.4 sec
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   set_timer1(1536);
   
   read_and_print();
   
   while (1)
   {  
   }
}
