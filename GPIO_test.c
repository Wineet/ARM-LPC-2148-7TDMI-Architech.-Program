#include<LPC214x.h>
void delay(){

for(int i=0;i<500;i++)	{
	 			for(int j=0;j<500;j++)
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
  IO0DIR=(IO0DIR)|(0x80000000);	
	IO0CLR=0x80000000;
	
	while(1)
	{
	  IO0CLR=0x80000000;
	   //IO1CLR=0x02000000;
	}



}