#include "Config.h"
#include <iostream>
using namespace std;
Config::Config(void){

	screenW = 1280;
	screenH = 720;
	fullscreen = true;
}

void Config::readConfig(string fileName){
	ifstream file;
	file.open(fileName);
	if(file.is_open()){
		string tmp;
		while(!file.eof()){
			file >> tmp;
			configContent.push_back(tmp);
		}
	}else{
		cout << "No config found, use default settings" << endl;
		screenW = GetSystemMetrics(SM_CXSCREEN);	// Windows screen X Information
		screenH = GetSystemMetrics(SM_CYSCREEN);	// Windows screen Y Information

		return;
	}
	for(unsigned int i = 0; i < configContent.size(); i++){
		if(configContent[i] == "fullscreen"){
			if(configContent[i+1] == "false"){
				fullscreen = false;
			}
		}
		if(configContent[i] == "width"){
			stringstream ss;
			ss << configContent[i+1];
			ss >> screenW;
		}
		if(configContent[i] == "height"){
			stringstream ss;
			ss << configContent[i+1];
			ss >> screenH;
		}
	}

}

int Config::getScreenW(){
	return screenW;
}

int Config::getScreenH(){
	return screenH;
}

bool Config::isFullscreen(){
	return fullscreen;
}

Config::~Config(void)
{
}
