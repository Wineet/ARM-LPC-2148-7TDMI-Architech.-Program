/*
* In this Code EINT2 external interrupt is enabled
* level triggered and it is active Low Sensitive
* when Interrupt occure Led Turn on for a small delay
* writing delay in interrupt is not suggested it is only for demo purpose
*/



#include<LPC214x.h>

void delay(){

for(int i=0;i<1000;i++)	{
	 			for(int j=0;j<1000;j++)
				{
					;
				}
			}

}

void led_on(){
	
	IO0DIR=(IO0DIR)|(0x80000000);			//LED
	IO0CLR=0x80000000;
	
}
void led_off(){
	  			//LED OFF
	  IO0SET=0x80000000;
}





void Buzz_on(){
     IO1DIR=(IO1DIR)|(0x02000000);	
	   IO1CLR=0x02000000;
}



void Buzz_off(){
  IO1SET=0x02000000;

}

void Ext_interrupt_isr()__irq
	{

	EXTINT=(1<<2);		// Clearing Flag MUST Do
	led_on();
	delay();
	VICVectAddr=0x00;		// Dummy data to exit ISR

}
void ext_interrupt_setup()
{
			
	PINSEL0|=(1<<31);														//Interrupt Enabled
	EXTMODE=(0<<2);	   													//Level Sensitive
	EXTPOLAR=(0<<2);	 													// active low sensitive
  VICIntEnable=(1<<16);												// EXT int2 Int Enable 
  VICVectCntl4=0x20| 16;											//		Enabling Slot	
	VICVectAddr4=(unsigned long)Ext_interrupt_isr;		
	EXTINT |=(1<<2);														// clearing flag by Writing one to it


}
void main()
{
	led_on();
	delay();
	led_off();
	VPBDIV=0x02;
  ext_interrupt_setup();
	while(1)
	{
		led_off();
		
	}
	




}