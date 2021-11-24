#include <at89x52.h>
#include <stdio.h>
#include "purworejo.h"
#include "i2c.h"
#include "util.h"

#define Jan 0
#define Feb 500
#define Mar 1000
#define Apr 1500
#define Mei 2000
#define Jun 2500
#define Jul 3000
#define Agu 3500
#define Sep 4000
#define Okt 4500
#define Nov 5000
#define Des 5500

#define space 40
#define buzzer_pin P2_5

void write_byte(unsigned int eeaddress, char data)
{
  unsigned char a, b;
  a = eeaddress >> 8;
  b = eeaddress & 0x00ff;
  I2C_start();
  I2C_write(0xa0);
  I2C_write(a);
  I2C_write(b);
  I2C_write(data);
  I2C_stop();
  delay(10);
}

void setup()
{
  unsigned int i;
  unsigned int epromaddr;
  int bulan;
  // for (i = 0; i < 8191; i++)
  // {
  //   write_byte(i, 0); //hapus memori
  // }

  for (bulan = 0; bulan < 12; bulan++)
  {
    int addr,index;
    index = 0;
    switch (bulan)
    {
    case 0:
      addr = Jan;
      break;
    case 1:
      addr = Feb;
      break;
    case 2:
      addr = Mar;
      break;
    case 3:
      addr = Apr;
      break;
    case 4:
      addr = Mei;
      break;
    case 5:
      addr = Jun;
      break;
    case 6:
      addr = Jul;
      break;
    case 7:
      addr = Agu;
      break;
    case 8:
      addr = Sep;
      break;
    case 9:
      addr = Okt;
      break;
    case 10:
      addr = Nov;
      break;
    case 11:
      addr = Des;
      break;
    }
    for (i = 0; i < 12; i++)
    {
      int count;
      epromaddr = addr;
      for (count = 1; count < 32; count++)
      {
        unsigned char data; 
        switch (bulan)
        {
        case 0:
          data = januari[index]; //Jan;
          break;
        case 1:
          data = Februari[index]; //Feb;
          break;
        case 2:
          data = Maret[index]; //Mar;
          break;
        case 3:
          data = April[index]; //Apr;
          break;
        case 4:
          data = Mey[index]; //Mei;
          break;
        case 5:
          data = Juni[index]; //Jun;
          break;
        case 6:
          data = Juli[index]; //Jul;
          break;
        case 7:
          data = Agustus[index]; //Agu;
          break;
        case 8:
          data = September[index]; //Sep;
          break;
        case 9:
          data = Oktober[index]; //Okt;
          break;
        case 10:
          data = November[index]; //Nov;
          break;
        case 11:
          data = Desember[index]; //Des;
          break;
        }
        index++;
        write_byte(epromaddr, data); // Copy data to eeprom
        epromaddr++;
      }
      addr = addr + space;
    }
  }
}

void loop()
{
  buzzer_pin = 1; //
  delay(300);
  buzzer_pin = 0; //
  delay(300);
}

void main(void)
{
  setup();
  for (;;)
  {
    loop();
  }
}