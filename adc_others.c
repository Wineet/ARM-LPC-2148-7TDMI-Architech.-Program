#include<lpc214x.h>
#include<stdio.h>
void UART_init(void);
void UART_tx(char []);

int main(void)
{
	int x;
	char ch[50];
	VPBDIV = 0x02;    //to work on 30 MHz
	UART_init();
	
	PINSEL1 = 0x10000000;    //adc0.3 has pot and is enabled with adc functionality
	AD0CR = 0x00210708;
	//ADGSR = 0x00010000;
	
	while(1){
		while(!(AD0STAT | 0x00000008));   //checking for conversion completion at channel 3
		x = ((AD0DR3 & 0x0000FFC0)>>6);    // to get result from pin 0.6-0.15 and right shifted by 6
		sprintf(ch, "result=%d", x);
		UART_tx(ch);
		for(int i=0;i<1000;i++)
		{
			for(int j=0;j<10000;j++);
		}
	}
}

void UART_init(void)
{
	PINSEL0 = 0x00050000;								//configuring Pin P0.8 & P0.9 (0101)
	U1LCR = 0x00000083;								//(bit0:bit1 = 11 , for word length 8), (bit2= 1, 2Stop bits), (bit7 = 1 , Enable DLAB=1 (setup UART ))
	U1DLL = 0x000000C3;								// baudrate 9600 	SET FOR 30MHz
	U1DLM = 0x00000000;								//zero
	U1LCR = 0x00000003;								//reset DLAB=0
}

void UART_tx(char ch[50])
{
	int i=0;
	while(ch[i] != '\0')
	{
			while(!(U1LSR & 0x20));
			U1THR = ch[i++];
	}
}