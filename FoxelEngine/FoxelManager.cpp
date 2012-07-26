#include "FoxelManager.h"
#include <math.h>
#include "TextButton.h"
#include <sstream>
#include "Config.h"
#include <math.h>
#include "CollisionDetector.h"
// Index Formel: index = [(x+y*BITSIZE)+z*BITSIZE*BITSIZE]
using namespace std;
using namespace GLSL;

float* FoxelManager::BounceLights = NULL;

FoxelManager::FoxelManager(void){
	vertexCount = 0;
	polyCount = 0;

	initialise();

}

/*
	=============================================
	Creates a new Chnunk at the specific Position
	=============================================
 */
FoxelManager::FoxelManager(int x, int y, int z){
	
	// first chunk?
	if(firstInit){
		firstInit = false;
		lodCenter[0] = 0;
		lodCenter[1] = 0;
		lodCenter[2] = 0;	
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(4,vbos); // vertices Normals and Indices

	position.x = (float) x * BITSIZE;
	position.y = (float) y * BITSIZE;
	position.z = (float) z * BITSIZE;

	myID.push_back(x);
	myID.push_back(y);
	myID.push_back(z);

	initialise();
	chunks.push_back(this);
	
}

FoxelManager::~FoxelManager(){
	while(!doneSetup){ // wait until the Chunk is ready for delete
		boost::this_thread::sleep(boost::posix_time::millisec(100));
	}
	delete foxel;
	delete bitGrid;
	for(int i = 0; i < brushes.size();i++){
		delete brushes[i];
	}
	
	glDeleteVertexArrays(1,&vao); //crashing
	glDeleteBuffers(3,vbos);
}

void FoxelManager::deleteAll(){
	for(int i = 0; i < (int)chunks.size(); i++){
		delete chunks[i];
	}
	chunks.clear();
	idMap.clear();
	
	while(!setupQueue.empty()){
		setupQueue.pop();
	}

	while(!uploadQueue.empty()){
		uploadQueue.pop();
	}
}

void FoxelManager::startChunkThreads(int count){
	

	for(int threadID = 0; threadID < count; threadID++){
		// Init VertexGrid
		vertexGridList.push_back(new MYVertex[(BITSIZE+1)*(BITSIZE+1)*(BITSIZE+1)]);
		int i = 0;
		for(unsigned char z = 0; z < BITSIZE+1; z++){
			for(unsigned char y = 0; y < BITSIZE+1; y++){
				for(unsigned char x = 0; x < BITSIZE+1; x++){
					vertexGridList.at(threadID)[i].x = x;
					vertexGridList.at(threadID)[i].y = y;
					vertexGridList.at(threadID)[i].z = z;
					
					vertexGridList.at(threadID)[i].r = 255;
					vertexGridList.at(threadID)[i].g = 255;
					vertexGridList.at(threadID)[i].b = 255;

					vertexGridList.at(threadID)[i].u = 0;
					vertexGridList.at(threadID)[i].v = 0;
					vertexGridList.at(threadID)[i].w = 0;

					//vertexGridList.at(threadID)[i].a = 255;
					
					vertexGridList.at(threadID)[i].used = false;
					i ++;
				}
			}
		}
		MYVertex*** lightMap = new MYVertex**[18];
		for(int a = 0; a < 18; a++){
			lightMap[a] = new MYVertex*[18];
			for(int b = 0; b < 18; b++){
				lightMap[a][b] = new MYVertex[18];
			}
		}
		lightMapList.push_back(lightMap);
		for(unsigned char x = 0; x <= BITSIZE/LIGHT_MAP_SIZE+1; x++){
			for(unsigned char y = 0; y <= BITSIZE/LIGHT_MAP_SIZE+1; y++){
				for(unsigned char z = 0; z <= BITSIZE/LIGHT_MAP_SIZE+1; z++){
					lightMapList.at(threadID)[x][y][z].x = (x) * LIGHT_MAP_SIZE;
					lightMapList.at(threadID)[x][y][z].y = (y) * LIGHT_MAP_SIZE;
					lightMapList.at(threadID)[x][y][z].z = (z) * LIGHT_MAP_SIZE;
					

					lightMapList.at(threadID)[x][y][z].r = 255;
					lightMapList.at(threadID)[x][y][z].g = 128;
					lightMapList.at(threadID)[x][y][z].b = 25;

					lightMapList.at(threadID)[x][y][z].u = 0;
					lightMapList.at(threadID)[x][y][z].v = 0;
					lightMapList.at(threadID)[x][y][z].w = 0;
					lightMapList.at(threadID)[x][y][z].used = false;
				}
			}
		}


		threads.push_back(new boost::thread(boost::bind(&FoxelManager::FoxelThreadLoop, threadID)));
	}
	
}


void FoxelManager::FoxelThreadLoop(int threadID){
	
	FoxelManager* currentFM;
	cout << endl << endl << "ChunkWorkerThread: " << threadID << " is running..." << endl;

	while(running){
		bool setup = false;

		{
			setupQueueLock.lock();
			if(!setupQueue.empty()){
				setup = true;
				currentFM = setupQueue.front();
				setupQueue.pop();
			}
			setupQueueLock.unlock();
		}

		if(setup){
			currentFM->needSetup = false;
			currentFM->doneSetup = false;
			currentFM->clearSetterBuffer();
			currentFM->setupFoxels(threadID,true);
			currentFM->setupFoxels(threadID,false);
		}else{
			boost::this_thread::sleep(boost::posix_time::microsec(1000 + 2 * threadID));
		}
	}
	
}


void FoxelManager::initialise(){
	lod = 8;
	foxel = NULL;
	vertices = NULL;
	normals = NULL;
	indices = NULL;
	colors = NULL;
	anzFoxel = 0;
	anzVertex = 0;
	anzPolygon = 0;
	readyToDraw = false;
	treadUse = false;
	needSetup = true;
	steady = true;
	doneSetup = true;
	idMap[myID] = this;
	bitGrid = new BitCube();

	myNeighborUp.push_back   (myID[0]  ); myNeighborUp.push_back   (myID[1]  );	myNeighborUp.push_back	 (myID[2]+1);
	myNeighborDown.push_back (myID[0]  ); myNeighborDown.push_back (myID[1]  ); myNeighborDown.push_back (myID[2]-1);
	myNeighborLeft.push_back (myID[0]-1); myNeighborLeft.push_back (myID[1]  ); myNeighborLeft.push_back (myID[2]  );
	myNeighborRight.push_back(myID[0]+1); myNeighborRight.push_back(myID[1]  ); myNeighborRight.push_back(myID[2]  );
	myNeighborFront.push_back(myID[0]  ); myNeighborFront.push_back(myID[1]+1); myNeighborFront.push_back(myID[2]  );
	myNeighborBack.push_back (myID[0]  ); myNeighborBack.push_back (myID[1]-1); myNeighborBack.push_back (myID[2]  );

	for(unsigned char x = 0; x < BITSIZE; x++){
		for(unsigned char y = 0; y < BITSIZE; y++){
			for(unsigned char z = 0; z < BITSIZE; z++){
				bitGrid->set(x,y,z,false);
			}
		}
	}
}
/*
	==================================================
	Generates the the mesh only from the visable sides
	of one Foxel and pack it to one GLint Vertex Array
	that will be transfared to the GPU memory.
	==================================================
*/
void FoxelManager::setupFoxels(int threadID, bool genLightMap){
	if(treadUse){
		cout << "WARNING! THREAD INTERSECTION!" << endl;
		return;
	}else{
		treadUse = true;
	}

	char visState = 0;
	MYVertex* vertexGrid = vertexGridList.at(threadID);
	MYVertex*** lightMap = lightMapList.at(threadID);
	std::vector<GLuint> v_Index;
	BitCube* bitCube;
	
	// select the lod level
	unsigned char selected_lod;
	if(genLightMap){
		selected_lod = LIGHT_MAP_SIZE;
		gi_Lights.clear();
	}else{
		selected_lod = lod;
	}

	register const unsigned char clod = selected_lod;

	if(clod == 1){
		// use the native bitGrid
		bitCube = bitGrid;
	}else{
		// use a smaller one
		bitCube = generateLodGrid(clod);
	}

	register const unsigned char max = BITSIZE/clod;
	for(register unsigned char x = 0; x < max; x++){
		for(register unsigned char y = 0; y < max; y++){
			for(register unsigned char z = 0; z < max; z++){
				if(bitCube->get(x,y,z)){

					if(z == max-1){
						if(idMap.find(myNeighborUp) != idMap.end()){
							if(idMap[myNeighborUp]->bitGrid->get(x*clod,y*clod,0) == false){
								visState |= UP;
							}
						}else{ // No Chunk TopSide
							visState |= UP;
						}
					}else if(bitCube->get( x , y ,z+1) == false){ visState |= UP	;}

					if(z == 0){
						if(idMap.find(myNeighborDown) != idMap.end()){
							if(idMap[myNeighborDown]->bitGrid->get(x*clod,y*clod,BITSIZE-1) == false){
								visState |= DOWN;
							}
						}else{ // No Chunk DownSide
							visState |= DOWN;
						}
					}else if(bitCube->get( x , y ,z-1) == false){ visState |= DOWN ;}

					if(x == 0){
						if(idMap.find(myNeighborLeft) != idMap.end()){
							if(idMap[myNeighborLeft]->bitGrid->get(BITSIZE-1,y*clod,z*clod) == false){
								visState |= LEFT ;
							}
						}else{ // No Chunk LeftSide
							visState |= LEFT;
						}
					}else if(bitCube->get(x-1, y , z ) == false){ visState |= LEFT ;}

					if(x == max-1){
						if(idMap.find(myNeighborRight) != idMap.end()){
							if(idMap[myNeighborRight]->bitGrid->get(0,y*clod,z*clod) == false){
								visState |= RIGHT;
							}
						}else{ // No Chunk LeftSide
							visState |= RIGHT;
						}
					}else if(bitCube->get(x+1, y , z ) == false){ visState |= RIGHT;}

					if(y == max-1){
						if(idMap.find(myNeighborFront) != idMap.end()){
							if(idMap[myNeighborFront]->bitGrid->get(x*clod,0,z*clod) == false){
								visState |= FRONT;
							}
						}else{ // No Chunk FrontSide
							visState |= FRONT;
						}
					}else if(bitCube->get( x ,y+1, z ) == false){ visState |= FRONT;}

					if(y == 0){
						if(idMap.find(myNeighborBack) != idMap.end()){
							if(idMap[myNeighborBack]->bitGrid->get(x*clod,BITSIZE-1,z*clod) == false){
								visState |= BACK;
							}
						}else{ // No Chunk BackSide
							visState |= BACK;
						}
					}else if(bitCube->get( x ,y-1, z ) == false){ visState |= BACK ;}

					if(visState > 0){	// Foxel is visable
						//v_Foxel.push_back(Foxel(1,visState));
						if(genLightMap){
							addLightPoints(x,y,z,visState,lightMap);
						}else{
							addPolygonVertices(x*clod,y*clod,z*clod,visState,clod,&v_Index,vertexGrid);
						}
						visState = 0;
					}
				}
			}
		}
	}
	if(genLightMap){
		packLightMap(lightMap);
		
	}else{
		packVertices(&v_Index,vertexGrid);
		doneSetup = true;
	}
	if(clod != 1) delete bitCube;
	treadUse = false;
}

BitCube* FoxelManager::generateLodGrid(const unsigned char clod){
	BitCube* lodGrid = new BitCube();
	const int max = BITSIZE/clod;
	for(unsigned char x = 0; x < max; x++){
		for(unsigned char y = 0; y < max; y++){
			for(unsigned char z = 0; z < max; z++){
				int hits = 0;
				for(unsigned char a = 0; a < clod; a++){
					for(unsigned char b = 0; b < clod; b++){
						for(unsigned char c = 0; c < clod; c++){
			
						
							if(bitGrid->get(x*clod+a, y*clod+b, z*clod+c)) hits++;
						}
					}
				}
				if(hits >= (int)pow((double)clod,(int)3)/2)lodGrid->set(x,y,z,true);
				else lodGrid->set(x,y,z,false);
			}
		}
	}
	return lodGrid;
}

/*
	===============================================
	
	===============================================
*/
void FoxelManager::addLightPoints(unsigned char x, unsigned char y, unsigned char z, char visState, MYVertex*** lightMap){

	const float s = 0.5f * LIGHT_MAP_SIZE;
	const float d = (float)LIGHT_MAP_SIZE;
	
	if(visState & UP){
		lightMap[ x ][ y ][z+1].used = true; lightMap[ x ][ y ][z+1].w++;
		lightMap[x+1][ y ][z+1].used = true; lightMap[x+1][ y ][z+1].w++;
		lightMap[ x ][y+1][z+1].used = true; lightMap[ x ][y+1][z+1].w++;
		lightMap[x+1][y+1][z+1].used = true; lightMap[x+1][y+1][z+1].w++;
		//gi_Lights.push_back(Light(Vec3(x+s,y+s,z+d),Vec3( 0.0f, 0.0f, 1.0f),Color(128,128,128,64)));
	}
	if(visState & DOWN){
		lightMap[ x ][ y ][z].used = true; lightMap[ x ][ y ][z].w--;
		lightMap[x+1][ y ][z].used = true; lightMap[x+1][ y ][z].w--;
		lightMap[ x ][y+1][z].used = true; lightMap[ x ][y+1][z].w--;
		lightMap[x+1][y+1][z].used = true; lightMap[x+1][y+1][z].w--;
		//gi_Lights.push_back(Light(Vec3(x+s,y+s, z ),Vec3( 0.0f, 0.0f,-1.0f),Color(128,128,128,64)));
	}
	if(visState & LEFT){
		lightMap[x][ y ][ z ].used = true; lightMap[x][ y ][ z ].u--;
		lightMap[x][y+1][ z ].used = true; lightMap[x][y+1][ z ].u--;
		lightMap[x][ y ][z+1].used = true; lightMap[x][ y ][z+1].u--;
		lightMap[x][y+1][z+1].used = true; lightMap[x][y+1][z+1].u--;
		//gi_Lights.push_back(Light(Vec3( x ,y+s,z+s),Vec3(-1.0f, 0.0f, 0.0f),Color(128,128,128,64)));
	}
	if(visState & RIGHT){
		lightMap[x+1][ y ][ z ].used = true; lightMap[x+1][ y ][ z ].u++;
		lightMap[x+1][y+1][ z ].used = true; lightMap[x+1][y+1][ z ].u++;
		lightMap[x+1][ y ][z+1].used = true; lightMap[x+1][ y ][z+1].u++;
		lightMap[x+1][y+1][z+1].used = true; lightMap[x+1][y+1][z+1].u++;
		//gi_Lights.push_back(Light(Vec3(x+d,y+s,z+s),Vec3( 1.0f, 0.0f, 0.0f),Color(128,128,128,64)));
	}
	if(visState & FRONT){
		lightMap[ x ][y+1][ z ].used = true; lightMap[ x ][y+1][ z ].v++;
		lightMap[x+1][y+1][ z ].used = true; lightMap[x+1][y+1][ z ].v++;
		lightMap[ x ][y+1][z+1].used = true; lightMap[ x ][y+1][z+1].v++;
		lightMap[x+1][y+1][z+1].used = true; lightMap[x+1][y+1][z+1].v++;
		//gi_Lights.push_back(Light(Vec3(x+s,y+d,z+s),Vec3( 0.0f, 1.0f, 0.0f),Color(128,128,128,64)));
	}
	if(visState & BACK){
		lightMap[ x ][y][ z ].used = true; lightMap[ x ][y][ z ].v--;
		lightMap[x+1][y][ z ].used = true; lightMap[x+1][y][ z ].v--;
		lightMap[ x ][y][z+1].used = true; lightMap[ x ][y][z+1].v--;
		lightMap[x+1][y][z+1].used = true; lightMap[x+1][y][z+1].v--;

		//gi_Lights.push_back(Light(Vec3(x+s, y ,z+s),Vec3( 0.0f,-1.0f, 0.0f),Color(128,128,128,64)));
	}
	
}
/*
	===========================================
	Adding 4 or more vertices to the vertex
	colection as Quads
	===========================================
*/
void FoxelManager::addPolygonVertices(int x, int y, int z, char visState, const unsigned char clod, std::vector<GLuint>* v_Index, MYVertex* vertexGrid){
	
	GLfloat d = (GLfloat)1*clod;
	//x *= lod;
	//y *= lod;
	//z *= lod;

	register int zo = (z+clod) * BITSIZE_129_X2;
	register int zu =   z   * BITSIZE_129_X2;

	const int v1 = (  x   +   y   * BITSIZE_129) + zo;
	register int v2 = ((x+clod) +   y   * BITSIZE_129) + zo;
	register int v3 = ((x+clod) + (y+clod) * BITSIZE_129) + zo;
	register int v4 = (  x   + (y+clod) * BITSIZE_129) + zo;

	register int v5 = (  x   + (y+clod) * BITSIZE_129) + zu;
	register int v6 = ((x+clod) + (y+clod) * BITSIZE_129) + zu;
	register int v7 = ((x+clod) +   y   * BITSIZE_129) + zu;
	register int v8 = (  x   +   y   * BITSIZE_129) + zu;

	if(visState & UP){
		//glNormal3f(0,0,1); // oben
		vertexGrid[v1].used = true; vertexGrid[v1].w ++; v_Index->push_back(v1);
		vertexGrid[v2].used = true; vertexGrid[v2].w ++; v_Index->push_back(v2);
		vertexGrid[v3].used = true; vertexGrid[v3].w ++; v_Index->push_back(v3);
		vertexGrid[v4].used = true; vertexGrid[v4].w ++; v_Index->push_back(v4);
	}
	
	if(visState & DOWN){
		//glNormal3f(0,0,-1); // unten
		vertexGrid[v5].used = true; vertexGrid[v5].w --; v_Index->push_back(v5);
		vertexGrid[v6].used = true; vertexGrid[v6].w --; v_Index->push_back(v6);
		vertexGrid[v7].used = true; vertexGrid[v7].w --; v_Index->push_back(v7);
		vertexGrid[v8].used = true; vertexGrid[v8].w --; v_Index->push_back(v8);
	}
	if(visState & LEFT){
		//glNormal3f(-1,0,0); // links
		vertexGrid[v8].used = true; vertexGrid[v8].u --; v_Index->push_back(v8);
		vertexGrid[v1].used = true; vertexGrid[v1].u --; v_Index->push_back(v1);
		vertexGrid[v4].used = true; vertexGrid[v4].u --; v_Index->push_back(v4);
		vertexGrid[v5].used = true; vertexGrid[v5].u --; v_Index->push_back(v5);
	}
	if(visState & RIGHT){
		//glNormal3f(1,0,0); // rechts
		vertexGrid[v6].used = true; vertexGrid[v6].u ++; v_Index->push_back(v6);
		vertexGrid[v3].used = true; vertexGrid[v3].u ++; v_Index->push_back(v3);
		vertexGrid[v2].used = true; vertexGrid[v2].u ++; v_Index->push_back(v2);
		vertexGrid[v7].used = true; vertexGrid[v7].u ++; v_Index->push_back(v7);
	}
	if(visState & FRONT){
		//glNormal3f(0,1,0); // vorne
		vertexGrid[v5].used = true; vertexGrid[v5].v ++; v_Index->push_back(v5);
		vertexGrid[v4].used = true; vertexGrid[v4].v ++; v_Index->push_back(v4);
		vertexGrid[v3].used = true; vertexGrid[v3].v ++; v_Index->push_back(v3);
		vertexGrid[v6].used = true; vertexGrid[v6].v ++; v_Index->push_back(v6);
	}
	if(visState & BACK){
		//glNormal3f(0,-1,0); // hinten
		vertexGrid[v7].used = true; vertexGrid[v7].v --; v_Index->push_back(v7);
		vertexGrid[v2].used = true; vertexGrid[v2].v --; v_Index->push_back(v2);
		vertexGrid[v1].used = true; vertexGrid[v1].v --; v_Index->push_back(v1);
		vertexGrid[v8].used = true; vertexGrid[v8].v --; v_Index->push_back(v8);
	}
}

void FoxelManager::packLightMap(MYVertex*** lightMap){
	
	for(unsigned char x = 1; x <= BITSIZE/LIGHT_MAP_SIZE+1; x++){

		for(unsigned char y = 1; y <= BITSIZE/LIGHT_MAP_SIZE+1; y++){
			for(unsigned char z = 1; z <= BITSIZE/LIGHT_MAP_SIZE+1; z++){
				if(lightMap[x][y][z].used){
					int x_count = 0;
					bool is_GI_Light = false;
					if(lightMap[ x ][y-1][ z ].used) x_count++;
					if(lightMap[ x ][y-1][z+1].used) x_count++;
					if(lightMap[ x ][y-1][z-1].used) x_count++;

					if(lightMap[ x ][y+1][ z ].used) x_count++;
					if(lightMap[ x ][y+1][z+1].used) x_count++;
					if(lightMap[ x ][y+1][z-1].used) x_count++;

					if(lightMap[ x ][ y ][z+1].used) x_count++;
					if(lightMap[ x ][ y ][z-1].used) x_count++;

					if(x_count > 4 && (y % 2 == 1) && (z % 2 == 1)){
						is_GI_Light = true;
					}


					int y_count = 0;
					if(lightMap[x-1][ y ][ z ].used) y_count++;
					if(lightMap[x-1][ y ][z+1].used) y_count++;
					if(lightMap[x-1][ y ][z-1].used) y_count++;

					if(lightMap[x+1][ y ][ z ].used) y_count++;
					if(lightMap[x+1][ y ][z+1].used) y_count++;
					if(lightMap[x+1][ y ][z-1].used) y_count++;

					if(lightMap[ x ][ y ][z+1].used) y_count++;
					if(lightMap[ x ][ y ][z-1].used) y_count++;

					if(y_count > 4  &&  (x % 2 == 1) && (z % 2 == 1)){
						is_GI_Light = true;

					}


					int z_count = 0;
					if(lightMap[ x ][y-1][ z ].used) z_count++;
					if(lightMap[x+1][y-1][ z ].used) z_count++;
					if(lightMap[x-1][y-1][ z ].used) z_count++;

					if(lightMap[ x ][y+1][ z ].used) z_count++;
					if(lightMap[x+1][y+1][ z ].used) z_count++;
					if(lightMap[x-1][y+1][ z ].used) z_count++;

					if(lightMap[x+1][ y ][ z ].used) z_count++;
					if(lightMap[x-1][ y ][ z ].used) z_count++;

					if(z_count > 4 &&  (x % 2 == 1) && (y % 2 == 1)){
						is_GI_Light = true;
					}

					if(is_GI_Light){
						gi_Lights.push_back(Light(Vec3(lightMap[x][y][z].x, lightMap[x][y][z].y,lightMap[x][y][z].z),
						                          Vec3(lightMap[x][y][z].u, lightMap[x][y][z].v, lightMap[x][y][z].w),
							                      Color()));
					}

				}

			}

		}

	}

	// Materials and lights
	directLights.clear();
	for(int i = 0; i < gi_Lights.size(); i++){
		gi_Lights[i].color = detectBrushColor(&gi_Lights[i].position);
		gi_Lights[i].position = gi_Lights[i].position + Vec3( myID[0],myID[1],myID[2]) * BITSIZE;
		gi_Lights[i].normal.normalize();
		if(gi_Lights[i].color.getAlpha() > 32){
			directLights.push_back(gi_Lights[i]);
		}
	}

	illuminateLightMap();

	// cleanup
	for(unsigned char x = 1; x <= BITSIZE/LIGHT_MAP_SIZE+1; x++){
		for(unsigned char y = 1; y <= BITSIZE/LIGHT_MAP_SIZE+1; y++){
			for(unsigned char z = 1; z <= BITSIZE/LIGHT_MAP_SIZE+1; z++){
				lightMap[x][y][z].used = false;
				lightMap[x][y][z].u = 0;
				lightMap[x][y][z].v = 0;
				lightMap[x][y][z].w = 0;
			}
		}
	}

	int i = 0;
	while(i < gi_Lights.size()){
		// is the light bright enough and is it AxisOriented?
		if(gi_Lights[i].color.getMaximum() < 128 || !gi_Lights[i].normal.isAxisOriented()){
			gi_Lights.erase(gi_Lights.begin()+i);
		}else{
			i++;
		}
	}
	countBounceLights();
	generateBounceLightArray();
}
/*
	===========================================
	Pack Vertices in an useable GLint Array
	and upload this Array to the Graphics Card
	===========================================
*/
void FoxelManager::packVertices(std::vector<GLuint>* v_Index, MYVertex* vertexGrid){
	anzVertex = 0;
	register int length = (int)v_Index->size();
	for(int i = 0; i < length; i++){
		if(vertexGrid[v_Index->at(i)].used == true){
			anzVertex++;
		}
	}

	anzPolygon = length/2;
	//vertexCount += anzVertex;
	//polyCount += anzPolygon;
	anzIndex = (unsigned int)v_Index->size();
	if(anzVertex > 0){
		delete[] vertices;
		delete[] colors;
		delete[] normals;
		delete[] indices;
		vertices = new GLubyte[anzVertex*3];
		colors = new GLubyte[anzVertex*4];
		normals = new GLbyte[anzVertex*3];
		indices = new GLuint[anzIndex];

		int vIndex = 0;
		int cIndex = 0;
		int nIndex = 0;
		for(int i = 0; i < length; i++){
			if(vertexGrid[v_Index->at(i)].used == true){
				vertexGrid[v_Index->at(i)].indexofset = v_Index->at(i) - nIndex;
				vertexGrid[v_Index->at(i)].used = false;

				vertices[vIndex]   = vertexGrid[v_Index->at(i)].x;
				vertices[vIndex+1] = vertexGrid[v_Index->at(i)].y;
				vertices[vIndex+2] = vertexGrid[v_Index->at(i)].z;

				normals[vIndex]   = vertexGrid[v_Index->at(i)].u;
				normals[vIndex+1] = vertexGrid[v_Index->at(i)].v;
				normals[vIndex+2] = vertexGrid[v_Index->at(i)].w;

				setVertexToBrushColor(&vertices[vIndex], &colors[cIndex], &normals[vIndex]);

				vertexGrid[v_Index->at(i)].u = (GLbyte) 0.0f;
				vertexGrid[v_Index->at(i)].v = (GLbyte) 0.0f;
				vertexGrid[v_Index->at(i)].w = (GLbyte) 0.0f;

				nIndex++;
				vIndex += 3;
				cIndex += 4;
			}
			indices[i] = v_Index->at(i) - vertexGrid[v_Index->at(i)].indexofset;
		}



		illuminateDirectly();
		
	}
	uploadQueue.push(this);
}

vector<Light*> FoxelManager::getSuroundingDirectlights(){
	register short range = 2;
	register vector<int> lightingChunk;
	lightingChunk.push_back(myID[0] - range);
	lightingChunk.push_back(myID[1] - range);
	lightingChunk.push_back(myID[2] - range);

	// get all lights
	register vector<Light*> lights;
	for(; lightingChunk[0] < myID[0] + range; lightingChunk[0]++){
		for(; lightingChunk[1] < myID[1] + range; lightingChunk[1]++){
			for(; lightingChunk[2] < myID[2] + range; lightingChunk[2]++){	
				if(idMap.find(lightingChunk) != idMap.end()){
					for(int i = 0; i < idMap[lightingChunk]->getDirectLights()->size();i++){
						lights.push_back(&idMap[lightingChunk]->getDirectLights()->at(i));
					}
				}
			}
			lightingChunk[2] = myID[2] - range;
		}
		lightingChunk[1] = myID[1] - range;
	}
	return lights;
}

void FoxelManager::illuminateDirectly(){
	

	register int cIndex = 0;
	register int vIndex = 0;
	register float brightnes;
	register float face_x_ray;
	register float light_x_ray;
	register float finalBrightnes;
	register vector<Light*> lights = getSuroundingDirectlights();
	register const short l_length = lights.size();

	register int length = anzVertex/3;
	for(int i = 0; i < length; i++){
		finalBrightnes = 0.0f;
		register Vec3 pos(vertices[vIndex] + (myID[0] * BITSIZE), vertices[vIndex+1] + (myID[1] * BITSIZE), vertices[vIndex+2] + (myID[2] * BITSIZE));
		register Vec3 nor(normals[vIndex], normals[vIndex+1], normals[vIndex+2]);
		nor.normalize();

		
		for(int j = 0; j < l_length; j++){

			register Vec3 ray = (lights[j]->position - pos);
			ray.normalize();
			face_x_ray = Vec3::dot(ray,nor);
			light_x_ray = Vec3::dot(lights[j]->normal,ray);
							
			if(light_x_ray < 0 && face_x_ray > 0 && !rayHit(&lights[j]->position,&pos)){
								
				brightnes = -light_x_ray * face_x_ray * lights[j]->color.getAlpha();
				brightnes /= 0.00035 * pow((lights[j]->position - pos).length(),2);
			
				// Todo		Material farbe
				finalBrightnes += brightnes;
								
			}
		}


		if(finalBrightnes < 0) finalBrightnes = 0;
		else if(finalBrightnes > 255) finalBrightnes = 255;

		
		//cout << finalBrightnes << endl;

		colors[cIndex]	 *= finalBrightnes/255.0f;
		colors[cIndex+1] *= finalBrightnes/255.0f;
		colors[cIndex+2] *= finalBrightnes/255.0f;

		cIndex +=4;
		vIndex +=3;
	}

}

void FoxelManager::illuminateLightMap(){
	register vector<Light*> lights = getSuroundingDirectlights();

	int cIndex = 0;
	int vIndex = 0;
	
	float brightnes = 0.0f;
	const int length = gi_Lights.size();
	for(int i = 0; i < length; i++){
		float finalBrightnes = 0.0f;				
		for(int j = 0; j < lights.size(); j++){

			Vec3 ray = (lights[j]->position - gi_Lights[i].position);
			ray.normalize();
			float face = Vec3::dot(ray,gi_Lights[i].normal);
							
			if((Vec3::dot(lights[j]->normal,ray) < 0) && face > 0 && !rayHit(&lights[j]->position,&gi_Lights[i].position)){
								
				brightnes = -Vec3::dot(lights[j]->normal,ray);
				brightnes *= face;
				brightnes /= 0.00035 / (lights[j]->color.getAlpha()) * pow((lights[j]->position - gi_Lights[i].position).length(),2);
			
				// Todo		Material farbe
				finalBrightnes += brightnes;
								
				//energys[i]  += brightnes;
			}
		}

	
				

		if(finalBrightnes < 0) finalBrightnes = 0;
		if(finalBrightnes > 255) finalBrightnes = 255;

		
		//cout << finalBrightnes << endl;

		gi_Lights[i].color.setRed  (gi_Lights[i].color.getRed()   * finalBrightnes/255.0f);
		gi_Lights[i].color.setGreen(gi_Lights[i].color.getGreen() * finalBrightnes/255.0f);
		gi_Lights[i].color.setBlue (gi_Lights[i].color.getBlue()  * finalBrightnes/255.0f);

		cIndex +=4;
		vIndex +=3;
	}
}

void FoxelManager::uploadToGPU(){

		// Creating Buffer and uploading data
	if(anzVertex > 0){
		glBindVertexArray(vao);

		// Vertex
		glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte)*anzVertex*3, vertices, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_UNSIGNED_BYTE,GL_FALSE,0,0);
		// Color
		glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte)*anzVertex*4, colors, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,4,GL_UNSIGNED_BYTE,GL_FALSE,0,0);
		// Normals
		glBindBuffer(GL_ARRAY_BUFFER, vbos[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLbyte)*anzVertex*3, normals, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2,3,GL_BYTE,GL_FALSE,0,0);
		// Indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbos[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,anzIndex*sizeof(GL_UNSIGNED_INT),indices,GL_DYNAMIC_DRAW);

		glBindVertexArray(0);

		readyToDraw = true;
	}

	//cleanup


	constAnzIndex = anzIndex;
	steady = true;
}

