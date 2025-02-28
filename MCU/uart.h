// uart
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h> 

//#define	UART_BAUD 9600  
#define	UART_BAUD 57600

volatile unsigned char mas[16];
unsigned char index_mas = 0;
unsigned char old_bt = 0;
volatile unsigned char responce = 0; //None


/*Initialize the UART to 9600 Bd, tx/rx, 8N1.*/
void uart_init(void)
{
#if F_CPU < 2000000UL && defined(U2X)
  UCSR0A = _BV(U2X);             // improve baud rate error by using 2x clk 
  UBRR0L = (F_CPU / (8UL * UART_BAUD)) - 1;
#else
  UBRR0L = (F_CPU / (16UL * UART_BAUD)) - 1;
#endif
  UCSR0B = _BV(TXEN0) | _BV(RXEN0); // tx/rx enable 
} 

// send to uart

void	send_uart(unsigned char bt)
{
while (testbit(UCSR0A, UDRE0) == 0) {;}
		UDR0 = bt;
}

void print_byte(unsigned char sim)
	{
	send_uart(sim / 100 + '0');
	sim = sim % 100;
	send_uart(sim / 10 + '0');
	send_uart(sim % 10 + '0');
	}

unsigned int intdec;

unsigned char last_dec(void)
	{
	unsigned char res = intdec % 10;
	intdec = intdec / 10;
	return res;
	}

void print_int(unsigned int sim)
	{
	unsigned char i = 0;
	unsigned char sign[5];
	intdec = sim;
	while(intdec != 0)
		{
		sign[i] = last_dec();
		i++;
		}
	if( i == 0) send_uart('0');
	while(i != 0)
		{
		i--;
		send_uart(sign[i] + '0');
		} 
	}

void print_signed(unsigned int sim)
	{
	volatile unsigned char lbi;
	unsigned char mbi;
	
	mbi = sim >> 8;
	lbi = sim;
	if(testbit(mbi, 7))
		{
		send_uart('-');
		mbi &= 0b01111111;
		sim = mbi;
		sim = sim << 8 | lbi;
		sim = 32768 - sim;
		}
	print_int(sim);	
	}

void print_float(float sim)
	{

	}

void	println(char *str)
	{
	unsigned char i;
	i = 0;
	while (str[i]!=0)
		{
		send_uart(str[i]);
		i++;		
		}
	send_uart(13);
	send_uart(10);
	}

void	print(char *str)
	{
	unsigned char i;
	i = 0;
	while (str[i]!=0)
		{
		send_uart(str[i]);
		i++;		
		}
	}


void printmas(void)
{
for(unsigned char i = 0; i <= index_mas; i++)
	{
	send_uart(mas[i]);
	}
}


char compare(char *str)
{
unsigned char i = 0;
	while(str[i] != 0)
		{
		if(mas[i] != str[i]) return 0;
		i++;
		}
return 1;
}



void print2bin(unsigned int dlitelnost)
{
for(unsigned char i = 0; i < 16; i++)
	{
	if((i&0b00000111) == 0)
		{
		send_uart(' ');
		}
	if(dlitelnost%2)
		{
		send_uart('1');
		}
		else
		{
		send_uart('0');
		}
	dlitelnost = dlitelnost / 2;
	}
}


ISR(USART_RX_vect)
{
unsigned char bt;
while ( !(UCSR0A & (1<<RXC0)) );
bt = UDR0;
//print_byte(bt);
//send_uart(' ');
mas[index_mas] = bt;
// признак конца строки
//if((old_bt == 13)&&(bt == 10))
if(bt == 13)
	{
	responce = 3;
	if(compare("hello")) responce = 1;
	if(compare("bye")) responce = 2;
	index_mas = 0;
	}
	else
	{
	old_bt = bt;
	index_mas++;
	index_mas &= 0b00001111;
	}
}


