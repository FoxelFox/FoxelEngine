#pragma once
#include <sstream>
#include "TextField.h"
#include "Screen.h"
#include "Vec2.h"

class GameGUI{
private:
	bool debug;
	TextField* debugInformations;
	std::string debug_ChunkInformations;
	std::string debug_GPU_Uploads;
	std::string debug_PolycountInformation;
	std::string debug_DirectLights;
	std::string debug_BounceLights;
	
public:
	GameGUI(void);
	~GameGUI(void);
	void draw();
	void update();
	void setDebugGpuUploads(int value);
	void setDebugChunkInformation(int value);
	void setDebugPolycountInformation(long value);
	void setDebugDirectLightsCount(int value);
	void setDebugBounceLightsCount(int value);
};

