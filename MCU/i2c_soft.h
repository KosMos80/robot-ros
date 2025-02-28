
// i2c soft

#define	i2c_clk_ddr	DDRC
#define	i2c_clk_port	PORTC
#define i2c_clk	PC5

#define	i2c_dat_ddr	DDRC
#define	i2c_dat_port	PORTC
#define	i2c_dat_pin	PINC
#define i2c_dat	PC4

void	I2C_Init(void)
	{
	setb(i2c_clk_port, i2c_clk);
	setb(i2c_clk_ddr, i2c_clk);
	resb(i2c_dat_ddr, i2c_dat);
	resb(i2c_dat_port, i2c_dat);
	}

void	I2C_Start(void)
	{
	setb(i2c_clk_port, i2c_clk);	// scl = 1

	resb(i2c_dat_ddr, i2c_dat);		// sdt = 1
	resb(i2c_dat_port, i2c_dat);
	_delay_us(2);
	setb(i2c_dat_ddr, i2c_dat);
	_delay_us(2);
	resb(i2c_clk_port, i2c_clk);
	_delay_us(2);
	resb(i2c_dat_ddr, i2c_dat);

//	println(" ");


	}

void	I2C_Stop(void)
	{
	resb(i2c_clk_port, i2c_clk);	// scl = 0

	setb(i2c_dat_ddr, i2c_dat);
	resb(i2c_dat_port, i2c_dat);
	_delay_us(2);
	setb(i2c_clk_port, i2c_clk);
	_delay_us(2);
	resb(i2c_dat_ddr, i2c_dat);
	resb(i2c_dat_port, i2c_dat);
	_delay_us(2);
	}

inline void	I2C_Clock(void)
	{
	_delay_us(2);
	setb(i2c_clk_port, i2c_clk);
	_delay_us(2);
	resb(i2c_clk_port, i2c_clk);
	}

inline void	I2C_bitoutHI(void)
	{
	resb(i2c_clk_port, i2c_clk);
	resb(i2c_dat_ddr, i2c_dat);
	I2C_Clock();
//	print("1");
	}

inline void	I2C_bitoutLO(void)
	{
	resb(i2c_clk_port, i2c_clk);
	resb(i2c_dat_port, i2c_dat);
	setb(i2c_dat_ddr, i2c_dat);
	I2C_Clock();
//	print("0");
	}

unsigned char I2C_bitin(void)
	{
	unsigned char temp;
	temp=0;
	resb(i2c_clk_port, i2c_clk);
	resb(i2c_dat_ddr, i2c_dat);
	setb(i2c_clk_port, i2c_clk);
	if (testbit(i2c_dat_pin, i2c_dat)) 
		{
		temp=1;
//		print("1");
		}
		else
		{
//		print("0");
		}
	resb(i2c_clk_port, i2c_clk);
	return temp;
	}

unsigned char	I2C_Read(unsigned char i2c_ack)	// i2c_rx
	{
	unsigned char i,dsrx=0;
	for(i=1;i<=8;i++)
		{
		dsrx<<=1;
		if (I2C_bitin()==1) dsrx|=0b00000001;
		}
	if (i2c_ack==0) I2C_bitoutLO(); else I2C_bitoutHI();
	return dsrx;
	}

unsigned char	I2C_Write(unsigned char i2c_tx)	// i2c_ack
	{
	char i;
	for(i=1;i<=8;i++)                                            
  		{
    	if ((i2c_tx&128)==128)  
			{
			I2C_bitoutHI();
			}
			 else 
			{
			I2C_bitoutLO();
			}
		i2c_tx<<=1;
  		} 
	i=I2C_bitin();
//	print(" ");
	return i;
	}


