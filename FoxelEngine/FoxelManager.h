#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "Foxel.h"
#include "DrawableGameComponent.h"
#include "Foxel_Interaction.h"
#include "ShaderProgram.h"
#include "Screen.h"
#include "Vec3d.h"
#include "Vec3.h"
#include "Map.h"
#include "BitCube.h"
#include <boost\thread\thread.hpp>
#include <queue>
#include "Color.h"
#include "Light.h"

#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i)) // for VBO


struct LightVertex{
	GLubyte* position;
	GLbyte* normal;
	GLubyte* color;
	LightVertex(GLubyte* position, GLbyte* normal, GLubyte* color){
		this->position = position;
		this->normal = normal;
		this->color = color;
	}
};

struct MYVertex{
	GLubyte x,y,z;
	GLbyte u,v,w;	// normal
	GLubyte r,g,b;
	bool used;
	int indexofset;
};

struct FoxelSetter{
	char x,y,z;
	char id;
};

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
static const float LIGHT_MAP_SIZE = 8;

static char renderMode = POLYGON_MODE;
static unsigned long vertexCount;
static long polyCount;
static const int BITSIZE = 128;
static const int BITSIZE_129 = 129;
static const int BITSIZE_129_X2 = BITSIZE_129*BITSIZE_129;
static const int BITSIZE_X3 = BITSIZE*BITSIZE*BITSIZE;

static int lodCenter[3];

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

static bool firstInit = true;
static bool running = true;
static unsigned char globalLevelOfDetail;
static std::vector<MYVertex*> vertexGridList;	// vertexGridList for every thread
static std::vector<MYVertex***> lightMapList;
static std::vector<boost::thread*> threads;
static boost::mutex setupQueueLock;
static int NumberOfBounceLights;



class FoxelManager{
	friend class Map;
	//             Z                X        Y
	BitCube* bitGrid;
	GLuint vbos[4];
	GLuint vao;
	Foxel* foxel;
	Vec3d position;

	bool treadUse;
	bool needSetup;
	bool doneSetup;
	bool readyToDraw;
	bool steady;		// unstady from putting  in setupQueue to finished gpu upload
	GLubyte* vertices;
	GLubyte* colors;
	GLbyte* normals;
	GLuint* indices;
	unsigned int anzFoxel;
	unsigned int anzVertex;
	unsigned int anzIndex, constAnzIndex;
	unsigned int anzPolygon;
	unsigned char lod;			// level of detail
	std::vector<Light> gi_Lights;
	std::vector<Light> directLights;
	std::queue<FoxelSetter> setterBuffer;
	std::vector<int>myID;
	std::vector<int>myNeighborUp	, myNeighborDown ,
					myNeighborLeft	, myNeighborRight,
					myNeighborBack	, myNeighborFront;
	std::vector<Brush*> brushes;

	static float* BounceLights;


public:
	FoxelManager(void);
	~FoxelManager(void);
	static void deleteAll();
	void setupFoxels(int threadID, bool genLightMap);
	static long getPolyCount();
	long getVertexCount();
	bool rayHit(Vec3* start, Vec3* end);
	static void startChunkThreads(int count);
	static void render();
	static void switchDebug();
	static void settingFoxel(Event::setFoxel* setterEvent);
	static void makeBlock(Vec3 start, Vec3 end, int id);
	static void addBrush(ChunkBrush brush);
	static void makeLine(Vec3 start, Vec3 direction, int id);
	static bool detectBulletHit(Vec3* position, Vec3* direction);
	static void update();
	static void setGlobalLod(unsigned char nlod);
	static void setLodCenter(Vec3d center);

	

	static int getNumberOfCurrentChunkUpdates();
	static int getNumberOfPendingGpuUploads();
	static int getNumberOfDirectLights();
	static int getNumberOfBounceLights();
	static float* getBounceLightArray();

private:
	FoxelManager(int x, int y, int z);
	void addLightPoints(unsigned char x, unsigned char y, unsigned char z, char visState, MYVertex*** lightMap);
	void addPolygonVertices(int x, int y, int z, char visState, const unsigned char clod, std::vector<GLuint>* v_Index, MYVertex* vertexGrid);
	void packVertices(std::vector<GLuint>* v_Index, MYVertex* vertexGrid);
	void packLightMap(MYVertex*** lightMap);
	void buildBrush(Brush* brush);
	void clearSetterBuffer();
	BitCube* generateLodGrid(const unsigned char clod);
	void uploadToGPU();
	void setLevelOfDetail(unsigned char nlod);
	static void loadAllChunks();
	static std::vector<FoxelManager*>* getChunkList();
	static std::vector<int> tracingChunkID(Vec3 point);
	static void FoxelThreadLoop(int threadID);
	static void generateBounceLightArray();
	static Vec3 tracingFoxelPositionInChunk(Vec3 point, std::vector<int> chunkID);
	static void countBounceLights();
	void setVertexToBrushColor(GLubyte* vertex, GLubyte* color,  GLbyte* normal);
	Color detectBrushColor(Vec3* position);
	void illuminateDirectly();
	void illuminateLightMap();
	std::vector<Light>* getDirectLights();
	std::vector<Light*> getSuroundingDirectlights();
	void initialise();
	void drawChunk();

	
};

static std::vector<FoxelManager*> chunks;
static std::map<std::vector<int>,FoxelManager*> idMap;
static std::queue<FoxelManager*> setupQueue;
static std::queue<FoxelManager*> uploadQueue;
