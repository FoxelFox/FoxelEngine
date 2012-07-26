#include "Convert.h"

float Convert::degToRad(float* deg){
	return (float) PI**deg/180;
}

double Convert::degToRad(double* deg){
	return PI**deg/180;
}

float Convert::degToRad(float deg){
	return (float) PI*deg/180;
}

double Convert::degToRad(double deg){
	return PI*deg/180;
}
