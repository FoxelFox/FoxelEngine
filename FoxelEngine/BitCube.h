#pragma once
#include <bitset>
class BitCube
{
public:
	std::bitset<128> bitGrid[128][128];
	void set(unsigned char x,unsigned char y,unsigned char z,bool state);
	bool get(unsigned char x,unsigned char y,unsigned char z);
};
