#include <16F887.h>
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay (clock = 4M)
#define use_portb_lcd TRUE
#include <lcd.c>
#use fast_io(D)

// X: 1,    2,    3
// Y: A(2), B(1), C(0)
// rule: number = (x + 3Y)

int get_input()
{
   int x = 0;
   for (int y = 0; y < 4; y++)
   {
      output_D(1 << y);
      x = (input_D() & 0b01110000) >> 4;
      x = (x == 4) ? 3 : x;
      if (x)
      {
         int num = x+(3*y);
         num = (num == 11)? 0 : num;
         output_D(0x00);
         return num;
      }
   }
   return 0xFF;
}

void get_num(int* n)
{
   int input = get_input();
   if (input != 0xFF && input <= 9)
      {
         if (*n <= 9)
         {
            *n *= 10;
            *n += input;
         }
         else
         {
            *n = 0;
            printf(lcd_putc, "\f\fError:\n2 dig limit");
            delay_ms(1000);
         }
         printf(lcd_putc, "\f\f%d", *n);   
         delay_ms(1000);
      }
}

void main()
{
   set_tris_b(0x00);
   set_tris_d(0xF0);
   lcd_init();

   int n1 = 0;
   int n2 = 0;
   int* wrt = &n1;
   while (1)
   {
      lcd_cursor_on(TRUE);
      
      int input = get_input();
      if (input <= 9)
         get_num(wrt);
         
      if (input == 10)
      {
         printf(lcd_putc,"\f\f");
         wrt = &n2;
      }
      if (input == 12)
      {
         printf(lcd_putc,"\f\fResult:\n%u", n1+n2);
         delay_ms(2000);
         printf(lcd_putc,"\f\f");
         n1 = 0;
         n2 = 0;
         wrt = &n1;
      }
   }
}
