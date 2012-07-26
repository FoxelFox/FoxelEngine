#include "BitCube.h"


void BitCube::set(unsigned char x,unsigned char y,unsigned char z,bool state){
	bitGrid[x][y][z] = state;
}

bool BitCube::get(unsigned char x,unsigned char y,unsigned char z){
	return bitGrid[x][y][z];
}