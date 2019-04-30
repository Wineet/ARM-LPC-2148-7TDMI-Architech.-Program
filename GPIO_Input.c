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

void main()
{
	VPBDIV=0x02;

	while(1)
	{
			PINSEL0=0x00000000;
			IO0DIR=0x00000000;
		if( IO0PIN & (1<<15) )
		{
	  led_off(); 
		
		}
		else
		{
		 led_on();
		}
			
	}




}