void FoxelManager::update(){
	
	int uploadsize = 0;
	while(uploadQueue.size() > 0 && uploadsize < 24){
		uploadQueue.front()->uploadToGPU();
		uploadsize += 8/uploadQueue.front()->lod;
		uploadQueue.pop();
	}
	

	// check what chunks need to setup
	for(int i = 0; i < chunks.size(); i++){
		if(chunks[i]->needSetup && chunks[i]->steady){
			chunks[i]->steady = false;
			setupQueue.push(chunks[i]);
		}
	}
	
}


/*
	==================================================================
	The public render method to setup parameters and render all chunks
	==================================================================
*/
void FoxelManager::render(){

	PM::useProg(PROGRAM_FOXEL);
	for(unsigned int i = 0; i < chunks.size(); i++){
		if(chunks.at(i)->readyToDraw){
			chunks.at(i)->drawChunk();
		}
		
	}
	glBindVertexArray(NULL);
	glUniform3f(PM::getUnifLoc(PROGRAM_FOXEL, "chunk_Position"),0.0f,0.0f,0.0f);
	PM::useProg(PROGRAM_NULL);
}
/*
	====================================
	Draws a single chunk at his Position
	====================================
 */
void FoxelManager::drawChunk(){

	if(Config::isDebug()){
		
		glBegin(GL_LINES);
		for(int i = 0; i < gi_Lights.size(); i++){
			glVertexAttrib4f(1,0,128,255,1);
			glVertex3f(gi_Lights[i].position.x,gi_Lights[i].position.y,gi_Lights[i].position.z);
			glVertex3f(gi_Lights[i].position.x + gi_Lights[i].normal.x*4, gi_Lights[i].position.y + gi_Lights[i].normal.y*4, gi_Lights[i].position.z + gi_Lights[i].normal.z*4);
		}
		glEnd();

		glBegin(GL_LINES);
		for(int i = 0; i < directLights.size(); i++){
			glVertexAttrib4f(1,255,64,0,1);
			glVertex3f(directLights[i].position.x,directLights[i].position.y,directLights[i].position.z);
			glVertex3f(directLights[i].position.x + directLights[i].normal.x*4, directLights[i].position.y + directLights[i].normal.y*4, directLights[i].position.z + directLights[i].normal.z*4);
		}
		glEnd();

		PM::useProg(PROGRAM_FOXEL);
	}


	Screen::ViewMatrix.translate((float)position.x,(float)position.y,(float)position.z);
	glUniformMatrix4fv(PM::getUnifLoc(PROGRAM_FOXEL, "viewMatrix"), 1, GL_FALSE, Screen::ViewMatrix.getMatrix());
	glUniform3f(PM::getUnifLoc(PROGRAM_FOXEL, "chunk_Position"),(float)position.x,(float)position.y,(float)position.z);

	// draw Foxel	
	glBindVertexArray(vao);
	glDrawElements(GL_QUADS,constAnzIndex,GL_UNSIGNED_INT,(void*)0);
	
	// draw a debugBox
	if(Config::isDebug() && false){
		glColor3f(1.0f,1.0f,1.0f);
		glVertexPointer(3,GL_FLOAT,0,debugChunkBoxV);
		glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, debugChunkBoxI);
	}

	Screen::ViewMatrix.translate((float)-position.x,(float)-position.y,(float)-position.z);
	glUniformMatrix4fv(PM::getUnifLoc(PROGRAM_FOXEL, "viewMatrix"), 1, GL_FALSE, Screen::ViewMatrix.getMatrix());
}

