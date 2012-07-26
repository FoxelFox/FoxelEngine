#include "DirectLight.h"

DirectLight::DirectLight(std::vector<int> id){
	this->id = id;
}


float* DirectLight::generateDirectLightArray(){
	float* lightArray = new float[lights.size()*10];
	int k = 0;
	for(int i = 0; i < lights.size();i++){
		lightArray[k+0] = lights[i].position.x;
		lightArray[k+1] = lights[i].position.y;
		lightArray[k+2] = lights[i].position.z;

		lightArray[k+3] = lights[i].normal.x;
		lightArray[k+4] = lights[i].normal.y;
		lightArray[k+5] = lights[i].normal.z;

		lightArray[k+6] = lights[i].color.getRed();
		lightArray[k+7] = lights[i].color.getGreen();
		lightArray[k+8] = lights[i].color.getBlue();
		lightArray[k+9] = lights[i].color.getAlpha();
		k += 10;
	}
	return lightArray;
}

std::vector<Light> DirectLight::getLight(){
	return lights;
}