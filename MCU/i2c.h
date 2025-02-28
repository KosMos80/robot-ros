// i2c

/*
TWI_init_master() - init i2c master
TWI_start() - start bit
TWI_stop() - stop bit
TWI_write(byte) - write byte to i2c
uint8_t TWI_read_ack() - read byte from i2c with ACK
uint8_t TWI_read_nack() - read byte from i2c without ACK


*/

#include <avr/io.h>
#include <util/twi.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

void TWI_init_master(void)
{
    // Set bit rate
    TWBR = ((F_CPU / 100000UL) - 16) / 2;

    // Enable TWI, Acknowledge bit
    TWCR = (1 << TWEN) | (1 << TWEA);
}

void TWI_start(void)
{
    // Send start condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // Wait for TWINT flag set
    while (!(TWCR & (1 << TWINT)));
}

void TWI_stop(void)
{
    // Send stop condition
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8_t data)
{
    // Load data into TWDR register
    TWDR = data;

    // Clear TWINT bit in TWCR to start transmission of data
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Wait for TWINT flag set
    while (!(TWCR & (1 << TWINT)));
}

uint8_t TWI_read_ack(void)
{
    // Enable TWI, Generation of ACK
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    // Wait for TWINT flag set
    while (!(TWCR & (1 << TWINT)));

    // Return received data
    return TWDR;
}

uint8_t TWI_read_nack(void)
{
    // Enable TWI, Generation of NACK
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Wait for TWINT flag set
    while (!(TWCR & (1 << TWINT)));

    // Return received data
    return TWDR;
}

unsigned char read_i2c(unsigned char slave, unsigned char addr)
{
unsigned char data;
TWI_start();
TWI_write(slave); // Slave address (change according to your slave device address)
TWI_write(addr); // Register address to read from
TWI_start();
slave |= 0b00000001;
TWI_write(slave); // Slave address with read bit
data = TWI_read_nack(); // Read data from slave without sending ACK
TWI_stop();
return data;
}

void write_i2c(unsigned char slave, unsigned char addr, unsigned char data)
{

}

/*
// Example of code

int main(void)
{
    TWI_init_master();

    while (1)
    {
        TWI_start();
        TWI_write(0b11010000); // Slave address (change according to your slave device address)

        // Example: Read data from slave
        TWI_write(0x00); // Register address to read from
        TWI_start();
        TWI_write(0b11010001); // Slave address with read bit

        uint8_t data = TWI_read_nack(); // Read data from slave without sending ACK
        TWI_stop();

        // Do something with the received data
    }

    return 0;
} 

*/
