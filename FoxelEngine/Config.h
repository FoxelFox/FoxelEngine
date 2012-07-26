#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

enum DisplayMode{ DISPLAY_NORMAL, DISPLAY_WIRE, DISPLAY_QUAD, DISPLAY_WITHOUT_RAD };

class Config{
	std::vector<std::string> configContent;
	int screenW, screenH;
	bool fullscreen;

	static DisplayMode displayMode;
	static bool debug;
	static int chunkThreads;

public:
	Config(void);
	void readConfig(std::string fileName);
	int getScreenW();
	int getScreenH();
	
	bool isFullscreen();
	~Config(void);

	void switchDebugMode();
	void setDisplayMode(DisplayMode mode);

	static bool isDebug();
	static DisplayMode getDisplayMode();
	static int getChunkThreads();
};

