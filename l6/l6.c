#include <16F887.h>
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay (clock = 4M)
#use fast_io(C)

void main()
{
   set_tris_c(0b00000000);
   output_c(0b00000100);   //only c2 is on
   
   setup_ccp2(CCP_PWM);
   setup_timer_2(T2_DIV_BY_16, 255, 1); //Timer2 setup determines period
   
   int16 pwm_val = 300;
   set_pwm2_duty(pwm_val);
   
   while(1)
   {
      if (input_a() & 0b00000001)  //if toggle button is pressed
      {
         while(input_a() & 0b00000001){}     //wait while button is still on
         output_c(input_c() ^ 0b00001100);   //reverse c2 and c3
      }
      
      if (input_a() & 0b00000010)   //if increase button is pressed
      {
         if (pwm_val < 1000) 
            pwm_val += 100;
         set_pwm2_duty(pwm_val);
         delay_ms(150);
      }
      
      if (input_a() & 0b00000100)   //if decrease button is pressed
      {
         if (pwm_val > 100) 
            pwm_val -= 100;
         set_pwm2_duty(pwm_val);
         delay_ms(150);
      }
   }
}
