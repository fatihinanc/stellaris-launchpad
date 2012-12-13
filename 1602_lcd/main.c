
#include "inc/lm4f120h5qr.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "lcd_1602_lm4f.h"
#include "systick.h"
#include "pll.h"

unsigned long cpu_freq;

int main(void)
{
  pll_init();              
  systick_init();
  
  set_cpu_freq(3,1);         // 50 MHz
  cpu_freq = get_cpu_freq();
  
  lcd_init();
  delay_ms(1000);
  
  lcd_puts("LM4F120LaunchPad");
  lcd_goto(2,2);
  lcd_puts("2x16 LCD Testi");
  
  while(1);
}