void FoxelManager::settingFoxel(Event::setFoxel* setterEvent){
	std::vector<int> chunkID = tracingChunkID(*setterEvent->getPosition());

	// tracing Foxel position in chunk from event position
	int x = (int)setterEvent->getPosition()->x % (BITSIZE);
	int y = (int)setterEvent->getPosition()->y % (BITSIZE);
	int z = (int)setterEvent->getPosition()->z % (BITSIZE);

	if(x <= 0 && chunkID[0] < 0) x += BITSIZE-1;
	if(y <= 0 && chunkID[1] < 0) y += BITSIZE-1;
	if(z <= 0 && chunkID[2] < 0) z += BITSIZE-1;

	if(idMap.find(chunkID) != idMap.end()){			// chunk exist
		idMap[chunkID]->bitGrid->set(x,y,z,true);
		idMap[chunkID]->needSetup = true;
	}else{											// create a chunk
		new FoxelManager(chunkID[0],chunkID[1],chunkID[2]);
		idMap[chunkID]->bitGrid->set(x,y,z,true);
		idMap[chunkID]->needSetup = true;
		std::cout << "Chunks: " << chunks.size() << "   Total Vertices:  " << vertexCount << std::endl;
	}
}

// veraltet kann später entfernt werden
void FoxelManager::makeBlock(Vec3 start, Vec3 end, int id){
	std::vector<std::vector<int>> chunkIDs;
	std::vector<int> cChunkID;
	bool boolean;
	if(id > 0) boolean = true;
	else boolean = false;

	int fx,fy,fz;
	for(int x = (int)start.x; x < (int)end.x; x++){
		for(int y = (int)start.y; y < (int)end.y; y++){
			for(int z = (int)start.z; z < (int)end.z; z++){

				cChunkID = tracingChunkID(Vec3((float)x,(float)y,(float)z));	
				// chunk exist? no? create new ...
				if(idMap.find(cChunkID) == idMap.end()){
					new FoxelManager(cChunkID[0],cChunkID[1],cChunkID[2]);
				}
				if(std::find(chunkIDs.begin(), chunkIDs.end(), cChunkID) == chunkIDs.end()) {
					chunkIDs.push_back(cChunkID);
				}

				// tracing Foxel position in chunk
				fx = x % (BITSIZE);
				fy = y % (BITSIZE);
				fz = z % (BITSIZE);

				if(x < 0 && cChunkID[0] < 0) fx += BITSIZE;
				if(y < 0 && cChunkID[1] < 0) fy += BITSIZE;
				if(z < 0 && cChunkID[2] < 0) fz += BITSIZE;

				if(fx >=128) std::cout << "warning";
				if(fy >=128) std::cout << "warning";
				if(fz >=128) std::cout << "warning";
				idMap[cChunkID]->bitGrid->set(fx,fy,fz,boolean);
			}
		}
	}

	// update Foxels
	for(int i = 0; i < chunkIDs.size(); i++){
		idMap[chunkIDs[i]]->needSetup = true;
	}
}

