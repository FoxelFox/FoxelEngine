#pragma once
#include <stack>
#include "Vec3.h"
#include <vector>
#include <string>
#include "Color.h"
class Brush{
public:
	unsigned char sX,sY,sZ;		// Start Point x y z;
	unsigned char eX,eY,eZ;		// End Point x y z;
	unsigned char cR,cG,cB,em;		// Color
	short id;					// Foxel id
	Brush(){}
	Brush(unsigned char sX, unsigned char sY, unsigned char sZ,
		  unsigned char eX, unsigned char eY, unsigned char eZ,
		  short id, unsigned char cR, unsigned char cG, unsigned char cB,
		  unsigned char em){
		this->sX = sX; this->sY = sY; this->sZ = sZ;
		this->eX = eX; this->eY = eY; this->eZ = eZ;
		this->id = id; this->cR = cR; this->cG = cG;
		this->cB = cB; this->em = em;
	}
};

class ChunkBrush : public Brush {
public:
	int idX, idY, idZ;
};

class Map{
	static std::string name;
public:
	Map();
	~Map(void);
	static void createBlock(Vec3 start, Vec3 end, short id, Color color);
	static void update();
	static bool load(std::string mapName);
	static void save(std::string mapName);
};