#include<LPC21xx.h>

int i=0;

void led_on()
{
	  IO0DIR=(IO0DIR)|(0x80000000);			//LED
	  IO0CLR=0x80000000;
}
void led_off()
{
	  			//LED OFF
	  IO0SET=0x80000000;
}


// timer working fine LED blinking  with 1 sec delay >>POLLING Method

void timer_int(unsigned long int val)		//T1TC value
{
	
		T1PR=0;
		T1PC=0;
		T1TC= val;

}



void timer_start()
{
  T1TCR=0x01;			   // Timer ON
}



void timer_stop()
{
  T1TCR=0x00;			   // Timer ON
}


void timer_poll()
{
	while((T1TC<0xFFFFFFF0));

}



void timer_delay_ms(unsigned int delay_ms){				// delay is by considering 30 Mhz PCLK
	
		T1PR=0;
		T1PC=0;
		T1TC= 4294967296 -(unsigned long int)((long double)delay_ms/3.33)*100000;		// for 1 SECOND Delay 4294... is max value of 32 bit timer
		//	T1MR1=0XFFFFFFFF;		// not used for now
	  T1TCR=0x01;			   // Timer ON
		while((T1TC<0xFFFFFFF0));		//It will COnsume Some machine Cycles so it may miss max value, so used lower value
																// precision we can balance by changing T1MR1 reg.
		T1TCR=0X00;									// TIMER STOP
}




//Timer Interrupt based Loops

void timer_interrupt_ISR()__irq
{
		T1TCR=0x00;		// Timer Stop	
		T1IR=(1<<1);		// Clearing Interrupt Flag
		if(i%2==0)
		{
			led_on();
		}
		else{
				led_off();
		}
		
		i++;
			if(i==65535)
			{ i=1;
			}
		T1PR=0;
	  T1PC=0;
	  T1TC= 4294967296 -(unsigned long int)((long double)1000/3.33)*100000;		
	  T1TCR=0x01;	
		
		VICVectAddr=0x00;		//Dummy data to exit ISR
}





void timer_interrupt_int(){
  
		T1IR=(1<<1);	// Reset Timer MR1 match Interrupt
									// Interrupt Register
		VICIntEnable|=(1<<5);	// Timer1 Interrupt Enable
		T1MCR=(1<<3);		// MAtch MR1I interrupt Enabled
		VICVectCntl7= 0x20 | 5;		// enabling timer source and slot
	  VICVectAddr7=(unsigned int) timer_interrupt_ISR;
	
}









void main()
{
	VPBDIV=0x02;	//CCLK/2  30Mhz
  led_off();
	timer_interrupt_int();
	T1PR=0;
	T1PC=0;
	T1TC= 4294967296 -(unsigned long int)((long double)1000/3.33)*100000;		
	T1TCR=0x01;			   // Timer ON
	
	while(1)
	{
		
		/*
		led_on();
		timer_delay_ms(500);
		led_off();
		timer_delay_ms(500);
		*/
	
	}


}


