#include <at89x52.h>
#include <stdio.h>
#include "util.h"
#include "i2c.h"
#include "hari.h"
#include "mymacro.h"
void PowerOn(void);
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
void tulisjam(void)
{
	I2C_start();
	I2C_write(DS1307_ID);
	I2C_write(0);
	I2C_write(0);
	I2C_write(data[menit]);
	I2C_write(data[jam]);
	I2C_write(data[hari]);
	I2C_write(data[tanggal]);
	I2C_write(data[bulan]);
	I2C_write(data[tahun]);
	I2C_write(0x10);

	I2C_stop();
	delay(40);
	I2C_start();
	I2C_write(DS1307_ID);
	I2C_write(0x0e);
	I2C_write(0);
	I2C_stop();
	delay(40);
}
void bacajam(void)
{
	I2C_start();
	I2C_write(DS1307_ID);
	I2C_write(0);
	I2C_start();
	I2C_write(DS1307_ID + 1);
	data[detik] = I2C_read();
	I2C_ack();
	data[menit] = I2C_read();
	I2C_ack();
	data[jam] = I2C_read();
	I2C_ack();
	data[hari] = I2C_read();
	I2C_ack();
	data[tanggal] = I2C_read();
	I2C_ack();
	data[bulan] = I2C_read();
	I2C_ack();
	data[tahun] = I2C_read();
	I2C_stop();
}
unsigned char readeprom(unsigned int addr)
{
	unsigned char a, b, ret;
	a = addr >> 8;
	b = addr & 0x00ff;
	I2C_start();
	I2C_write(0xa0);
	I2C_write(a);
	I2C_write(b);
	I2C_start();
	I2C_write(0xa0 + 1);
	ret = I2C_read();
	I2C_nack();
	I2C_stop();
	delay(40);
	return ret;
}
void writeeprom(unsigned char c, unsigned int addr)
{
	unsigned char a, b;
	a = addr >> 8;
	b = addr & 0x00ff;
	I2C_start();
	I2C_write(0xa0);
	I2C_write(a);
	I2C_write(b);
	I2C_write(c);
	I2C_stop();
	delay(40);
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

// void tambah_jadwal(unsigned char a,unsigned char b){
// unsigned int c;
// c=(makedec(data[a])*60)+makedec(data[b]);
// c=c+jadwal_plus;
// data[a]=makebcd(c/60);
// data[b]=makebcd(c%60);
// }
// void kurang_jadwal(unsigned char a,unsigned char b){
// unsigned int c;
// c=(makedec(data[a])*60)+makedec(data[b]);
// c=c-jadwal_minus;
// data[a]=makebcd(c/60);
// data[b]=makebcd(c%60);
// }
void Baca_jadwal(void)
{
	unsigned int addr = 0;
	switch (data[bulan])
	{
	case 0x01:
		addr = Jan;
		break;
	case 0x02:
		addr = Feb;
		break;
	case 0x03:
		addr = Mar;
		break;
	case 0x04:
		addr = Apr;
		break;
	case 0x05:
		addr = Mei;
		break;
	case 0x06:
		addr = Jun;
		break;
	case 0x07:
		addr = Jul;
		break;
	case 0x08:
		addr = Agu;
		break;
	case 0x09:
		addr = Sep;
		break;
	case 0x10:
		addr = Okt;
		break;
	case 0x11:
		addr = Nov;
		break;
	case 0x12:
		addr = Des;
		break;
	}
	addr = addr + makedec(data[tanggal]);
	data[jamimsya] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[menitimsya] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[jamsubuh] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[menitsubuh] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[jamduhur] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[menitduhur] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[jamashar] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[menitashar] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[jammagrib] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[menitmagrib] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[jamisya] = readeprom(addr);
	addr = addr + incremet_jadwal;
	data[menitisya] = readeprom(addr);

	// 	jadwal_plus=makedec(readeprom(addr_tambah));
	// 	jadwal_minus=makedec(readeprom(addr_kurang));
	// /*	(alamat_jam,alamat_menit)*/
	// 	tambah_jadwal(jamimsya,menitimsya);
	// 	kurang_jadwal(jamimsya,menitimsya);
	// 	tambah_jadwal(jamsubuh,menitsubuh);
	// 	kurang_jadwal(jamsubuh,menitsubuh);
	// 	tambah_jadwal(jamduhur,menitduhur);
	// 	kurang_jadwal(jamduhur,menitduhur);
	// 	tambah_jadwal(jamashar,menitashar);
	// 	kurang_jadwal(jamashar,menitashar);
	// 	tambah_jadwal(jammagrib,menitmagrib);
	// 	kurang_jadwal(jammagrib,menitmagrib);
	// 	tambah_jadwal(jamisya,menitisya);
	// 	kurang_jadwal(jamisya,menitisya);
	hidup = readeprom(addr_hidup); /*hidup*/
	mati = readeprom(addr_mati);   /*mati*/
}
/*
void tampil(){
	unsigned char a,b;
	if (sqw==0) segmen[1]=segmen[1]&0xf7;
	else segmen[1]=segmen[1]|0x08;				//comon dulu baru data
	shiftout_jam(segmen[3]);
	shiftout_jam(segmen[2]);
	shiftout_jam(segmen[1]);
	shiftout_jam(segmen[0]);
	strobe_jam=1;
	b=0x80;
	for(a=0;a<9;a++){				//kelipatan 8			
		shiftout_jadwal(b);
		shiftout_jadwal(segmen[a+12]);
		shiftout_jadwal(b);
		shiftout_jadwal(segmen[a+20]);
		shiftout_jadwal(b);
		shiftout_jadwal(segmen[a+28]);		
		shiftout_tanggal(b);
		shiftout_tanggal(segmen[a+4]);
		b=b>>1;//(b>>1)|(b<<7);
		strobe_tanggal=1;
		strobe_jadwal=1;
		delay(1);
	}
}
*/
/*
unsigned char convert(unsigned char a){
	unsigned char b=0,c=0;
	for(b=0;b<8;b++){
		c=(c>>1)|(segmen[a]&0x80);
		segmen[a]=(segmen[a]<<1)|(segmen[a]>>7);
		a++;
	}
	return c;
}
unsigned char convertdua(unsigned char a){
	unsigned char b=0,c=0;
	a=a+4;
	for(b=0;b<4;b++){
		c=(c>>1)|(segmen[a]&0x80);
		segmen[a]=(segmen[a]<<1)|(segmen[a]>>7);
		a++;
	}
	a=a-8;
	for(b=0;b<4;b++){
		c=(c>>1)|(segmen[a]&0x80);
		segmen[a]=(segmen[a]<<1)|(segmen[a]>>7);
		a++;
	}
	return c;
}
*/

void tampil()
{
	static unsigned int temp;
	unsigned char i;
	unsigned int sum;
	for (i = 0; i < 36; i++)
	{
		sum = sum + segmen[i];
	}
	if (sum == temp)
	{
		return;
	}
	temp = sum;

	shiftout_jadwal(segmen[31]);
	shiftout_jadwal(segmen[30]); //
	shiftout_jadwal(segmen[29]); //
	shiftout_jadwal(segmen[28]); //

	shiftout_jadwal(segmen[35]);
	shiftout_jadwal(segmen[34]); //
	shiftout_jadwal(segmen[33]); //
	shiftout_jadwal(segmen[32]); //

	shiftout_jadwal(segmen[23]);
	shiftout_jadwal(segmen[22]); //
	shiftout_jadwal(segmen[21]); //
	shiftout_jadwal(segmen[20]); //

	shiftout_jadwal(segmen[27]);
	shiftout_jadwal(segmen[26]); //
	shiftout_jadwal(segmen[25]); //
	shiftout_jadwal(segmen[24]); //

	shiftout_jadwal(segmen[15]);
	shiftout_jadwal(segmen[14]); //
	shiftout_jadwal(segmen[13]); //
	shiftout_jadwal(segmen[12]); //

	shiftout_jadwal(segmen[19]);
	shiftout_jadwal(segmen[18]);
	shiftout_jadwal(segmen[17]);
	shiftout_jadwal(segmen[16]); //

	shiftout_tanggal(segmen[11]);
	shiftout_tanggal(segmen[10]);
	shiftout_tanggal(segmen[9]);
	shiftout_tanggal(segmen[8]);
	shiftout_tanggal(segmen[7]);
	shiftout_tanggal(segmen[6]);
	shiftout_tanggal(segmen[5]);
	shiftout_tanggal(segmen[4]);

	shiftout_jam(segmen[3]);
	shiftout_jam(segmen[2]);
	shiftout_jam(segmen[1]);
	shiftout_jam(segmen[0]);

	strobe_jam = 1;
	strobe_tanggal = 1;
	strobe_jadwal = 1;
}
void tampilOff()
{
	unsigned char h;
	for (h = 4; h < 12; h++)
	{
		shiftout_tanggal(data_kalender[10]);
	}
	for (h = 12; h < 36; h++)
	{
		shiftout_jadwal(data_jadwal[10]);
	}
	strobe_tanggal = 1;
	strobe_jadwal = 1;
}
void displayOff()
{
	unsigned char h;
	segmen[0] = (data_jam[10]);
	segmen[1] = (data_jam[10]);
	segmen[2] = (data_jam[10]);
	segmen[3] = (data_jam[10]);
	for (h = 4; h < 12; h++)
		segmen[h] = data_kalender[10];
	for (h = 12; h < 36; h++)
		segmen[h] = data_jadwal[10];
	tampil();
}
void load()
{
	segmen[0] = (data_jam[data[menit] & 0x0f]);
	segmen[1] = (data_jam[data[menit] >> 4]);
	segmen[2] = (data_jam[data[jam] & 0x0f]);
	segmen[3] = (data_jam[data[jam] >> 4]);

	segmen[11] = (data_kalender[data[tanggal] >> 4]);
	segmen[10] = (data_kalender[data[tanggal] & 0x0f]);
	segmen[9] = (data_kalender[data[bulan] >> 4]);
	segmen[8] = (data_kalender[data[bulan] & 0x0f]);
	segmen[7] = (data_kalender[2]);
	segmen[6] = (data_kalender[0]);
	segmen[5] = (data_kalender[data[tahun] >> 4]);
	segmen[4] = (data_kalender[data[tahun] & 0x0f]);

	segmen[28] = (data_jadwal[data[menitimsya] & 0x0f]);
	segmen[29] = (data_jadwal[data[menitimsya] >> 4]);
	segmen[30] = (data_jadwal[data[jamimsya] & 0x0f]);
	segmen[31] = (data_jadwal[data[jamimsya] >> 4]);
	segmen[32] = (data_jadwal[data[menitsubuh] & 0x0f]);
	segmen[33] = (data_jadwal[data[menitsubuh] >> 4]);
	segmen[34] = (data_jadwal[data[jamsubuh] & 0x0f]);
	segmen[35] = (data_jadwal[data[jamsubuh] >> 4]);

	segmen[20] = (data_jadwal[data[menitduhur] & 0x0f]);
	segmen[21] = (data_jadwal[data[menitduhur] >> 4]);
	segmen[22] = (data_jadwal[data[jamduhur] & 0x0f]);
	segmen[23] = (data_jadwal[data[jamduhur] >> 4]);
	segmen[24] = (data_jadwal[data[menitashar] & 0x0f]);
	segmen[25] = (data_jadwal[data[menitashar] >> 4]);
	segmen[26] = (data_jadwal[data[jamashar] & 0x0f]);
	segmen[27] = (data_jadwal[data[jamashar] >> 4]);

	segmen[12] = (data_jadwal[data[menitmagrib] & 0x0f]);
	segmen[13] = (data_jadwal[data[menitmagrib] >> 4]);
	segmen[14] = (data_jadwal[data[jammagrib] & 0x0f]);
	segmen[15] = (data_jadwal[data[jammagrib] >> 4]);
	segmen[16] = (data_jadwal[data[menitisya] & 0x0f]);
	segmen[17] = (data_jadwal[data[menitisya] >> 4]);
	segmen[18] = (data_jadwal[data[jamisya] & 0x0f]);
	segmen[19] = (data_jadwal[data[jamisya] >> 4]);
}
/******************************************************************************************/
void T_menu()
{
	buzer = BUZER_ON;
	delay(100);
	buzer = BUZER_OFF;
	while (menu == 0)
	{
		//tampil();
		menu = 1;
		delay(150);
	}
}
void T_up()
{
	buzer = BUZER_ON;
	delay(100);
	buzer = BUZER_OFF;
	while (up == 0)
	{
		//tampil();
		up = 1;
		delay(150);
	}
}
void T_down()
{
	buzer = BUZER_ON;
	delay(100);
	buzer = BUZER_OFF;
	while (down == 0)
	{
		//tampil();
		down = 1;
		delay(150);
	}
}
//seting(data,bawah,atas)
void seting(unsigned char a, unsigned char b, unsigned char c)
{
	unsigned char d = 0;
	while (menu == 1)
	{
		if (up == 0)
		{
			data[a] = makedec(data[a]);
			data[a]++;
			if (data[a] > c)
				data[a] = b;
			data[a] = makebcd(data[a]);
			if (a == 3)
				tampil_hari(data[hari]);
			else
				load();
			T_up();
		}
		if (down == 0)
		{
			data[a] = makedec(data[a]);
			data[a]--;
			if (data[a] < b || data[a] == 0xff)
				data[a] = c;
			data[a] = makebcd(data[a]);
			if (a == 3)
				tampil_hari(data[hari]);
			else
				load();
			T_down();
		}
		d = data[a];
		if (sqw == 1)
			data[a] = 0xaa;
		load();
		if (a == 3)
		{
			if (sqw == 1)
				data[a] = 0xaa;
			tampil_hari(data[hari]);
		}
		tampil();
		data[a] = d;
	}
	T_menu();
}
//parameter(data,bawah,atas)
unsigned char parameter(unsigned char a, unsigned char b, unsigned char c)
{
	unsigned char d = 0;
	while (menu == 1)
	{
		if (up == 0)
		{
			data[a] = makedec(data[a]);
			data[a]++;
			if (data[a] > c)
				data[a] = b;
			data[a] = makebcd(data[a]);
			load();
			tampil_hari(data[hari]);
			T_up();
		}
		if (down == 0)
		{
			data[a] = makedec(data[a]);
			data[a]--;
			if (data[a] < b || data[a] == 0xff)
				data[a] = c;
			data[a] = makebcd(data[a]);
			load();
			tampil_hari(data[hari]);
			T_down();
		}
		d = data[a];
		load();
		tampil_hari(data[hari]);
		if (sqw == 1)
		{
			data[a] = 0xaa;
			load();
			tampil_hari(0xaa);
		}
		tampil();
		data[a] = d;
	}
	T_menu();

	return d;
}
void tombol()
{
	unsigned char a;
	if (menu == 0)
	{
		T_menu();
		seting(2, 0, 23); //jam
		seting(1, 0, 59); //menit
		seting(4, 1, 31); //tanggal
		seting(5, 1, 12); //bulan
		seting(7, 0, 99); //tahun
		seting(3, 1, 7);  //hari
		tulisjam();		  //simpan seting
		Baca_jadwal();
		delay(600);
		PowerOn();
	}
	if (up == 0)
	{
		T_up();
		data[jam] = 0xaa;
		data[hari] = beep;
		data[menit] = readeprom(addr_beep); //set beep
		a = parameter(1, 0, 99);
		writeeprom(a, addr_beep);
		data[hari] = subuh;
		data[menit] = readeprom(addr_subuh);
		a = parameter(1, 0, 99);
		writeeprom(a, addr_subuh);
		data[hari] = duhur;
		data[menit] = readeprom(addr_duhur);
		a = parameter(1, 0, 99);
		writeeprom(a, addr_duhur);
		data[hari] = ashar;
		data[menit] = readeprom(addr_ashar);
		a = parameter(1, 0, 99);
		writeeprom(a, addr_ashar);
		data[hari] = magrib;
		data[menit] = readeprom(addr_maghrib);
		a = parameter(1, 0, 99);
		writeeprom(a, addr_maghrib);
		data[hari] = isya;
		data[menit] = readeprom(addr_isya);
		a = parameter(1, 0, 99);
		writeeprom(a, addr_isya);
		data[hari] = stanbay;
		data[menit] = readeprom(addr_stanby);
		a = parameter(1, 0, 99);
		writeeprom(a, addr_stanby);
		data[menit] = 0x00;
		data[hari] = on;
		data[jam] = readeprom(addr_hidup); //on
		a = parameter(2, 0, 23);
		writeeprom(a, addr_hidup);
		data[hari] = off;
		data[jam] = readeprom(addr_mati); //off
		a = parameter(2, 0, 23);
		writeeprom(a, addr_mati);
		data[jam] = 0xaa;
		data[hari] = jumat;
		data[menit] = readeprom(addr_jumat); //jumat
		a = parameter(1, 0, 99);
		writeeprom(a, addr_jumat);
		bacajam();
		delay(40);
		Baca_jadwal();
		load();
		delay(600);
		PowerOn();
	}
	// if (down == 0)
	// {
	// a=0;
	// while(down==0){
	// 	down=1;
	// 	delay(150);
	// 	a++;
	// 	if(a==0xff){
	// 		T_down();
	// 		data[jam]=0xaa;
	// 		data[hari]=tambah;
	// 		data[menit]=readeprom(addr_tambah);//tambah
	// 		a=parameter(1,0,99);
	// 		writeeprom(a,addr_tambah);
	// 		data[hari]=kurang;
	// 		data[menit]=readeprom(addr_kurang);//kurang
	// 		a=parameter(1,0,99);
	// 		writeeprom(a,addr_kurang);
	// 		delay(50);
	// 		bacajam();
	// 		delay(50);
	// 		Baca_jadwal();
	// 		load();
	// 		}
	// 	}
	// }
}
/******************************************************************************************/
void PowerOn(void)
{
	buzer = BUZER_ON;
	delay(400);
	buzer = BUZER_OFF;
	delay(400);
	buzer = BUZER_ON;
	delay(400);
	buzer = BUZER_OFF;
	delay(400);
	buzer = BUZER_ON;
	delay(400);
	buzer = BUZER_OFF;
}
void alarm(void)
{
	unsigned char count_down = 0, bunyi, i, j;
	unsigned int mundur = 60 * 4;
	if (data[jam] == data[jamimsya] && data[menit] == data[menitimsya])
	{
		EA = 0;
		load();
		data[hari] = imsya;
		for (i = 12; i < 36; i++)
			if (i < 28 || i > 31)
				segmen[i] = data_jadwal[10];
		for (i = 0; i < 60; i++)
		{

			while (sqw == 0)
			{
				if (i < 10)
				{
					buzer = BUZER_ON;
				}
				else
				{
					buzer = BUZER_OFF;
				}
				tampil_hari(data[hari]);
				tampil();
			}
			tampil();
			while (sqw == 1)
			{
				buzer = BUZER_OFF;
				tampilOff();
			}
		}
		goto alarm_off;
	};
	if (data[jam] == data[jamsubuh] && data[menit] == data[menitsubuh])
	{
		EA = 0;
		load();
		//	port_flag=flag_subuh;
		data[hari] = subuh;
		count_down = readeprom(addr_subuh);
		for (i = 12; i < 32; i++)
			segmen[i] = data_jadwal[10];
		goto alarm_on;
	};
	if (data[jam] == data[jamduhur] && data[menit] == data[menitduhur])
	{
		EA = 0;
		load();
		//	port_flag=flag_duhur;
		data[hari] = duhur;
		count_down = readeprom(addr_duhur);
		for (i = 12; i < 36; i++)
			if (i < 20 || i > 23)
				segmen[i] = data_jadwal[10];
		goto alarm_on;
	};
	if (data[jam] == data[jamashar] && data[menit] == data[menitashar])
	{
		EA = 0;
		load();
		//	port_flag=flag_ashar;
		data[hari] = ashar;
		count_down = readeprom(addr_ashar);
		for (i = 12; i < 36; i++)
			if (i < 24 || i > 27)
				segmen[i] = data_jadwal[10];
		goto alarm_on;
	};
	if (data[jam] == data[jammagrib] && data[menit] == data[menitmagrib])
	{
		EA = 0;
		load();
		//	port_flag=flag_magrib;
		data[hari] = magrib;
		count_down = readeprom(addr_maghrib);
		for (i = 16; i < 36; i++)
			segmen[i] = data_jadwal[10];
		goto alarm_on;
	};
	if (data[jam] == data[jamisya] && data[menit] == data[menitisya])
	{
		EA = 0;
		load();
		//	port_flag=flag_isya;
		data[hari] = isya;
		count_down = readeprom(addr_isya);
		for (i = 12; i < 36; i++)
			if (i < 16 || i > 19)
				segmen[i] = data_jadwal[10];
		goto alarm_on;
	};
	goto alarm_off;
alarm_on:
	bunyi = makedec(readeprom(addr_beep));
	while (sqw == 1)
		;
	while (mundur)
	{
		mundur--;
		if (bunyi)
		{
			buzer = BUZER_ON;
			bunyi--;
		}
		while (sqw == 0)
		{
			tampil_hari(data[hari]);
			tampil();
		}
		tampil();
		while (sqw == 1)
		{
			buzer = BUZER_OFF;
			// tampil_hari(data[hari]);
			tampilOff();
		}
	}
	//COUNT DOWN IQOMAH
	if (data[hari] == duhur)
	{
		bacajam();
		if (data[hari] == jumat)
		{
			count_down = readeprom(addr_jumat);
			goto jumatan;
		}
	}
	data[hari] = iqomah;
jumatan:
	buzer = BUZER_ON;
	delay(500);
	buzer = BUZER_OFF;
	//if(data[hari]!=jumat)
	count_down = makedec(count_down);
	while (count_down)
	{
		//	port_flag=flag_iqomah;
		count_down--;
		for (j = 59; j < 60; j--)
		{
			data[menit] = makebcd(j);
			data[jam] = makebcd(count_down);
			load();
			for (i = 12; i < 36; i++)
				segmen[i] = data_jadwal[10];
			while (sqw == 1)
			{
				tampilOff();
			}

			while (sqw == 0)
			{
				tampil_hari(data[hari]);
				tampil();
			}
			tampil();
		}
	}
	buzer = BUZER_ON;
	delay(800);
	buzer = BUZER_OFF;
	delay(800);
	buzer = BUZER_ON;
	delay(800);
	buzer = BUZER_OFF;
	delay(800);
	buzer = BUZER_ON;
	delay(3000);
	//stanby:
	buzer = BUZER_OFF;
	//if (data[hari]==jumat) mundur=60*readeprom(addr_jumat);
	//else

	mundur = 60 * makedec(readeprom(addr_stanby));
	for (i = 0; i < 4; i++)
		segmen[i] = data_jam[10];
	for (i = 4; i < 12; i++)
		segmen[i] = data_kalender[10];
	for (i = 12; i < 36; i++)
		segmen[i] = data_jadwal[10];
	tampil();
	while (mundur)
	{
		//	port_flag=flag_stanby;
		while (sqw == 1)
			;
		while (sqw == 0)
			;
		mundur--;
		displayOff();
	}
	Baca_jadwal();
alarm_off:
	EA = 1;
}
//--------------------------------------------------------------------------------------
//manual sdcc halaman 44
//nama fungsi bebas
//  __using() untuk memilih register bank
//  __interrupt() memilih alamat interupsi
//0 External 0 0x0003
//1 Timer 0 0x000b
//2 External 1 0x0013
//3 Timer 1 0x001b
//4 Serial 0x0023
//5 Timer 2 (8052) 0x002b
/*
void timer_isr (void) __interrupt (0) __using (0)
{
}
*/
void timer0_isr(void) __interrupt(1) __using(1)
{
	TR0 = 0;
	counter = 0;
}
void remot(void) __interrupt(2) __using(1)
{
	TR0 = 0;
	EA = 0;
	counter++;
	if (counter == 2)
	{
		if (TH0 < 0x0a || TH0 > 0x0b)
			counter = 0;
		data_ir = 0;
	}
	if (counter > 2 && counter < 10)
	{
		if (TH0 > 5 && TH0 < 8)
			data_ir++;
		if (TH0 < 4 || TH0 > 7)
			counter = 0;
		data_ir = (data_ir << 1) | (data_ir >> 7);
	}
	if (counter > 9)
	{
		counter = 0;
		if (data_ir == 0x08 || data_ir == 0x48)
			up = 0;
		if (data_ir == 0x06)
			menu = 0;
		if (data_ir == 0x88 || data_ir == 0xc8)
			down = 0;
		/*	//DEBUG INFO
	data[jam]=data_ir;
	data[menit]=data_ir;
	load();
	tampil();
	buzer=1;
	delay(100);
	buzer=0;
	delay(2000);
*/
	}
	TH0 = 0;
	TL0 = 0;
	TR0 = 1;
	EA = 1;
}
/***************************** Main function *************************************/
void main(void)
{
	unsigned char h;
	//unsigned int i;
	//unsigned char v;
	__bit power = 0;
	load();
	tampil();
	//segment testing
	// h = 0xfe;
	// for (;;)
	// {
	// 	//h=data_jam[v];
	// 	//v++;
	// 	if (h == 0xfe)
	// 	{
	// 		buzer = BUZER_ON;
	// 		delay(200);
	// 		buzer = BUZER_OFF;
	// 	}
	// 	for (v = 0; v < 36; v++)
	// 		shiftout_jadwal(h);
	// 	//	b=(b>>1)|(b<<7);
	// 	//	delay(1);
	// 	strobe_jadwal = 1;
	// 	h = (h << 1) | (h >> 7);
	// 	delay(1000);
	// }

	PowerOn();
	TCON = 0;	 //
	TR0 = 1;	 //
	TMOD = 0x29; //		; 2untuk serial mode 2,untuk IR mode 1 INT0
	PX1 = 1;	 //		; priority
	IT1 = 1;	 //		; set ext. int.1 to down
	EX1 = 1;	 //		; enable ext. int.1
	ET0 = 1;	 //		; enable timer overflow interup 1
	EA = 1;		 //			; Enable all interupt

	I2C_start();
	I2C_write(DS1307_ID);
	I2C_write(0x0e); //jika ds3232 0Eh
	I2C_write(0);
	I2C_stop();
	delay(40);
	bacajam();
	//tulisjam();
	Baca_jadwal();
	while (1)
	{
		bacajam();
		alarm();
		if (data[jam] == 0 && data[menit] == 0)
		{
			delay(500);
			Baca_jadwal();
		}
		for (h = 0; h < 10; h++)
		{
			while (sqw == 0)
			{
				//while(--i){
				tampil();
				tombol();
			}
			load();
			if (hidup < mati)
			{
				if (!data[jam] && data[jam] <= hidup)
					power = 0;
				if (data[jam] >= hidup && data[jam] <= mati)
					power = 1;
				if (data[jam] >= mati && data[jam] <= 0x23)
					power = 0;
			}
			if (hidup > mati)
			{
				if (!data[jam] && data[jam] <= mati)
					power = 1;
				if (data[jam] >= mati && data[jam] <= hidup)
					power = 0;
				if (data[jam] >= hidup && data[jam] <= 0x23)
					power = 1;
			};
			if (hidup == mati)
				power = 1;
			lampu = power;
			if (power == 0)
			{
				segmen[0] = (data_jam[10]);
				segmen[1] = (data_jam[10]);
				segmen[2] = (data_jam[10]);
				segmen[3] = (data_jam[10]);
				for (h = 4; h < 12; h++)
					segmen[h] = data_kalender[10];
				for (h = 12; h < 36; h++)
					segmen[h] = data_jadwal[10];
				//			port_flag=flag_stanby;
			}
			//		else port_flag=flag_normal;
			if (h < 5)
				tampil_hari(data[hari]);
			while (sqw == 1)
			{
				//while(--i){
				tampil();
				tombol();
			}
			//	i=(i<<1)|(i>>7);
		} //for
	}	  //while

} //int