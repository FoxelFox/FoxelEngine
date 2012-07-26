#pragma once

class Color{
	unsigned char RGBA[4];
public:
	Color(void);
	Color(unsigned char R, unsigned char G, unsigned char B);
	Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A);

	unsigned char* getColorArray();
	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();
	unsigned char getAlpha();

	void setColor(unsigned char r, unsigned char g, unsigned char b);
	void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void setRed(unsigned char r);
	void setGreen(unsigned char g);
	void setBlue(unsigned char b);
	void setAlpha(unsigned char a);
	unsigned char getMaximum();
	short getLuminate();
};

