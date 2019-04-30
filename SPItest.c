#include<LPC21xx.h>
int i=0x0;

void delay()
{
	int k,j;
	
   for(k=0;k<1000;k++)
	 	  {
	 			for(j=0;j<1000;j++)
				{
					;
				}
			}
		
}

void spi_interrupt() __irq		//Interrupt ISR
{
	IO0CLR=0x00000080;	     // Clear Pin
	int dummy;
	  S0SPINT|=(1<<0); 				// clearing Flag
		delay();
	  i++;
		dummy=S0SPSR;						// dummy read to clear Flag
		VICVectAddr=0x00; 	// dummy data to return from Interrupt

}


void interrupt_int(){

  VICIntEnable=(1<<10);		// Only SPI0 Int Enable >>10 bit
  VICVectCntl4=0x20|10;		//		Enabling Slot	
	VICVectAddr4=(unsigned long)spi_interrupt;		// Putting Address.

}

void led_on()
{
	  IO0DIR=(IO0DIR)|(0x80000000);			//LED
	  IO0CLR=0x80000000;
}

void spi_int()
{
		// TAking Slave Select as GPIO for Active High Slave  // Don't do if Slave is active Low
	IO0DIR=(IO0DIR)|0x00000080;	  // SET As Output
  IO0CLR=0x00000080;	  				// 0/Clear Pin
	S0SPCCR=0x10;		    					//PCLK/16		CLKSET
	S0SPCR=0x0060;								// Control Register
	S0SPCR=S0SPCR |(1<<7);				// Activating Interrupt SPIE

}

void spi_polling(unsigned int data){

	  S0SPDR=data;	
	while( !(S0SPCR & (1<<8) ) );		// Wait upto SPIF flag gets to 1

}

void main()
{
	VPBDIV=0x02;									// 60Mhz/2

  PINSEL0=0x00001500;						// SSEL0 taken as GPIO
  led_on();
	
	interrupt_int();							//Interrupt Enable
	spi_int();
	
	
	while(1)
	{
					IO0SET=0x00000080;	   	// Slave Select Pin High
	        S0SPDR=i;	
	}
	
}