std::vector<int> FoxelManager::tracingChunkID(Vec3 point){
	std::vector<int> chunkID;
	int idX, idY, idZ;

	idX = (int)point.x / BITSIZE; 
	idY = (int)point.y / BITSIZE;
	idZ = (int)point.z / BITSIZE;
	
	if((int)point.x < 0) idX--;
	if((int)point.y < 0) idY--;
	if((int)point.z < 0) idZ--;

	chunkID.push_back(idX);
	chunkID.push_back(idY);
	chunkID.push_back(idZ);

	return chunkID;
}

Vec3 FoxelManager::tracingFoxelPositionInChunk(Vec3 point, std::vector<int> chunkID){
		Vec3 position;
		position.x = (float)((int)point.x % (BITSIZE));
		position.y = (float)((int)point.y % (BITSIZE));
		position.z = (float)((int)point.z % (BITSIZE));

		if((int)point.x <= 0 && chunkID[0] < 0) position.x += BITSIZE;
		if((int)point.y <= 0 && chunkID[1] < 0) position.y += BITSIZE;
		if((int)point.z <= 0 && chunkID[2] < 0) position.z += BITSIZE;

		return position;
}

void FoxelManager::makeLine(Vec3 start, Vec3 direction, int id){
	Vec3 end = start + direction;
	std::cout << start.x;
	std::vector<std::vector<int>> chunkIDs;
	direction.normalize();

	while(start != end){
		std::vector<int> cChunkID = tracingChunkID(start);

		// this is just for debug
		if(std::find(chunkIDs.begin(), chunkIDs.end(), cChunkID) == chunkIDs.end()) {
			chunkIDs.push_back(cChunkID);
		}

		if(idMap.find(cChunkID) == idMap.end()){
			new FoxelManager(cChunkID[0],cChunkID[1],cChunkID[2]);

		}
		Vec3 fpos = tracingFoxelPositionInChunk(start,cChunkID);
		idMap[cChunkID]->bitGrid->set((int)fpos.x, (int)fpos.y, (int)fpos.z, true);
		start += direction;
	}

	// TODO JUST DEBUG
	// update Foxels
	for(int i = 0; i < chunkIDs.size(); i++){
		idMap[chunkIDs[i]]->needSetup = true;
	}
}

