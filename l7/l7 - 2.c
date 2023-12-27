#include <16F887.h>
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay (clock = 4M)

#use rs232(baud=9600, uart1)

#define use_portb_lcd TRUE
#include <lcd.c>

//21067030
//abcd efg

void main()
{
   lcd_init();
   setup_uart(9600);
   
   int a = 0;
   while (1)
   {
      printf("23P60I63D\r");
      delay_ms(1000);
   }
}
