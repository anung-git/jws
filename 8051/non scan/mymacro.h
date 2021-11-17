#ifndef MYMACRO_H_
#define MYMACRO_H_

#define DS1307_ID 0xD0
#define detik 0
#define menit 1
#define jam 2
#define hari 3
#define tanggal 4
#define bulan 5
#define tahunp 6
#define tahun 7
#define jamimsya 8
#define menitimsya 9
#define jamsubuh 10
#define menitsubuh 11
#define jamduhur 12
#define menitduhur 13
#define jamashar 14
#define menitashar 15
#define jammagrib 16
#define menitmagrib 17
#define jamisya 18
#define menitisya 19

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
#define addr_beep 6001
#define addr_hidup 6002
#define addr_mati 6003
#define addr_subuh 6004
#define addr_duhur 6005
#define addr_ashar 6006
#define addr_maghrib 6007
#define addr_isya 6008
#define addr_stanby 6009
#define addr_jumat 6010
#define addr_tambah 6011
#define addr_kurang 6012
#define incremet_jadwal 40

#define port_flag P2
#define flag_subuh 0xff - 1
#define flag_duhur 0xff - 2
#define flag_ashar 0xff - 4
#define flag_magrib 0xff - 8
#define flag_isya 0xff - 16
#define flag_iqomah 0xff - 32
#define flag_normal 0xff - 64
#define flag_stanby 0xff - 128

#define BUZER_ON 0
#define BUZER_OFF 1

#define up P2_2
#define menu P2_1
#define down P2_3

#define buzer P2_5
#define sqw P0_2


// #define tombol_iqomah P0_6
#define lampu P1_5

#define strobe_jam P1_1 //pin 1
#define input_jam P1_0 //pin 2
#define clock_jam P1_2 //pin 3

#define strobe_tanggal P1_5 //pin 1
#define input_tanggal P1_4 //pin 2
#define clock_tanggal P1_3 //pin 3

#define strobe_jadwal P3_7 //pin 1
#define input_jadwal P3_6 //pin 2
#define clock_jadwal P3_5 //pin 3

#define ka     160
#define kb     131
#define kd     161
#define ke     132
#define kf     142
#define kg     144
#define kh     139
#define ki     249
#define kj     225
#define kk     138
#define kl     199
#define km1    204
#define km2    216
#define kn     200
#define ko     192
#define kp     140
#define kq     152
#define kr     206
#define ks     146
#define kt     135
#define ku     193
#define ky     145
#define k_     255

// __code (untuk menyimpan data di flash rom)
__code unsigned char data_jam[] = {192,249,164,176,153,146,130,248,128,144,0xff};

__code unsigned char data_kalender[] =  {192,249,164,176,153,146,130,248,128,144,0xff};//{0x81, 0xB7, 0xC2, 0x92, 0xB4, 0x98, 0x88, 0xB3, 0x80, 0x90, 0xFF};
__code unsigned char data_jadwal[] = {192,249,164,176,153,146,130,248,128,144,0xff};
unsigned char data[20];
unsigned char segmen[36];
unsigned char hidup, mati, jadwal_plus, jadwal_minus;
volatile unsigned char data_ir;
unsigned char volatile counter;

#endif // MACRO



