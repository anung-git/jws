
#include "util.h"
void delay(unsigned int a){
	unsigned char c;
	for(;a>0;a--)
	for(c=0;c<100;c++);
}