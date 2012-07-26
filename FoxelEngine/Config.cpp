#include "Config.h"
#include <iostream>
using namespace std;

DisplayMode Config::displayMode = DISPLAY_NORMAL;
bool Config::debug = true;
int Config::chunkThreads = 1;

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
		if(configContent[i] == "Fullscreen"){
			if(configContent[i+1] == "false"){
				fullscreen = false;
			}
		}
		if(configContent[i] == "Width"){
			stringstream ss;
			ss << configContent[i+1];
			ss >> screenW;
		}
		if(configContent[i] == "Height"){
			stringstream ss;
			ss << configContent[i+1];
			ss >> screenH;
		}
		if(configContent[i] == "ChunkThreads"){
			stringstream ss;
			ss << configContent[i+1];
			ss >> chunkThreads;
		}
	}
}

void Config::switchDebugMode(){
	if(debug) debug = false;
	else debug = true;
}

void Config::setDisplayMode(DisplayMode mode){
	displayMode = mode;
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
bool Config::isDebug(){
	return debug;
}
DisplayMode Config::getDisplayMode(){
	return displayMode;
}
int Config::getChunkThreads(){
	return chunkThreads;
}