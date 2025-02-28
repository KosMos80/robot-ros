// lib hy-srf05

#define trig_pin	PC1
#define echo_pin	PC2

#define trig_port	PORTC
#define echo_port	PORTC

#define trig_ddr	DDRC
#define echo_ddr	DDRC

#define echo_in		PINC


void	init_hysrf(void)
{
setb(trig_ddr, trig_pin);
resb(echo_ddr, echo_pin);
}


unsigned int get_distance(void)
{
	unsigned int duration = 0;
	resb(trig_port, trig_pin);
	_delay_us(2);
	setb(trig_port, trig_pin);
	_delay_us(10);
	resb(trig_port, trig_pin);
	while(!(echo_in & (1 << echo_pin)));  // ????, ???? ECHO_PIN ?????? HIGH
	TCNT1 = 0;
	while(echo_in & (1 << echo_pin)) 
		{
	    //duration++;
	    _delay_us(1);
		}
	duration = TCNT1;



	//unsigned int distance = (duration / 58);  // ?????????? ? ???????????
	return duration;
}
