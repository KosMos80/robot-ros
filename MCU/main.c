#define F_CPU 16000000

#include	<avr/io.h>
#include	<avr/delay.h>
#include 	<avr/interrupt.h>
/////////////////////////////////////////////////
#define setb(port, bit)	port|=(1<<bit)
#define	resb(port, bit)	port&=~(1<<bit)
#define	testbit(port, bit)	(port & (1<<bit))
/////////////////////////////////////////////////
#include "shassi.h"

//unsigned long int long_tim = 0;
unsigned char long_tim = 0;

unsigned long int dlitelnost;

unsigned long int buf_tim;
unsigned char onecol;
volatile unsigned char flag;
unsigned char stop_time = 0;

signed long int azimut = 0;
signed long int temp_azim = 0;
signed long int azim;
signed int azimut360 = 0;
signed int delta = 0;


unsigned char auto_comm = 0;
/*
0 - nothing
1 - turn left
2 - turn right
*/


volatile unsigned int max_tim = 0;
volatile unsigned int max_temp = 0;



#include "uart.h"
#include "timers.h"
//#include "i2c_soft.h"
#include "i2c.h"
#include "L3G4200D.h"
#include "servo.h"
#include "hy-srf05.h"
#include "pid.h"

int main(void)
{
config_shassi();
init_hysrf();
all_stop();

uart_init();
println(" UART57600 start ok ...");

print(" Init Timer0 ");
timer0_init();

println("..... Ok");
print(" Init Timer2 ");

//timer1_init();
timer2_init(); 
//init_pwm();
println("..... Ok");

print(" Init I2C");
TWI_init_master();
//I2C_Init();

println("..... Ok");
println("Start init gyroscope ...");
while(!init_l3g4(L3G4200D_SCALE_250DPS, L3G4200D_DATARATE_400HZ_50))
	{
	_delay_ms(500);
	print_byte(chipID);
	println("... try init");
	}

println("Init Ok!");

// enable interrupte
//setb(UCSR0B, RXCIE0);

print(" Init PID ...");
init_pid();
println("Init Ok!");


/*
//============================================
while(1)
	{
	TCCR1B = 4;
	print_int(get_distance());
	println(" ");
	_delay_ms(100);
	}
//============================================
*/


sei();
// INIT other modules

setServoAngleA(90);
println("Set servo to neutral");

flag = 0;
//unsigned char gyrcount = 0;

volatile unsigned int ttt = 0;


int dx = 1;
int dy = 10;

int vecx = 10;
int vecy = 10;
/*
//============================================
while(1)
	{
	azimut = 0;
	for(int i = 0; i < 1000; i++)
		{
		/// pause, oformit kak proceduru po tipu  sinhro(dlitelnost)
		while (testbit(TIFR2, TOV2) == 0) {;}
		setb(TIFR2, TOV2);
		TCNT2 = 11;		
		////////////////
		readRaw();
		azimut = azimut + ZAxis - 12;
		}
	print_signed(azimut/1000);
	println(" ");
	}
//============================================
*/

while(1)
	{
	/// pause, oformit kak proceduru po tipu  sinhro(dlitelnost)
	while (testbit(TIFR2, TOV2) == 0) {;}
	setb(TIFR2, TOV2);
	TCNT2 = 11;		
	////////////////
	ttt++;
	// code for control guroscope
	readRaw();
	azimut = azimut + ZAxis - 12;
	// 655360
	if(azimut > (2 * 655360))
		{
		azimut = - 4 * 655360 + azimut; 
		}
	if(azimut < - (2 * 655360))
		{
		azimut = 4 * 655360 - azimut; 
		}


	azim = azimut / 64;



	if(ttt == 8)
		{
		//print_signed(ZAxis);
		//print_signed(azimut - temp_azim);
		//temp_azim = azimut;
		//print("  ");
		azimut360 = (azimut * 9 / 64) / 1024;
		print_signed(azimut360);
/*
		send_uart(' ');
		//print_signed(pow_vector);
		print_signed(delta);
		send_uart(' ');
		print_byte(pl);
		send_uart(' ');
		print_byte(pr);
*/
		println(" ");
		ttt = 0;
		}




	switch(auto_comm)
		{
		case 1:
			{
			if(azimut < 655360)
				{
				turn_left();
				}
				else
				{
				// azimut > 655360
				if(azimut < (655360 + 720))
					{
					all_stop();
					auto_comm = 0;
					}
					else
					{
					turn_right();
					auto_comm = 4;
					}
				}
			break;
			}
		case 2:
			{
			if(azimut > -655360)
				{
				turn_right();
				}
				else
				{
				// azimut < -655360
				if(azimut > -(655360 + 720))
					{
					all_stop();
					auto_comm = 0;
					}
					else
					{
					turn_left();
					auto_comm = 5;
					}
				}
			break;
			}
		case 3:
			{
			new_error(azim);
			delta = calculate_pid();
			set_vector(delta);
			transform_vector();
			break;
			}
		case 4:
			{
			if(azimut > 655360)
				{
				turn_right();
				}
				else
				{
				// azimut < 655360
				if(azimut > (655360 - 720))
					{
					all_stop();
					auto_comm = 0;
					}
					else
					{
					turn_left();
					auto_comm = 1;
					}
				}
			break;
			}
		case 5:
			{
			if(azimut < -655360)
				{
				turn_left();
				}
				else
				{
				// azimut > -655360
				if(azimut < -(655360 - 7200))
					{
					all_stop();
					auto_comm = 0;
					}
					else
					{
					turn_right();
					auto_comm = 2;
					}
				}
			break;
			}
		}




// code for control IR port
		if(flag)
			{
			buf_tim = long_tim;
			flag = 0;
			switch(buf_tim)
				{
				case 231: move_forward(); break;
				case 181: 
					{
					// move to forward with hiro stable
					azimut = 0;
					auto_comm = 3;
					e0 = 0;
					e1 = 0;
					//move_back(); 
					break;
					}
				case 165: 
					{
					turn_left();
					//azimut = 0;
					//auto_comm = 1;
					break;
					}
				case 239: 
					{
					turn_right(); 
					//azimut = 0;
					//auto_comm = 2;
					break;
					}
				case 199: 
					{
					auto_comm = 0;
					all_stop(); 
					break;
					}
				}
			stop_time = 0;
			}
		if(flag_stop)
			{
			if(stop_time < 100) stop_time++;
			if(stop_time == 5)
				{
				//println("All mech stop");
				//flag_stop = 0;
				all_stop();
				//stop_time = 0;
				}
			}
/*
	max_temp = TCNT1 - 34286;
	if(max_temp > max_tim) 
		{
		max_tim = max_temp; 
		}
	print_int(max_tim);
	println(" ");
*/
	}
// End Main While
}