bool FoxelManager::detectBulletHit(Vec3* position, Vec3* direction){
	std::vector<std::vector<int>> chunkIDs;
	Vec3 end = *position + *direction;
	direction->normalize();
	bool hit = false;

	while(*position != end && !hit){
		std::vector<int> cChunkID = tracingChunkID(*position);

		if(idMap.find(cChunkID) != idMap.end()){	// chunk exist?
			Vec3 fpos = tracingFoxelPositionInChunk(*position,cChunkID);
			if(idMap[cChunkID]->bitGrid->get((int)fpos.x, (int)fpos.y, (int)fpos.z) == true){ // is there a Foxel?
				// hit
				FoxelSetter fs;
				fs.x = (char)fpos.x;
				fs.y = (char)fpos.y;
				fs.z = (char)fpos.z;
				fs.id = 0;
				idMap[cChunkID]->setterBuffer.push(fs);
				if(std::find(chunkIDs.begin(), chunkIDs.end(), cChunkID) == chunkIDs.end()) {
					chunkIDs.push_back(cChunkID);
				}
				hit = true;
				break;
			}
			
		}

		*position += *direction;
	}

	for(int i = 0; i < chunkIDs.size(); i++){
		idMap[chunkIDs[i]]->needSetup = true;
	}

	if(hit){
		return true;
	}else{
		return false;
	}
}

