// lib L3G4200D


#define L3G4200D_ADDRESS 210

// 0b11010010

#define L3G4200D_REG_WHO_AM_I      (0x0F)

#define L3G4200D_REG_CTRL_REG1     (0x20)
#define L3G4200D_REG_CTRL_REG2     (0x21)
#define L3G4200D_REG_CTRL_REG3     (0x22)
#define L3G4200D_REG_CTRL_REG4     (0x23)
#define L3G4200D_REG_CTRL_REG5     (0x24)
#define L3G4200D_REG_REFERENCE     (0x25)
#define L3G4200D_REG_OUT_TEMP      (0x26)
#define L3G4200D_REG_STATUS_REG    (0x27)

#define L3G4200D_REG_OUT_X_L       (0x28)
#define L3G4200D_REG_OUT_X_H       (0x29)
#define L3G4200D_REG_OUT_Y_L       (0x2A)
#define L3G4200D_REG_OUT_Y_H       (0x2B)
#define L3G4200D_REG_OUT_Z_L       (0x2C)
#define L3G4200D_REG_OUT_Z_H       (0x2D)

#define L3G4200D_REG_FIFO_CTRL_REG (0x2E)
#define L3G4200D_REG_FIFO_SRC_REG  (0x2F)

#define L3G4200D_REG_INT1_CFG      (0x30)
#define L3G4200D_REG_INT1_SRC      (0x31)
#define L3G4200D_REG_INT1_THS_XH   (0x32)
#define L3G4200D_REG_INT1_THS_XL   (0x33)
#define L3G4200D_REG_INT1_THS_YH   (0x34)
#define L3G4200D_REG_INT1_THS_YL   (0x35)
#define L3G4200D_REG_INT1_THS_ZH   (0x36)
#define L3G4200D_REG_INT1_THS_ZL   (0x37)
#define L3G4200D_REG_INT1_DURATION (0x38)

float XAxis;
float YAxis;
int ZAxis;

unsigned char zla;
unsigned char zha;


typedef enum
{
    L3G4200D_SCALE_2000DPS = 0b10,
    L3G4200D_SCALE_500DPS  = 0b01,
    L3G4200D_SCALE_250DPS  = 0b00
} l3g4200d_dps_t;

typedef enum
{
    L3G4200D_DATARATE_800HZ_110  = 0b1111,
    L3G4200D_DATARATE_800HZ_50   = 0b1110,
    L3G4200D_DATARATE_800HZ_35   = 0b1101,
    L3G4200D_DATARATE_800HZ_30   = 0b1100,
    L3G4200D_DATARATE_400HZ_110  = 0b1011,
    L3G4200D_DATARATE_400HZ_50   = 0b1010,
    L3G4200D_DATARATE_400HZ_25   = 0b1001,
    L3G4200D_DATARATE_400HZ_20   = 0b1000,
    L3G4200D_DATARATE_200HZ_70   = 0b0111,
    L3G4200D_DATARATE_200HZ_50   = 0b0110,
    L3G4200D_DATARATE_200HZ_25   = 0b0101,
    L3G4200D_DATARATE_200HZ_12_5 = 0b0100,
    L3G4200D_DATARATE_100HZ_25   = 0b0001,
    L3G4200D_DATARATE_100HZ_12_5 = 0b0000
} l3g4200d_odrbw_t;


unsigned char useCalibrate;
unsigned char chipID = 0;
float actualThreshold;
float dpsPerDigit;
float thresholdX;
float thresholdY;
float thresholdZ;

float dZAxis;
float tZAxis;



void writeRegister8(unsigned char reg, unsigned char value)
{	

	TWI_start();
    TWI_write(L3G4200D_ADDRESS);
 	TWI_write(reg);
	TWI_write(value);
    TWI_stop();
/*
I2C_Start();
I2C_Write(L3G4200D_ADDRESS);
_delay_ms(1);
I2C_Write(reg);
_delay_ms(1);
I2C_Write(value);
_delay_ms(1);
I2C_Stop();
*/
}

unsigned char readRegister8(uint8_t reg)
{
	unsigned char value;

	TWI_start();
	//I2C_Start();
	TWI_write(L3G4200D_ADDRESS);
	//I2C_Write(L3G4200D_ADDRESS);
	TWI_write(reg);
	//I2C_Write(reg);
    TWI_start();
	//I2C_Start();
	value = L3G4200D_ADDRESS;
	value |= 0b00000001;
	TWI_write(value);
	//I2C_Write(value);
    value = TWI_read_nack(); // Read data from slave without sending ACK
	//value = I2C_Read(1);
    TWI_stop();
	//I2C_Stop();
/*
	I2C_Start();
	I2C_Write(L3G4200D_ADDRESS);
//_delay_ms(1);
	I2C_Write(reg);
//_delay_ms(1);
    I2C_Start();
	value = L3G4200D_ADDRESS;
	value |= 0b00000001;
	I2C_Write(value);
//_delay_ms(1);
    value = I2C_Read(1);
    I2C_Stop();
*/

    return value;
}

