/*
*LCD Pins 
*D4,D5,D6,D7, P0.10, P0.11, P0.12, P0.13
* RS_LCD P1.24
* RW_LCD P1.23 
* EN_LCD P1.22
* BL_LCD P1.21  LCD_BACK LIGHT
*
*/

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





void BL_LCD_OFF(){
	
	  IO1DIR|=(1<<21);	
	   IO1CLR|=(1<<21);
}


void BL_LCD_ON(){
	 
	  IO1DIR|=(1<<21);	
	   IO1SET|=(1<<21);

}


void en_pulse(){
  IO1SET|=(1<<22);
	delay();
	IO1CLR|=(1<<22);
}


void lcd_cmd(unsigned char cmd){
	//HIGHER NIBBLE PUSH
				IO0SET|=((cmd & 0xF0) << 6);
				IO0CLR|=( ( ( (~cmd) & 0xF0) )<< 6);
				IO1CLR|=(1<<24);								//RS=0 CMD MODE	
				en_pulse();
	//LSB PUSH
				IO0SET|=( (cmd & 0x0F) << 10);
				IO0CLR|=((((~cmd) & 0x0F) )<< 10);
				IO1CLR|=(1<<24);								//RS=0 CMD MODE	
				en_pulse();
}


void lcd_dat(unsigned char dat){
//HIGHER NIBBLE PUSH
				IO0SET|=((dat & 0xF0) << 6);
				IO0CLR|=( ( ( (~dat) & 0xF0) )<< 6);
				IO1SET|=(1<<24);								//RS=0 CMD MODE	
				en_pulse();
	delay();
	//LSB nibble PUSH
				IO0SET|=( (dat & 0x0F) << 10);
				IO0CLR|=( ( ( (~dat) & 0x0F) )<< 10);
				IO1SET|=(1<<24);								//RS=0 CMD MODE	
				en_pulse();
	delay();
}





void lcd_int(){

		IO1DIR|=(1<<21)|(1<<22)|(1<<23)|(1<<24);	// Data Pins
  IO0DIR|=(1<<10)|(1<<11)|(1<<12)|(1<<13);	// RS RW EN BACKlight set as output
	IO1CLR|=(1<<23);													// RW=0; Write Mode
  
	  lcd_cmd(0x02);
		lcd_cmd(0x28);
		lcd_cmd(0x0E);
		lcd_cmd(0x0F);
		lcd_cmd(0x01);
	  lcd_cmd(0xC3);
	
}









void lcd_str(unsigned char *p){
while(*p)
{
lcd_dat(*p);
	p++;
}
}



void main(){

  VPBDIV=0x02;
  led_on();
  BL_LCD_ON();	
	lcd_int();
		lcd_cmd(0x80);
	lcd_str("LPC2148");
	lcd_cmd(0xC3);
	lcd_str("VINIT");
		while(1);
	


}