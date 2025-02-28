// timers

void timer0_init(void)
{
/*
0 - timer is not active
1 - div 1
2 - div 8
3 - div 64
4 - div 256
5 - div 1024
6 - external source on T0. falling edge
7 - external source on T0. rising edge
*/
TCCR0B = 2;
TCNT0 = 255-225;
setb(TIMSK0, TOIE0);
}


unsigned char packet = 0;	// fast recive
//unsigned long int packet = 0; // full recive with adress and data
unsigned char count_bit = 33;
unsigned char input_flag = 0;
volatile unsigned char null_time = 0;
volatile unsigned char one_time = 0;
volatile unsigned char flag_stop = 0;
volatile unsigned int dlit = 0;

volatile unsigned char count_togo = 0;

#define ledon	setb(PORTB, 5)
#define ledoff	resb(PORTB, 5)


ISR(TIMER0_OVF_vect)
{ 
	unsigned char copyport;
	TCNT0 = 30;
	copyport = PINC;
/////////////////////  obrabotka ik porta
	input_flag *= 2;
	if(testbit(copyport, 0))
		{
		resb(input_flag, 0);
		}
		else
		{
		setb(input_flag, 0);
		}
	input_flag &= 0b00000011;
	if(input_flag == 0b00000010) 
		{
		null_time = 0;
		}
	if(input_flag == 0b00000001) 
		{
		one_time = 0;
//		colone++;
		}
	if(testbit(input_flag, 0))
		{
		if(one_time < 100) one_time++;
		}
		else
		{
		null_time++;
		}
	if(one_time == 2)
		{
		if(count_bit < 32) { count_bit++;}
		// start packet
		if((null_time >= 39)&&(null_time <= 41))
			{
			// begin packet
			count_bit = 0;
			}
		// recive null bit
		if((null_time >= 4)&&(null_time <= 6))
			{
			packet *= 2;
			}
		// recive one bit
		if((null_time >= 14)&&(null_time <= 16))
			{
			packet = packet * 2 + 1;
			}
		// repeat code
		if((null_time >= 19)&&(null_time <= 21))
			{
			long_tim = packet;
			flag = 1;
			flag_stop = 0;
			count_bit = 0;
			dlit = 0;
			}
		// transmite packet
		if(count_bit == 32)
			{
			if(flag == 0)
				{
				long_tim = packet;
				flag = 1;
				flag_stop = 0;
				//onecol = packet;
				count_bit = 0;
				dlit = 0;
				}
			}
		}
if(dlit < 800) dlit++;
if(dlit == 700) flag_stop = 1;
//////////////////////  End of work with IK port


/// Control speed
count_togo++;
if(count_togo > 127) count_togo = 0;
if(count_togo == 0) move_forward_int();
if(pr == 0) turn_right_stop_int();
if(pl == 0) turn_left_stop_int();

unsigned char perehod;
perehod = count_togo / 4;

if(pr < perehod) turn_right_stop_int();
if(pl < perehod) turn_left_stop_int();

}



void timer1_init(void)
{
/*
0 - timer is not active
1 - div 1
2 - div 8
3 - div 64
4 - div 256
5 - div 1024
6 - external source on T1. falling edge
7 - external source on T1. rising edge
*/
TCCR1B = 2;
TCNT1 = 34286;
//setb(TIMSK1, TOIE1);
}

void timer2_init(void)
{
/*
0 - timer is not active
1 - div 1
2 - div 8
3 - div 32
4 - div 64
5 - div 128
6 - div 256
7 - div 1024
*/
TCCR2B = 7;
TCNT2 = 11;
//setb(TIMSK1, TOIE1);
}

