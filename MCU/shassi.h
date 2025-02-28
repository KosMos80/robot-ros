// shassi file

/*

PB0 -
PB1	- PWM1	servo1	timer1 OC1A
PB2	- PWM2	servo2	timer1 OC1B
PB3 - 
PB4 - 
PB5 - LED on board, as diagnostic led

PC0 - IR port
PC1 - trig_pin	| HY-SRF05
PC2 - echo_pin	|
PC3 -
PC4 - SDA	i2c bus for gyroscope	| L3G4200D
PC5 - SCL							|

PD0 - uart 
PD1 - uart
PD2 - 
PD3 -
PD4 - left forward	| Motor Driver
PD5 - left back		|
PD6 - right forward	|
PD7 - right back	|

*/

unsigned char speed_wheels = 0;

signed int pow_vector = 0;
// menyaetsa ot 0 - 127
// I II kvadranti 1 - 63
// full nazad 64
// III IV kvadranti 65 - 127

void vector_right(void)
{
pow_vector++;
if(pow_vector > 1024) pow_vector = 1024;
}

void vector_left(void)
{
pow_vector--;
if(pow_vector < -1024) pow_vector = -1024;
}

void vector_add(signed long int delta)
	{
	signed long int vec;
	vec = pow_vector;
	vec = vec + delta;
	if(vec < -1024)
		{
		pow_vector = -1024;
		}
		else
			{
			if(vec > 1024)
				{
				pow_vector = 1024;
				}
				else
				{
				pow_vector = vec;
				}
			}
	}

void set_vector(signed long int delta)
	{
	if(delta < -1024)
		{
		pow_vector = -1024;
		}
		else
			{
			if(delta > 1024)
				{
				pow_vector = 1024;
				}
				else
				{
				pow_vector = delta;
				}
			}
	}

unsigned char pr, pl, zr, zl;

void transform_vector(void)
{
signed int vect_temp;
vect_temp = 32 + (pow_vector / 32);

	if(vect_temp < 32)
		{
		pr = 31;
		pl = vect_temp;
		zr = 0;
		zl = 0;
		}
	if(vect_temp > 32)
		{
		pl = 31;
		pr = 64 - vect_temp;
		zr = 0;
		zl = 0;
		}
	if(vect_temp == 32)
		{
		pl = 31;
		pr = 31;
		}
}

/*
какаято хрень
проверить что идет на порт левого колеса, постоянно крутиться
проверить через терминал
отключив инициализацию гироскопа

*/


void	config_shassi(void)
{
// config IR port
setb(DDRB, 5);
resb(PORTB, 5);
resb(DDRC, 0);
setb(PORTC, 0);
// config 
PORTD &= 0b00001111;
DDRD |=  0b11110000;
pow_vector = 0;
pr = 0;
pl = 0;
zr = 0;
zl = 0;
}

void move_forward_int(void)
{
PORTD &= 0b00001111;
PORTD |= 0b01010000;
}

void move_back_int(void)
{
PORTD &= 0b00001111;
PORTD |= 0b10100000;
}

void turn_left_int(void)
{
PORTD &= 0b00001111;
PORTD |= 0b01100000;
}

void turn_right_int(void)
{
PORTD &= 0b00001111;
PORTD |= 0b10010000;
}

void turn_left_stop_int(void)
{
PORTD &= 0b10111111;
//PORTD &= 0b00001111;
//PORTD |= 0b01000000;
}

void turn_right_stop_int(void)
{
PORTD &= 0b11101111;
//PORTD &= 0b00001111;
//PORTD |= 0b00010000;
}


void all_stop_int(void)
{
PORTD &= 0b00001111;
}

unsigned char togo = 0;

void move_forward(void)
{
speed_wheels = 5;
togo = 1;
pr = 31;
pl = 31;
}

void move_back(void)
{
speed_wheels = 5;
togo = 2;
}

void turn_left(void)
{
speed_wheels = 5;
togo = 3;
pr = 31;
pl = 0;
}

void turn_right(void)
{
speed_wheels = 5;
togo = 4;
pl = 31;
pr = 0;
}

void turn_left_stop(void)
{
speed_wheels = 5;
togo = 5;
}

void turn_right_stop(void)
{
speed_wheels = 5;
togo = 6;
}

void all_stop(void)
{
speed_wheels = 0;
togo = 0;
pr = 0;
pl = 0;
}


