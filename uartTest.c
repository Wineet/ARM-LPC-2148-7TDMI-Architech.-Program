#include <LPC21xx.h>

int ch;

void Led_on(){
	
  IO0DIR=(IO0DIR)|(0x80000000);	
	IO0CLR=0x80000000;

}


void Led_off(){
	
  	
	IO0SET=0x80000000;

}



void uart_int(){
	
PINSEL0=(PINSEL0)|0x00050000;
U1LCR=0x83;		//Line Control reg.
	// Baud Rate
	U1DLL=185;
	U1DLM=0;
	U1FDR=0xF1;	// fraction baud Adjust
	U1LCR=0x03;	// Disable DLAB
	
}


void uart_transmit_poll(unsigned int data ){
	 U1THR=data;	
   	while(!(U1LSR & 0x20));
	 	
}


int uart_recieve_poll(){
	  int data;
   	while(!(U1LSR & (1<<0)));
	  data=U1RBR;
		return data;
}


void delay(){
	int k,j;
	
   for(k=0;k<1000;k++)
	 	  {
	 			for(j=0;j<1000;j++)
				{
					;
				}
			}	
}



void uart_interrupt() __irq
	{

		if( !(U1IIR & (1<<0)))		// PENDING Interrupt
		{
						if(U1IIR & (1<<2))			// Recieve interrupt
						{
							ch=U1RBR;

						}
						else //if(!(U1LSR & 0x20))		// Transmit Interrupt
						{
									Led_off();
									delay();
									Led_on();				// Transmit Interrupt LOOp
									delay();
									
									
						}
			
	}
		
			VICVectAddr=0x00;	//Dummy data to exit

}



void uart_int_setUp(){

  VICIntEnable=(1<<7);  											  //UART1 interrupt Enable	
	VICVectCntl5=0x20 | 7 ;										// activating Slot for Uart1  add 5
	VICVectAddr5=(unsigned int) uart_interrupt;	// Assigning Address

}




void main()
{
	
  VPBDIV=0x02;		  // 30 Mhz
	Led_on();
	uart_int_setUp();	// interrupt Setup
	uart_int();
  U1IER=(1<<0)|(1<<1);		  // RECIEVE & TRANSMIT ENABLE INTERRUPT
	
	while(1)
	{
		if(ch!=0)
		{
			U1THR=ch;
			ch=0;
		}	
			//	uart_transmit_poll(uart_recieve_poll());		// TO transmit and  echo data
		
	}


}