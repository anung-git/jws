#include <at89x52.h>
#include <stdio.h>
#include "purworejo.h"
#include "i2c.h"
#include "util.h"

__code unsigned int bulan_adr[] = {0, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500};
#define space 40
#define buzzer_pin P2_2

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

unsigned char makedec(unsigned char a)
{
  a = ((a >> 4) * 10) + (a & 0x0f);
  return (a);
}
unsigned char makebcd(unsigned char a)
{
  a = ((a / 10) << 4) + (a % 10);
  return (a);
}

//tambahkan jam (jam,menit,nilai tambah);
void addTime(unsigned char *hour, unsigned char *min, unsigned char value)
{
  unsigned int result = (makedec(*hour) * 60) + makedec(*min);
  result = result + value;
  *hour = makebcd(result / 60);
  *min = makebcd(result % 60);
}

void setup()
{
  unsigned int bulan;
  for (bulan = 6000; bulan < 8000; bulan++)
  {
    write_byte(bulan, 0x12);
  }

  for (bulan = 0; bulan < 12; bulan++)
  {
    unsigned char tanggal;

    for (tanggal = 0; tanggal < 31; tanggal++)
    {
      unsigned char jam, menit;
      unsigned int epromaddr = bulan_adr[bulan] + tanggal + 1;

      jam = tabel[(bulan * 372) + tanggal];        //jam imsya
      menit = tabel[(bulan * 372) + 31 + tanggal]; //menit imsya
      addTime(&jam, &menit, 8);
      write_byte(epromaddr, jam);
      epromaddr = epromaddr + space;
      write_byte(epromaddr, menit);

      jam = tabel[(bulan * 372) + 62 + tanggal];   //jam subuh
      menit = tabel[(bulan * 372) + 93 + tanggal]; //menit subuh
      addTime(&jam, &menit, 8);
      epromaddr = epromaddr + space;
      write_byte(epromaddr, jam);
      epromaddr = epromaddr + space;
      write_byte(epromaddr, menit);

      jam = tabel[(bulan * 372) + 124 + tanggal];   //jam dzuhur
      menit = tabel[(bulan * 372) + 155 + tanggal]; //menit dzuhur
      epromaddr = epromaddr + space;
      write_byte(epromaddr, jam);
      epromaddr = epromaddr + space;
      write_byte(epromaddr, menit);

      jam = tabel[(bulan * 372) + 186 + tanggal];   //jam ashar
      menit = tabel[(bulan * 372) + 217 + tanggal]; //menit ashar
      epromaddr = epromaddr + space;
      write_byte(epromaddr, jam);
      epromaddr = epromaddr + space;
      write_byte(epromaddr, menit);

      jam = tabel[(bulan * 372) + 248 + tanggal];   //jam maghrib
      menit = tabel[(bulan * 372) + 279 + tanggal]; //menit maghrib
      epromaddr = epromaddr + space;
      write_byte(epromaddr, jam);
      epromaddr = epromaddr + space;
      write_byte(epromaddr, menit);

      jam = tabel[(bulan * 372) + 310 + tanggal];   //jam isya
      menit = tabel[(bulan * 372) + 341 + tanggal]; //menit isya
      epromaddr = epromaddr + space;
      write_byte(epromaddr, jam);
      epromaddr = epromaddr + space;
      write_byte(epromaddr, menit);
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