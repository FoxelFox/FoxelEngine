#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

class Config{
	std::vector<std::string> configContent;
	int screenW, screenH;
	bool fullscreen;

public:
	Config(void);
	void readConfig(std::string fileName);
	int getScreenW();
	int getScreenH();
	bool isFullscreen();
	~Config(void);
};

