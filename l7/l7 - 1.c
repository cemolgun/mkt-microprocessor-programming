#include <16F887.h>
#include <stdlib.h>
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay (clock = 4M)

#use rs232(baud=9600, uart1)

#define use_portb_lcd TRUE
#include <lcd.c>

int Kp = 0;
int Ki = 0;
int Kd = 0;

void main()
{
   lcd_init();
   setup_uart(9600);

   char receive[10] = {0};
   while (1)
   {
      gets(receive);
      printf(lcd_putc, "\fR: %s", receive);
      
      for (int i = 0; i < 9; i++)
      {
         if (receive[i] == 'P' || receive[i] == 'I' || receive[i] == 'D')
            receive[i] = '\0';
      }
      Kp = atoi(receive);
      Ki = atoi(receive + 3);
      Kd = atoi(receive + 6);
      
      printf(lcd_putc, "\fKp:%u   Ki:%u\nKd:%u", Kp, Ki, Kd);
   }
}