void FoxelManager::addBrush(ChunkBrush brush){
	vector<int> cid;
	cid.push_back(brush.idX);
	cid.push_back(brush.idY);
	cid.push_back(brush.idZ);

	// chunk exist? no? create new ...
	if(idMap.find(cid) == idMap.end()){
		new FoxelManager(cid[0],cid[1],cid[2]);
	}

	idMap[cid]->brushes.push_back(new Brush(brush));
	idMap[cid]->buildBrush(idMap[cid]->brushes.back());
}

void FoxelManager::buildBrush(Brush* brush){
	bool b;
	if(brush->id == 0) b = false;
	else b = true;
	for(int x = brush->sX; x <= brush->eX; x++){
		for(int y = brush->sY; y <= brush->eY; y++){
			for(int z = brush->sZ; z <= brush->eZ; z++){
				bitGrid->set(x,y,z,b);
			}
		}
	}
	needSetup = true;
}

void FoxelManager::loadAllChunks(){
	for(int x = 0; x < chunks.size(); x++){
		for(int i = 0; i < chunks[x]->brushes.size(); i++){
			chunks[x]->buildBrush(chunks[x]->brushes[i]);
		}
	}
}

void FoxelManager::clearSetterBuffer(){
	while(setterBuffer.size() != 0){
		FoxelSetter fs = setterBuffer.front();
		setterBuffer.pop();
		if(fs.id > 0) bitGrid->set(fs.x,fs.y,fs.z,true);
		else bitGrid->set(fs.x,fs.y,fs.z,false);
	}
}

