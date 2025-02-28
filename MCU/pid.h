// PID regulyator

signed long int e0, e1, e2;
const signed int kp = 10;
const signed int ki = 3;
const signed int kd = 10;

void init_pid(void)
	{
	e0 = 0;
	e1 = 0;
	e2 = 0;
	}

void new_error(signed long int err)
	{
	e2 = (err - e0) * kd;
	e0 = err;
	e1 = e1 + ki * e0;
	}

signed long int calculate_pid(void)
	{
	signed int ei;
	signed int ed;
	ed = e2 / 512;
	ei = e1 / 512;
	signed long int du;
	du = kp * e0 ;
	du = du / 32 + ei + ed;
	return du;
	}
