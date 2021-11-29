

#ifndef HARI_H_
#define HARI_H_

#include "mymacro.h"


void tampil_hari(unsigned char a){
/*
unsigned char b;
if(a==0) for(b=4;b<12;b++) segmen[10]=ahad[(b-4)];
else if(a==1) for(b=4;b<12;b++) segmen[10]=senin[(b-4)];
else if(a==2) for(b=4;b<12;b++) segmen[10]=selasa[(b-4)];
else if(a==3) for(b=4;b<12;b++) segmen[10]=rabu[(b-4)];
else if(a==4) for(b=4;b<12;b++) segmen[10]=kamis[(b-4)];
else if(a==5) for(b=4;b<12;b++) segmen[10]=jumat[(b-4)];
else if(a==6) for(b=4;b<12;b++) segmen[10]=sabtu[(b-4)];
*/
#define ahad 7
if(a==7){
	segmen[11]=ka;
	segmen[10]=kh;
	segmen[9]=ka;
	segmen[8]=kd;
	segmen[7]=k_;
	segmen[6]=k_;
	segmen[5]=k_;
	segmen[4]=k_;
	}
#define senin 1
else if(a==1){
	segmen[11]=k_;
	segmen[10]=ks;
	segmen[9]=ke;
	segmen[8]=kn;
	segmen[7]=ki;
	segmen[6]=kn;
	segmen[5]=k_;
	segmen[4]=k_;
	}
#define selasa 2
else if(a==2){
	segmen[11]=ks;
	segmen[10]=ke;
	segmen[9]=kl;
	segmen[8]=ka;
	segmen[7]=ks;
	segmen[6]=ka;
	segmen[5]=k_;
	segmen[4]=k_;
	}
#define rabu 3
else if(a==3){
	segmen[11]=k_;
	segmen[10]=k_;
	segmen[9]=kr;
	segmen[8]=ka;
	segmen[7]=kb;
	segmen[6]=ku;
	segmen[5]=k_;
	segmen[4]=k_;
	}
#define kamis 4
else if(a==4){
	segmen[11]=kk;
	segmen[10]=ka;
	segmen[9]=km1;
	segmen[8]=km2;
	segmen[7]=ki;
	segmen[6]=ks;
	segmen[5]=k_;
	segmen[4]=k_;
	}
#define jumat 5
else if(a==5){
	segmen[11]=kj;
	segmen[10]=ku;
	segmen[9]=km1;
	segmen[8]=km2;
	segmen[7]=ka;
	segmen[6]=kt;
	segmen[5]=k_;
	segmen[4]=k_;
	}
#define sabtu 6
else if(a==6){
	segmen[11]=ks;
	segmen[10]=ka;
	segmen[9]=kb;
	segmen[8]=kt;
	segmen[7]=ku;
	segmen[6]=k_;
	segmen[5]=k_;
	segmen[4]=k_;
	}
#define beep 8
else if(a==8){
	segmen[11]=k_;
	segmen[10]=k_;
	segmen[9]=kb;
	segmen[8]=ke;
	segmen[7]=ke;
	segmen[6]=kp;
	segmen[5]=k_;
	segmen[4]=k_;
	}
#define on 9
else if(a==9){
	segmen[11]=k_;
	segmen[10]=k_;
	segmen[9]=k_;
	segmen[8]=k_;
	segmen[7]=k_;
	segmen[6]=k_;
	segmen[5]=ko;
	segmen[4]=kn;
	}
#define off 10
else if(a==10){
	segmen[11]=k_;
	segmen[10]=k_;
	segmen[9]=k_;
	segmen[8]=k_;
	segmen[7]=k_;
	segmen[6]=ko;
	segmen[5]=kf;
	segmen[4]=kf;
	}
#define imsya 11
else if(a==11){
	segmen[11]=k_;
	segmen[10]=ki;
	segmen[9]=km1;
	segmen[8]=km2;
	segmen[7]=ks;
	segmen[6]=ky;
	segmen[5]=ka;
	segmen[4]=k_;
	}
#define subuh 12
else if(a==12){
	segmen[11]=k_;
	segmen[10]=k_;
	segmen[9]=ks;
	segmen[8]=ku;
	segmen[7]=kb;
	segmen[6]=ku;
	segmen[5]=kh;
	segmen[4]=k_;
	}
#define duhur 13
else if(a==13){
	segmen[11]=k_;
	segmen[10]=k_;
	segmen[9]=kd;
	segmen[8]=ku;
	segmen[7]=kh;
	segmen[6]=ku;
	segmen[5]=kr;
	segmen[4]=k_;
	}
#define ashar 14
else if(a==14){
	segmen[11]=k_;
	segmen[10]=k_;
	segmen[9]=ka;
	segmen[8]=ks;
	segmen[7]=kh;
	segmen[6]=ka;
	segmen[5]=kr;
	segmen[4]=k_;
	}
#define magrib 15
else if(a==15){
	segmen[11]=km1;
	segmen[10]=km2;
	segmen[9]=ka;
	segmen[8]=kg;
	segmen[7]=kh;
	segmen[6]=kr;
	segmen[5]=ki;
	segmen[4]=kb;
	}
#define isya 16
else if(a==16){
	segmen[11]=k_;
	segmen[10]=k_;
	segmen[9]=ki;
	segmen[8]=ks;
	segmen[7]=ky;
	segmen[6]=ka;
	segmen[5]=k_;
	segmen[4]=k_;
	}
#define stanbay 17
else if(a==17){
	segmen[11]=ks;
	segmen[10]=kt;
	segmen[9]=ka;
	segmen[8]=kn;
	segmen[7]=kb;
	segmen[6]=ky;
	segmen[5]=k_;
	segmen[4]=k_;
	}
#define iqomah 18
else if(a==18){
	segmen[11]=k_;
	segmen[10]=ki;
	segmen[9]=kq;
	segmen[8]=ko;
	segmen[7]=km1;
	segmen[6]=km2;
	segmen[5]=ka;
	segmen[4]=kh;
	}

#define tambah 20
else if(a==20){
	segmen[11]=kt;
	segmen[10]=ka;
	segmen[9]=km1;
	segmen[8]=km2;
	segmen[7]=kb;
	segmen[6]=ka;
	segmen[5]=kh;
	segmen[4]=k_;
	}

#define kurang 21
else if(a==21){
	segmen[11]=kk;
	segmen[10]=ku;
	segmen[9]=kr;
	segmen[8]=ka;
	segmen[7]=kn;
	segmen[6]=kg;
	segmen[5]=k_;
	segmen[4]=k_;
	}

else if(a==0xaa){
	segmen[11]=k_;
	segmen[10]=k_;
	segmen[9]=k_;
	segmen[8]=k_;
	segmen[7]=k_;
	segmen[6]=k_;
	segmen[5]=k_;
	segmen[4]=k_;
	}
}
#endif // HARI_H_