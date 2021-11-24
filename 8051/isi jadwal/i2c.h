/*
 * Filename : i2c.h
 * Hardware : Controller  -> P89V51RD2
 *            XTAL        -> 18.432 MHz
 *            Mode        -> 6 Clock/MC
 * I/O      : SDA         -> P2.7
 *            SCL         -> P2.6
 * Compiler : SDCC
 * Author   : sci-3d@hotmail.com
 * Date		: 23/08/06
 */

#ifndef I2C_H_   /* Include guard */
#define I2C_H_
#define SDA P0_0			/* Set P2.7 = SDA */
#define SCL P0_1			/* Set P2.6 = SCL */
#include "i2c.c"
#include <at89x52.h>  
 

#define I2C_DELAY 0x0F			/* For delay i2c bus */
void I2C_delay(void);
void I2C_clock(void);
void I2C_start(void);
void I2C_stop(void);
void I2C_write(unsigned char dat);
unsigned char I2C_read(void);
void I2C_ack();
void I2C_nack();

#endif // FOO_H_