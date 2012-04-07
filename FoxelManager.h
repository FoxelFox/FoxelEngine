#pragma once
#include <bitset>
#include <vector>
#include <map>
#include "Foxel.h"
#include "DrawableGameComponent.h"
#include "Foxel_Interaction.h"
#include "Vec3d.h"

#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i)) // for VBO

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

class FoxelManager : public DrawableGameComponent
{
	//             Z                X        Y
	std::bitset<BITSIZE> bitGrid[BITSIZE][BITSIZE];
	GLint* vertices;
	GLuint vbo;
	Foxel* foxel;
	unsigned int anzFoxel;
	unsigned short lod;			// level of detail
	std::vector<int>myID;
	std::vector<int>myNeighborUp	, myNeighborDown ,
					myNeighborLeft	, myNeighborRight,
					myNeighborBack	, myNeighborFront;

public:
	FoxelManager(void);
	~FoxelManager(void);
	void deleteAll();
	void setupFoxels();
	void settingFoxel(Event::setFoxel* setterEvent);
	long getPolyCount();
	long getVertexCount();
	void render();

private:
	FoxelManager(int x, int y, int z);
	std::vector<int> genNewID(int x, int y, int z);
	void addPointVertices(GLint x, GLint y, GLint z, char visState, std::vector<GLint>* v_Vertex);
	void addPolygonVertices(GLint x, GLint y, GLint z, char visState, std::vector<GLint>* v_Vertex);
	void packVertices(std::vector<GLint> *v_Vertex);
	void initialise();
	void drawChunk();
};

static std::vector<FoxelManager*> chunks;
static std::map<std::vector<int>,FoxelManager*> idMap;