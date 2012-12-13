/* 
* pll.h
*
* M.Fatih INANC
* fatihinanc.com
* 
* 07.12.2012
*/

#include "inc/lm4f120h5qr.h"
#include "inc/hw_sysctl.h"
#include "pll.h"

// 400MHz/(2*SYSDIV+1+LSB) = 400MHz/(2*3+1+1) = 50 MHz

void pll_init(void)
{
  
  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
  SYSCTL_RCC_R  &= ~SYSCTL_RCC_XTAL_M; 
  SYSCTL_RCC_R  |= SYSCTL_RCC_XTAL_16MHZ;  	// 16 MHz Kristal Secildi.
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M; 
  SYSCTL_RCC2_R |= SYSCTL_RCC2_OSCSRC2_MO; 	// Kristal MAIN OSC Secildi.
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;		// Bus Frekansi = 400 MHz PLL
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_SYSDIV2_M;  
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_SYSDIV2LSB;

	//((2*sysdiv) + 1 + lsb) sysdiv = 3 , lsb = 1;
  set_cpu_freq(3,1); 

  while((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0);
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}

void set_cpu_freq(char sysdiv, char lsb)
{
  SYSCTL_RCC2_R &= ~0x1FC00000;
  SYSCTL_RCC2_R |= (sysdiv << 23) | (lsb << 22);
}

unsigned long get_cpu_freq(void)
{
  char sysdiv,lsb;
 
  sysdiv = (SYSCTL_RCC2_R & 0x1F800000) >> 23;
  lsb    = (SYSCTL_RCC2_R &   0x400000) >> 22;
   
  return ((unsigned long)(400000000)/(2 * sysdiv + 1 + lsb));
}
