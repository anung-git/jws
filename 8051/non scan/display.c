#include "display.h"


void shiftout_jam(unsigned char a)
{
	unsigned char b;
	strobe_jam = 0;
	for (b = 0; b < 8; b++)
	{
		if (a >= 0x80)
			input_jam = 1;
		else
			input_jam = 0;
		a = (a << 1) | (a >> 7);
		clock_jam = 1;
		clock_jam = 0;
	}
}
void shiftout_tanggal(unsigned char a)
{
	unsigned char b;
	strobe_tanggal = 0;
	for (b = 0; b < 8; b++)
	{
		if (a >= 0x80)
			input_tanggal = 1;
		else
			input_tanggal = 0;
		a = (a << 1) | (a >> 7);
		clock_tanggal = 1;
		clock_tanggal = 0;
	}
}
void shiftout_jadwal(unsigned char a)
{
	unsigned char b;
	strobe_jadwal = 0;
	for (b = 0; b < 8; b++)
	{
		if (a >= 0x80)
			input_jadwal = 1;
		else
			input_jadwal = 0;
		a = (a << 1) | (a >> 7);
		clock_jadwal = 1;
		clock_jadwal = 0;
	}
}