void FoxelManager::setLodCenter(Vec3d center){
	
	vector<int> lodCenter = tracingChunkID(center);

	for(int i = 0; i < chunks.size(); i++){
		char nlod;
		float entf = Vec3((float)chunks[i]->myID[0] - (float)lodCenter[0], (float)chunks[i]->myID[1] - (float)lodCenter[1], (float)chunks[i]->myID[2] - (float)lodCenter[2]).length();
		entf = log(entf * 1.75f);
		if(entf < 0) entf = 0;
		//cout << entf << "\t" << pow(2.0f,entf) << endl;
		nlod = (char)pow(2.0f,(int)entf);
		if(nlod > 8) nlod = 8;
		chunks[i]->setLevelOfDetail(nlod);
	}


}

void FoxelManager::setGlobalLod(unsigned char nlod){
	globalLevelOfDetail = nlod;

}

void FoxelManager::setLevelOfDetail(unsigned char nlod){
	unsigned char clod = lod;
	if(steady && (lod != nlod || globalLevelOfDetail > lod)){
			clod = nlod;
		if(globalLevelOfDetail > clod || globalLevelOfDetail > clod ){
			clod = globalLevelOfDetail;
		}
		if(clod != lod){
			lod = clod;
			needSetup = true;
		}
	}
}

long FoxelManager::getPolyCount(){
	long polys = 0;
	for(int i = 0; i < chunks.size(); i++){
		polys += chunks[i]->anzPolygon;
	}
	
	return polys;
}

// TODO in eigene Klasse verlegen
bool BrushIntersection(Brush* B1, Brush* B2){
	return 
	  ((B1->sX < B2->eX) && (B1->eX > B2->sX)
	&& (B1->sY < B2->eY) && (B1->eY > B2->sY)
	&& (B1->sZ < B2->eZ) && (B1->eZ > B2->sZ));
}