unsigned char fastRegister8(uint8_t reg)
{
    unsigned char value;

    TWI_start();
	println(" start I2C");
	TWI_write(L3G4200D_ADDRESS);
	println(" send adress i2c ");
	TWI_write(reg);
	println(" send adress ram ");
    TWI_start();
	println(" send restart ");
	value = L3G4200D_ADDRESS;
	value |= 0b00000001;
	TWI_write(value);
	println(" send adress with code for read memory");
    value = TWI_read_nack(); // Read data from slave without sending ACK
	println(" read byte from i2c");
    TWI_stop();
	println(" stop i2c");
/*
	I2C_Start();
	println(" start I2C");
	I2C_Write(L3G4200D_ADDRESS);
	println(" send adress i2c ");
	I2C_Write(reg);
	println(" send adress ram ");
	I2C_Start();
	println(" send restart ");
	value = L3G4200D_ADDRESS;
	value |= 0b00000001;
	I2C_Write(value);
	println(" send adress with code for read memory");
	value = I2C_Read(1);
	println(" read byte from i2c");
	I2C_Stop();
	println(" stop i2c");
*/
 return value;
}

unsigned char init_l3g4(l3g4200d_dps_t scale, l3g4200d_odrbw_t odrbw)
{
println(" Reset calibrate values");
//    d.XAxis = 0;
//    d.YAxis = 0;
    dZAxis = 0;
    useCalibrate = 0;

println(" Reset threshold values");
//  t.XAxis = 0;
//  t.YAxis = 0;
    tZAxis = 0;
    actualThreshold = 0;

	println("Check L3G4200D Who Am I Register");

	//chipID = fastRegister8(L3G4200D_REG_WHO_AM_I);
	chipID = readRegister8(L3G4200D_REG_WHO_AM_I);

    if (chipID != 0xD3)
    {
	println(" It's not a gyroscope ");
	return 0;
    }

	println(" Yes. It's gyroscope ");
	print(" Setup gyroscope ");

    // Enable all axis and setup normal mode + Output Data Range & Bandwidth
    unsigned char reg1 = 0x00;
    reg1 |= 0x0F; // Enable all axis and setup normal mode
    reg1 |= (odrbw << 4); // Set output data rate & bandwidh
    writeRegister8(L3G4200D_REG_CTRL_REG1, reg1);

    // Disable high pass filter
    writeRegister8(L3G4200D_REG_CTRL_REG2, 0x00);

    // Generata data ready interrupt on INT2
    writeRegister8(L3G4200D_REG_CTRL_REG3, 0x08);

    // Set full scale selection in continous mode
    writeRegister8(L3G4200D_REG_CTRL_REG4, scale << 4);

    switch(scale)
    {
	case L3G4200D_SCALE_250DPS:
	    dpsPerDigit = .00875f;
	    break;
	case L3G4200D_SCALE_500DPS:
	    dpsPerDigit = .0175f;
	    break;
	case L3G4200D_SCALE_2000DPS:
	    dpsPerDigit = .07f;
	    break;
	default:
	    break;
    }

    // Boot in normal mode, disable FIFO, HPF disabled
    writeRegister8(L3G4200D_REG_CTRL_REG5, 0x00);
	
	println("......Ok");	

    return 1;

}

void calibrate_l3g4(unsigned char samples)  /// 60
{
}

void setThreshold(unsigned char multiple)  // 1
{
}

unsigned char getThreshold(void)
{
return 0;
}

void readRaw(void)
{
/*
	TWI_start();
	TWI_write(L3G4200D_ADDRESS);
	TWI_write(L3G4200D_REG_OUT_Z_L | (1 << 7)); 
 	TWI_start();
	TWI_write(L3G4200D_ADDRESS | 0b00000001);
	zla = TWI_read_ack();
	zha = TWI_read_nack();
	TWI_stop();


	I2C_Start();
	I2C_Write(L3G4200D_ADDRESS);
	I2C_Write(L3G4200D_REG_OUT_Z_L);// | (1 << 7)); 
 	I2C_Start();
	I2C_Write(L3G4200D_ADDRESS | 0b00000001);
	zla = I2C_Read(0);
	zha = I2C_Read(0);
	I2C_Stop(); 
*/
	zla = readRegister8(L3G4200D_REG_OUT_Z_L);
	zha = readRegister8(L3G4200D_REG_OUT_Z_L + 1);

    ZAxis = zha << 8 | zla;
}

void readNormalize(void)
{
}

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
//float yaw = 0;
signed int yaw = 0;

