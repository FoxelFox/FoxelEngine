#include <iostream>
#include "FoxelManager.h"

FoxelManager::FoxelManager(void) : DrawableGameComponent(){
	chunks.push_back(this);
	myID.push_back(0);
	myID.push_back(0);
	myID.push_back(0);

	renderMode = POLYGON_MODE;
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
	position.x = (float) x * BITSIZE;
	position.y = (float) y * BITSIZE;
	position.z = (float) z * BITSIZE;

	myID.push_back(x);
	myID.push_back(y);
	myID.push_back(z);

	initialise();
}

FoxelManager::~FoxelManager(){

}

void FoxelManager::deleteAll(){
	for(int i = 0; i < (int)chunks.size(); i++){
		delete chunks[i];
	}
	chunks.clear();
	idMap.clear();
}

std::vector<int> FoxelManager::genNewID(int x, int y, int z){
	std::vector<int> newID;
	newID.push_back(x);
	newID.push_back(y);
	newID.push_back(z);
	return newID;
}

void FoxelManager::initialise(){
	lod = 1;
	foxel = NULL;
	anzFoxel = 0;
	anzVertex = 0;
	vertices = NULL;
	idMap[myID] = this;

	myNeighborUp.push_back   (myID[0]  ); myNeighborUp.push_back   (myID[1]  );	myNeighborUp.push_back	 (myID[2]+1);
	myNeighborDown.push_back (myID[0]  ); myNeighborDown.push_back (myID[1]  ); myNeighborDown.push_back (myID[2]-1);
	myNeighborLeft.push_back (myID[0]-1); myNeighborLeft.push_back (myID[1]  ); myNeighborLeft.push_back (myID[2]  );
	myNeighborRight.push_back(myID[0]+1); myNeighborRight.push_back(myID[1]  ); myNeighborRight.push_back(myID[2]  );
	myNeighborFront.push_back(myID[0]  ); myNeighborFront.push_back(myID[1]+1); myNeighborFront.push_back(myID[2]  );
	myNeighborBack.push_back (myID[0]  ); myNeighborBack.push_back (myID[1]-1); myNeighborBack.push_back (myID[2]  );

	for(int x = 0; x < BITSIZE; x++){
		for(int y = 0; y < BITSIZE; y++){
			for(int z = 0; z < BITSIZE; z++){
				bitGrid[x][y][z] = false;
			}
		}
	}
	setupFoxels();
}
/*
	==================================================
	Generates the the mesh only from the visable sides
	of one Foxel and pack it to one GLint Vertex Array
	that will be transfared to the GPU memory.
	==================================================
*/
void FoxelManager::setupFoxels(){
	delete[] foxel;
	char visState = 0;
	std::vector<Foxel> v_Foxel;
	std::vector<GLint> v_Vertex;
	v_Foxel.reserve ((unsigned int)(anzFoxel  * 1.2));
	v_Vertex.reserve((unsigned int)(anzVertex * 1.2));

	for(short x = 0; x < BITSIZE; x++){
		for(short y = 0; y < BITSIZE; y++){
			for(short z = 0; z < BITSIZE; z++){
				if(bitGrid[x][y][z] == true){

					if(z == BITSIZE-1){
						if(idMap.find(myNeighborUp) != idMap.end()){
							if(idMap[myNeighborUp]->bitGrid[x][y][0] == false){
								visState |= UP;
							}
						}else{ // No Chunk TopSide
							visState |= UP;
						}
					}else if(bitGrid[ x ][ y ][z+1] == false){ visState |= UP	;}

					if(z == 0){
						if(idMap.find(myNeighborDown) != idMap.end()){
							if(idMap[myNeighborDown]->bitGrid[x][y][BITSIZE-1] == false){
								visState |= DOWN;
							}
						}else{ // No Chunk DownSide
							visState |= DOWN;
						}
					}else if(bitGrid[ x ][ y ][z-1] == false){ visState |= DOWN ;}

					if(x == 0){
						if(idMap.find(myNeighborLeft) != idMap.end()){
							if(idMap[myNeighborLeft]->bitGrid[BITSIZE-1][y][z] == false){
								visState |= LEFT ;
							}
						}else{ // No Chunk LeftSide
							visState |= LEFT;
						}
					}else if(bitGrid[x-1][ y ][ z ] == false){ visState |= LEFT ;}

					if(x == BITSIZE-1){
						if(idMap.find(myNeighborRight) != idMap.end()){
							if(idMap[myNeighborRight]->bitGrid[0][y][z] == false){
								visState |= RIGHT;
							}
						}else{ // No Chunk LeftSide
							visState |= RIGHT;
						}
					}else if(bitGrid[x+1][ y ][ z ] == false){ visState |= RIGHT;}

					if(y == BITSIZE-1){
						if(idMap.find(myNeighborFront) != idMap.end()){
							if(idMap[myNeighborFront]->bitGrid[x][0][z] == false){
								visState |= FRONT;
							}
						}else{ // No Chunk FrontSide
							visState |= FRONT;
						}
					}else if(bitGrid[ x ][y+1][ z ] == false){ visState |= FRONT;}

					if(y == 0){
						if(idMap.find(myNeighborBack) != idMap.end()){
							if(idMap[myNeighborBack]->bitGrid[x][BITSIZE-1][z] == false){
								visState |= BACK;
							}
						}else{ // No Chunk BackSide
							visState |= BACK;
						}
					}else if(bitGrid[ x ][y-1][ z ] == false){ visState |= BACK ;}

					if(visState > 0){	// Foxel is visable
						v_Foxel.push_back(Foxel(1,visState));
						if(renderMode == POINT_MODE){
							addPointVertices(x,y,z,visState,&v_Vertex);
						}else{
							addPolygonVertices(x,y,z,visState,&v_Vertex);
						}
						visState = 0;
					}
				}
			}
		}
	}
	packVertices(&v_Vertex);
}
/*
	===============================================
	Adding vertices to the vertex colection. At the
	moment unused and better cast would be to float
	===============================================
*/
void FoxelManager::addPointVertices(GLint x, GLint y, GLint z, char visState, std::vector<GLint>* v_Vertex){

	GLint s = (int)0.5f*lod;	// have to be float !
	GLint d = (int)1.0f*lod;	// just to disable warnings

	if(visState & UP){
		//glNormal3f(0,0,1);
		v_Vertex->push_back(x+s);
		v_Vertex->push_back(y+s);
		v_Vertex->push_back(z+d);
	}
	if(visState & DOWN){
		//glNormal3f(0,0,-1);
		v_Vertex->push_back(x+s);
		v_Vertex->push_back(y+s);
		v_Vertex->push_back( z );
	}
	if(visState & LEFT){
		//glNormal3f(-1,0,0);
		v_Vertex->push_back( x );
		v_Vertex->push_back(y+s);
		v_Vertex->push_back(z+s);
	}
	if(visState & RIGHT){
		//glNormal3f(1,0,0);
		v_Vertex->push_back(x+d);
		v_Vertex->push_back(y+s);
		v_Vertex->push_back(z+s);
	}
	if(visState & FRONT){
		//glNormal3f(0,1,0);
		v_Vertex->push_back(x+s);
		v_Vertex->push_back(y+d);
		v_Vertex->push_back(z+s);
	}
	if(visState & BACK){
		//glNormal3f(0,-1,0);
		v_Vertex->push_back(x+s);
		v_Vertex->push_back( y );
		v_Vertex->push_back(z+s);
	}
}
/*
	===========================================
	Adding 4 or more vertices to the vertex
	colection as Quads
	===========================================
*/
void FoxelManager::addPolygonVertices(GLint x, GLint y, GLint z, char visState, std::vector<GLint>* v_Vertex){
	
	GLint d = 1*lod;

	if(visState & 1){
		//glNormal3f(0,0,1); // oben
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+0); v_Vertex->push_back(z+d); //v1
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+0); v_Vertex->push_back(z+d); //v2
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v3
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v4
	}
	if(visState & 2){
		//glNormal3f(0,0,-1); // unten
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v5
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v6
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+0); v_Vertex->push_back(z+0); //v7
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+0); v_Vertex->push_back(z+0); //v8
	}
	if(visState & 4){
		//glNormal3f(-1,0,0); // links
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+0); v_Vertex->push_back(z+0); //v8
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+0); v_Vertex->push_back(z+d); //v1
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v4
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v5
	}
	if(visState & 8){
		//glNormal3f(1,0,0); // rechts
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v6
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v3
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+0); v_Vertex->push_back(z+d); //v2
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+0); v_Vertex->push_back(z+0); //v7
	}
	if(visState & 16){
		//glNormal3f(0,1,0); // vorne
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v8
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v6
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v7
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v8
	}
	if(visState & 32){
		//glNormal3f(0,-1,0); // hinten
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+0); v_Vertex->push_back(z+0); //v5
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+0); v_Vertex->push_back(z+d); //v6
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+0); v_Vertex->push_back(z+d); //v7
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+0); v_Vertex->push_back(z+0); //v8
	}
}
/*
	===========================================
	Pack Vertices in an useable GLint Array
	and upload this Array to the Graphics Card
	===========================================
*/
void FoxelManager::packVertices(std::vector<GLint> *v_Vertex){
	if(vertexCount > 0){
		glDeleteBuffers(1,&vbo);
		glDeleteVertexArrays(1,&vbo);
	}
	delete[] vertices;
	vertexCount -= (long) anzVertex;
	polyCount -= (long) anzPolygon;
	anzVertex = (unsigned int) v_Vertex->size() /3;
	anzPolygon = anzVertex / 3;
	vertexCount += anzVertex;
	vertices = new GLint[v_Vertex->size()];
	for(unsigned int i = 0; i < v_Vertex->size(); i++){
		vertices[i] = v_Vertex->at(i);
	}
	// Creating Buffer and uploading data
	if(anzVertex > 0){
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1,&vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLint)*v_Vertex->size(), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0,3,GL_INT,GL_FALSE,0,0);
		glEnableVertexAttribArray(0);

	}
}
/*
	==================================================================
	The public render method to setup parameters and render all chunks
	==================================================================
*/
void FoxelManager::render(){
	//glEnable(GL_POINT_SMOOTH);
	//GLfloat pointParameter[3] = {0.0f,0.00001f,0.000001f};
	//glPointParameterf(GL_POINT_SIZE_MIN, 0.0f);
	//glPointParameterf(GL_POINT_SIZE_MAX, 2048.0f);
	//glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION,pointParameter);

	
	for(unsigned int i = 0; i < chunks.size(); i++){
		chunks.at(i)->drawChunk();
	}
	
}
/*
	====================================
	Draws a single chunk at his Position
	====================================
 */
