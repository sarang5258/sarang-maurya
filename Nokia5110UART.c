/*Nokia LCD Display*/

// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected
// Ground        (Gnd, pin 8) ground

// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected

#include <stdint.h>
#include "Nokia5110.h"
#include "PLL.h"
#include "UART.h"

// delay function for testing from sysctl.c
// which delays 3*ulCount cycles

void Delay(unsigned long ulCount){
  do{
    ulCount--;
	}while(ulCount);
}


void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}
// image of a IIITDM
const unsigned char Longhorn [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
0x00, 0x00, 0x30, 0xF8, 0xD8, 0x18, 0x30, 0x30, 0x60, 0x60, 0xC0, 0xFE, 0x7F, 0x03, 0x06, 0x06,
0x0C, 0x38, 0x30, 0x30, 0x30, 0x3C, 0x8F, 0xC3, 0xC1, 0x83, 0x1E, 0x3C, 0x30, 0x30, 0x38, 0x0C,
0x06, 0x03, 0x03, 0x7F, 0x7E, 0xC0, 0x60, 0x20, 0x30, 0x18, 0x98, 0xE8, 0xF8, 0x10, 0x00, 0x00,
0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xE0, 0xE0, 0xE0, 0x60, 0x60, 0x63,
0x67, 0x6D, 0x79, 0x73, 0x33, 0x02, 0x06, 0x06, 0x07, 0x83, 0xC0, 0xC0, 0xC6, 0xC4, 0xCC, 0xC8,
0xD8, 0xD8, 0xF0, 0xB0, 0xF0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC4, 0xDF, 0xFF, 0xFF, 0xDF, 0xCE, 0xE0,
0xE0, 0xE0, 0xE0, 0xF0, 0xB0, 0xF8, 0xD8, 0xD8, 0xCC, 0xCC, 0xC4, 0xC6, 0xC0, 0xC0, 0x83, 0x83,
0x06, 0x03, 0x03, 0x03, 0x31, 0x79, 0x6D, 0x67, 0x23, 0x20, 0xB0, 0xB0, 0xF0, 0xE0, 0x60, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x38, 0x78, 0x78, 0x59,
0xC9, 0xCB, 0xCB, 0x8E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x81, 0xC3, 0x63, 0xB7, 0xFF, 0x7F, 0x3F,
0x1F, 0x3E, 0xFF, 0xFF, 0xF3, 0xE3, 0xC3, 0x81, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0xCD, 0x6D,
0x6C, 0x6C, 0x2C, 0x3C, 0x38, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C,
0x1C, 0x16, 0x16, 0x12, 0x92, 0x93, 0xD3, 0x71, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF8, 0xFE, 0x8F, 0xE3, 0xFD, 0x7F,
0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0xFE, 0xFD, 0xC7, 0x9F, 0xFC, 0xF0, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x20, 0x78, 0x59, 0xD9, 0xDB, 0x9B, 0x1B, 0x0A, 0x0E, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x07, 0x05, 0x06, 0x06, 0x86, 0xE6, 0xF6, 0x9A, 0xDE,
0xCC, 0xC0, 0x60, 0x60, 0x60, 0xC0, 0xC0, 0x70, 0x70, 0x50, 0x76, 0x76, 0x70, 0x71, 0x71, 0x71,
0x7F, 0x5F, 0x7F, 0x7E, 0x2E, 0x7F, 0x7E, 0x73, 0x7E, 0x7B, 0x7A, 0x7E, 0x7E, 0x3E, 0x7D, 0x6F,
0x7F, 0x71, 0x71, 0x71, 0x60, 0x76, 0x66, 0x70, 0x70, 0x70, 0x70, 0xC0, 0xE0, 0x20, 0x60, 0x60,
0x44, 0xCE, 0xDF, 0xDB, 0xF2, 0x62, 0x02, 0x02, 0x06, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x1F, 0x1B, 0x08, 0x0C, 0x04, 0x06, 0x03, 0x03,
0x3F, 0x7E, 0x40, 0x60, 0x30, 0x38, 0x0C, 0x04, 0x04, 0x3C, 0x78, 0xC0, 0x80, 0xE0, 0x78, 0x1C,
0x0C, 0x04, 0x04, 0x1C, 0x18, 0x30, 0x60, 0x62, 0x7F, 0x3F, 0x03, 0x03, 0x06, 0x06, 0x0C, 0x0C,
0x0B, 0x0F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// image of a I love ELE403P


const uint8_t Longhorn2[] ={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0xC0,
0xC0, 0xC0, 0xC0, 0xC0, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00,
0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01,
0x03, 0x03, 0x07, 0x0F, 0x1E, 0x0F, 0x07, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0xFF,
0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0C, 0x0F, 0x0F, 0x0F, 0x0C, 0x08, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x3C,
0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0,
0xF8, 0x7C, 0x1F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x0F, 0x1E, 0x3C, 0x78, 0x3C, 0x1E, 0x0F,
0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0xFF, 0xFF, 0x11, 0x11,
0x7D, 0x01, 0x83, 0xC7, 0x00, 0x01, 0x01, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0x00, 0x80, 0xE0, 0x00,
0x01, 0x01, 0xFF, 0xFF, 0x11, 0x11, 0x7D, 0x01, 0x83, 0xC7, 0x00, 0x60, 0x50, 0x48, 0x44, 0xFE,
0xFF, 0x40, 0x40, 0x00, 0x7C, 0xFE, 0x01, 0x01, 0x81, 0x7E, 0x38, 0x00, 0x02, 0x02, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x01, 0x01, 0xFF, 0xFF, 0x11, 0x11, 0x11, 0x12, 0x1E, 0x0C, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

int main(void){
	unsigned char i;
  char string[20];  // global to assist in debugging
  unsigned long n;
  uint32_t count = 0;
  PLL_Init(); 
	UART_Init();              // initialize UART
  OutCRLF();	// set system clock to 50 MHz
  Nokia5110_Init();
	Nokia5110_Clear();
  for(count=0; count<2; count=count+1){
		UART_OutString("Wait ");
   Nokia5110_DrawFullImage(Longhorn);
    Delay(16666667);                    // delay ~1 sec at 50 MHz
   Nokia5110_DrawFullImage(Longhorn2);
    Delay(16666667);                    // delay ~1 sec at 50 MHz
  }
	
  

 Nokia5110_Clear();
	Nokia5110_SetCursor(0,0);
           
  while(1){
		UART_OutString("Enter the text: ");
    UART_InString(string,19);
    UART_OutString(" Your Text="); UART_OutString(string); OutCRLF();
	 		
		Nokia5110_OutString(string);
		OutCRLF();
  UART_OutChar('-');
  UART_OutChar('-');
  UART_OutChar('>');
	
  }
           
  
}
