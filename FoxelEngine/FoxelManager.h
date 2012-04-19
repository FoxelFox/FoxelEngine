#pragma once
#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include "Foxel.h"
#include "DrawableGameComponent.h"
#include "Foxel_Interaction.h"
#include "ShaderProgram.h"
#include "Screen.h"
#include "Vec3d.h"

static const char UP	=  1;
static const char DOWN	=  2;
static const char LEFT	=  4;
static const char RIGHT =  8;
static const char FRONT = 16;
static const char BACK	= 32;

static const int idUP	 =   1;
static const int idDOWN  =  -1;
static const int idFRONT =   1;
static const int idBACK  =  -1;
static const int idLEFT  =   1;
static const int idRIGHT =  -1;

// render modes
static const char POINT_MODE = 1;
static const char POLYGON_MODE = 2;

static char renderMode;
static unsigned long vertexCount;
static unsigned long polyCount;
static const int BITSIZE = 128;
static bool debug = false;

static GLfloat debugChunkBoxV[] = {0.0f ,  0.0f ,  0.0f ,
								  128.0f,  0.0f ,  0.0f ,
								   0.0f , 128.0f,  0.0f ,
								   0.0f ,  0.0f , 128.0f,
								  128.0f, 128.0f, 128.0f,
								   0.0f , 128.0f, 128.0f,
								  128.0f,  0.0f , 128.0f,
								  128.0f, 128.0f,  0.0f ,};

static GLuint debugChunkBoxI[] = {0,1, 0,2, 0,3, 4,5, 4,6, 4,7,
								  1,6, 2,5, 3,5, 2,7, 3,6, 1,7};

class FoxelManager{
	//             Z                X        Y
	std::bitset<BITSIZE> bitGrid[BITSIZE][BITSIZE];
	GLuint vbos[2];
	GLuint vao;
	Foxel* foxel;
	Vec3d position;
	GLfloat *vertices, *normals;
	unsigned int anzFoxel;
	unsigned int anzVertex;
	unsigned int anzIndex;
	unsigned int anzPolygon;
	unsigned short lod;			// level of detail
	std::vector<int>myID;
	std::vector<int>myNeighborUp	, myNeighborDown ,
					myNeighborLeft	, myNeighborRight,
					myNeighborBack	, myNeighborFront;

public:
	FoxelManager(void);
	~FoxelManager(void);
	static void deleteAll();
	void setupFoxels();
	long getPolyCount();
	long getVertexCount();
	static void render();
	static void switchDebug();
	static void settingFoxel(Event::setFoxel* setterEvent);
private:
	FoxelManager(int x, int y, int z);
	std::vector<int> genNewID(int x, int y, int z);
	void addPointVertices(GLfloat x, GLfloat y, GLfloat z, char visState, std::vector<GLfloat>* v_Vertex, std::vector<GLfloat>* v_Normal);
	void addPolygonVertices(GLfloat x, GLfloat y, GLfloat z, char visState, std::vector<GLfloat>* v_Vertex, std::vector<GLfloat>* v_Normal);
	void packVertices(std::vector<GLfloat> *v_Vertex, std::vector<GLfloat>* v_Normal);
	void initialise();
	void drawChunk();
};

static std::vector<FoxelManager*> chunks;
static std::map<std::vector<int>,FoxelManager*> idMap;