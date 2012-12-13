
#include "inc/lm4f120h5qr.h"
#include "lcd_1602_lm4f.h"
#include "systick.h"

void lcd_putch(char c)
{
  LCD_RS(1); 
  
  delay_ms(2);       
  
  LCD_DATA = ((c & 0xF0) >> 4);
  EN_ACKAPA();
  LCD_DATA =  (c & 0x0F);
  EN_ACKAPA();
}

void lcd_komut(unsigned char c)
{
  LCD_RS(0);
  
  delay_ms(2);      
  
  LCD_DATA = ((c & 0xF0) >> 4);
  EN_ACKAPA();
  LCD_DATA =  (c & 0x0F);
  EN_ACKAPA();
}

void lcd_temizle(void)
{  
  lcd_komut(0x01);
  delay_ms(10);
}

void lcd_puts(const char* s)
{ 
  while(*s)
    lcd_putch(*s++);
}

void lcd_goto(char x, char y)
{ 
  if(x==1)
    lcd_komut(0x80+((y-1)%16));
  else
    lcd_komut(0xC0+((y-1)%16));
}
	
void lcd_init()
{
  SYSCTL_RCGC2_R     |=  SYSCTL_RCGC2_GPIOB;	// GPIOB Aktif
  GPIO_PORTB_DIR_R   |=  0x03;          
  GPIO_PORTB_AFSEL_R &= ~0x03;          
  GPIO_PORTB_DEN_R   |=  0x03;          
  GPIO_PORTB_PCTL_R   =  0xFFFFFF00;    
  GPIO_PORTB_AMSEL_R &=  0x03;          

  SYSCTL_RCGC2_R     |=  SYSCTL_RCGC2_GPIOD;	// GPIOD Aktif
  GPIO_PORTD_DIR_R   |=  0x0F;          
  GPIO_PORTD_AFSEL_R &= ~0x0F;          
  GPIO_PORTD_DEN_R   |=  0x0F;          
  GPIO_PORTD_PCTL_R  &=  0xFFFF0000;    
  GPIO_PORTD_AMSEL_R &= ~0x0F;          

  LCD_RS(0);
  LCD_EN(0);

  lcd_komut(0x28);  // 4 Bit , Çift Satýr LCD
  lcd_komut(0x0C);  // Ýmleç Gizleniyor
  lcd_komut(0x06);  // Saða doðru yazma aktif
  lcd_komut(0x80);  // LCD Birinci Satýr Konumunda
  lcd_komut(0x28);  // 4 Bit , Çift Satýr LCD
  lcd_temizle();    // Ekran Temizleniyor 
}