bool BrushVertexIntersection(Brush* brush, GLubyte* vertex){
	return
		brush->sX <= vertex[0] && brush->eX+1 >= vertex[0] &&
		brush->sY <= vertex[1] && brush->eY+1 >= vertex[1] &&
		brush->sZ <= vertex[2] && brush->eZ+1 >= vertex[2];
}

bool BrushVertexIntersection(Brush* brush, Vec3* position){
	return
		brush->sX <= position->x && brush->eX+1 >= position->x &&
		brush->sY <= position->y && brush->eY+1 >= position->y &&
		brush->sZ <= position->z && brush->eZ+1 >= position->z;
}

bool BrushEdgeIntersection(Brush* brush, GLubyte* vertex){
	return
	brush->sX == vertex[0] || brush->eX+1 == vertex[0] ||
	brush->sY == vertex[1] || brush->eY+1 == vertex[1] ||
	brush->sZ == vertex[2] || brush->eZ+1 == vertex[2];
}

bool OutOfChunk(Vec3* point){
	return ((char)point->x < 0 || (char)point->y < 0 || (char)point->z < 0
	|| (char)point->x > 127 || (char)point->y > 127 || (char)point->z > 127 );
}

bool FoxelManager::rayHit(Vec3* start, Vec3* end){
	Vec3 Hit;
	Vec3 start_local = *start - Vec3(myID[0] * BITSIZE, myID[1] * BITSIZE, myID[2] * BITSIZE);
	Vec3 end_local = *start - Vec3(myID[0] * BITSIZE, myID[1] * BITSIZE, myID[2] * BITSIZE);

	for(int i = brushes.size()-1; i >= 0; i--){
		if(brushes.at(i)->id != 0){	
			if(CollisionDetector::LineBox(Vec3(brushes.at(i)->sX + (myID[0] * BITSIZE), brushes.at(i)->sY + (myID[1] * BITSIZE), brushes.at(i)->sZ + (myID[2] * BITSIZE)),
			            Vec3(brushes.at(i)->eX + (myID[0] * BITSIZE), brushes.at(i)->eY + (myID[1] * BITSIZE), brushes.at(i)->eZ + (myID[2] * BITSIZE)),
						*start, *end, Hit)){
				// Brush hit
				Vec3 rayNormal = (*start - *end);
				rayNormal.normalize();

				// Convert Hit to chunk coords
				Hit.x -= (myID[0] * BITSIZE);
				Hit.y -= (myID[1] * BITSIZE);
				Hit.z -= (myID[2] * BITSIZE);

				while((Hit != end_local) && !OutOfChunk(&Hit)){
					
					if(bitGrid->get((int)Hit.x , (int)Hit.y, (int)Hit.z)){
						return true;
					}
					Hit += rayNormal;
				}
			}
		}
	}
	return false;
}

void FoxelManager::setVertexToBrushColor(GLubyte* vertex, GLubyte* color, GLbyte* normal){
	register short r,g,b,e,hits;
	r = g = b = e = hits = 0;
	for(int i = brushes.size()-1; i >= 0; i--){
		if(brushes.at(i)->id != 0){
			if(BrushVertexIntersection(brushes.at(i),vertex)){
				hits++;
				r += brushes.at(i)->cR;
				g += brushes.at(i)->cG;
				b += brushes.at(i)->cB;
				e += brushes.at(i)->em;
				if(brushes.at(i)->em > 100){
					// its a light
					break;
				}

			}
		}else if(hits > 1){
			break;
		}
	}

	color[0] = (unsigned char)(r/hits);
	color[1] = (unsigned char)(g/hits);
	color[2] = (unsigned char)(b/hits);
	color[3] = (unsigned char)(e/hits);
}

Color FoxelManager::detectBrushColor(Vec3* position){
	Color color;
	for(int i = brushes.size()-1; i >= 0; i--){
		if(brushes.at(i)->id != 0 && BrushVertexIntersection(brushes.at(i),position)){
			color.setRed(brushes.at(i)->cR);
			color.setGreen(brushes.at(i)->cG);
			color.setBlue(brushes.at(i)->cB);
			color.setAlpha(brushes.at(i)->em);
			break;
		}
	}
	return color;
}

void FoxelManager::generateBounceLightArray(){
	const int lightCount = getNumberOfBounceLights();
	const int chunkCount = chunks.size();

	delete[] BounceLights;
	BounceLights = new float[lightCount*9];
	int k = 0;
	for(int f = 0; f < chunkCount; f++){
		for(int i = 0; i < chunks[f]->gi_Lights.size(); i++){
			BounceLights[k+0] = chunks[f]->gi_Lights[i].position.x;
			BounceLights[k+1] = chunks[f]->gi_Lights[i].position.y;
			BounceLights[k+2] = chunks[f]->gi_Lights[i].position.z;

			BounceLights[k+3] = chunks[f]->gi_Lights[i].normal.x;
			BounceLights[k+4] = chunks[f]->gi_Lights[i].normal.y;
			BounceLights[k+5] = chunks[f]->gi_Lights[i].normal.z;

			BounceLights[k+6] = chunks[f]->gi_Lights[i].color.getRed();
			BounceLights[k+7] = chunks[f]->gi_Lights[i].color.getGreen();
			BounceLights[k+8] = chunks[f]->gi_Lights[i].color.getBlue();
			//lightArray[k+9] = chunks[f]->gi_Lights[i].color.getAlpha();
			k += 9;
		}
	}
}

float* FoxelManager::getBounceLightArray(){
	return BounceLights;
}

std::vector<Light>* FoxelManager::getDirectLights(){
	return &directLights;
}

std::vector<FoxelManager*>* FoxelManager::getChunkList(){
	return &chunks;
}

long FoxelManager::getVertexCount(){
	return vertexCount;
}

int FoxelManager::getNumberOfCurrentChunkUpdates(){
	return (int)setupQueue.size();
}

int FoxelManager::getNumberOfPendingGpuUploads(){
	return (int)uploadQueue.size();
}

int FoxelManager::getNumberOfDirectLights(){
	int lights = 0;
	for(int i = 0; i < chunks.size(); i++){
		lights += chunks[i]->directLights.size();
	}
	return lights;
}

void FoxelManager::countBounceLights(){
	int lights = 0;
	for(int i = 0; i < chunks.size(); i++){
		lights += chunks[i]->gi_Lights.size();
	}
	NumberOfBounceLights = lights;
}

int FoxelManager::getNumberOfBounceLights(){
	return NumberOfBounceLights;
}