void FoxelManager::drawChunk(){
	glTranslatef((float)position.x,(float)position.y,(float)position.z);

	if(anzVertex > 0){
		// draw Foxel
		glColor4f(1.0f, 0.125f, 0.005f, 0.5f);
		glBindVertexArray(vao);
		glVertexAttrib3f((GLuint)1, 0.0, 0.0, 1.0);
		glDrawArrays(GL_QUADS, 0, anzVertex);
		glBindVertexArray(0);
		
		
	}
	// draw a debugBox
	if(debug){
		glColor3f(1.0f,1.0f,1.0f);
		glVertexPointer(3,GL_FLOAT,0,debugChunkBoxV);
		glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, debugChunkBoxI);
	}
	glTranslatef((float)-position.x,(float)-position.y,(float)-position.z);
}

void FoxelManager::settingFoxel(Event::setFoxel* setterEvent){
	std::vector<int> chunkID;
	
	// tracing chunk id from event position
	float idFX, idFY, idFZ;
	idFX = (float) setterEvent->getPosition()->x / BITSIZE;
	idFY = (float) setterEvent->getPosition()->y / BITSIZE;
	idFZ = (float) setterEvent->getPosition()->z / BITSIZE;

	if(idFX > 0) chunkID.push_back((int)idFX);
	else chunkID.push_back((int)idFX-1);
	
	if(idFY > 0) chunkID.push_back((int)idFY);
	else chunkID.push_back((int)idFY-1);

	if(idFZ > 0) chunkID.push_back((int)idFZ);
	else chunkID.push_back((int)idFZ-1);

	// tracing Foxel position in chunk from event position
	int x = (int)setterEvent->getPosition()->x % (BITSIZE);
	int y = (int)setterEvent->getPosition()->y % (BITSIZE);
	int z = (int)setterEvent->getPosition()->z % (BITSIZE);

	if(x <= 0 && idFX < 0) x += BITSIZE-1;
	if(y <= 0 && idFY < 0) y += BITSIZE-1;
	if(z <= 0 && idFZ < 0) z += BITSIZE-1;

	if(idMap.find(chunkID) != idMap.end()){			// chunk exist
		idMap[chunkID]->bitGrid[x][y][z] = true;
		idMap[chunkID]->setupFoxels();
	}else{											// create a chunk
		chunks.push_back(new FoxelManager(chunkID[0],chunkID[1],chunkID[2]));
		idMap[chunkID]->bitGrid[x][y][z] = true;
		idMap[chunkID]->setupFoxels();
		std::cout << "Chunks: " << chunks.size() << "   Total Vertices:  " << vertexCount << std::endl;
	}
}

void FoxelManager::switchDebug(){
	if(debug) debug = false;
	else debug = true;
}

long FoxelManager::getPolyCount(){
	return polyCount;
}

long FoxelManager::getVertexCount(){
	return vertexCount;
}


