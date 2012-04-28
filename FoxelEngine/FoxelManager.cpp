#include "FoxelManager.h"

using namespace GLSL;

FoxelManager::FoxelManager(void){
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

	// first chunk?
	if(chunks.size() == 0){

	}
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2,vbos); // vertices and Normals

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

void FoxelManager::initialise(){
	lod = 1;
	foxel = NULL;
	anzFoxel = 0;
	anzVertex = 0;
	vertices = NULL;
	normals = NULL;
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
	//setupFoxels();
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
	std::vector<GLfloat> v_Vertex;
	std::vector<GLfloat> v_Normal;
	v_Foxel.reserve ((unsigned int)(anzFoxel  * 1.2));
	v_Vertex.reserve((unsigned int)(anzVertex * 1.2));
	v_Normal.reserve((unsigned int)(anzVertex * 1.2));
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
							addPointVertices((GLfloat)x,(GLfloat)y,(GLfloat)z,visState,&v_Vertex,&v_Normal);
						}else{
							addPolygonVertices((GLfloat)x,(GLfloat)y,(GLfloat)z,visState,&v_Vertex,&v_Normal);
						}
						visState = 0;
					}
				}
			}
		}
	}
	packVertices(&v_Vertex,&v_Normal);
}
/*
	===============================================
	Adding vertices to the vertex colection. At the
	moment unused and better cast would be to float
	===============================================
*/
void FoxelManager::addPointVertices(GLfloat x, GLfloat y, GLfloat z, char visState, std::vector<GLfloat>* v_Vertex,std::vector<GLfloat>* v_Normal){

	GLfloat s = 0.5f*lod;	// have to be float !
	GLfloat d = 1.0f*lod;	// just to disable warnings

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
void FoxelManager::addPolygonVertices(GLfloat x, GLfloat y, GLfloat z, char visState, std::vector<GLfloat>* v_Vertex, std::vector<GLfloat>* v_Normal){
	
	GLfloat d = (GLfloat)1*lod;

	if(visState & 1){
		//glNormal3f(0,0,1); // oben
		v_Normal->push_back(0); v_Normal->push_back(0); v_Normal->push_back(1);
		v_Normal->push_back(0); v_Normal->push_back(0); v_Normal->push_back(1);
		v_Normal->push_back(0); v_Normal->push_back(0); v_Normal->push_back(1);
		v_Normal->push_back(0); v_Normal->push_back(0); v_Normal->push_back(1);

		v_Vertex->push_back(x+0); v_Vertex->push_back(y+0); v_Vertex->push_back(z+d); //v1
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+0); v_Vertex->push_back(z+d); //v2
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v3
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v4
	}
	if(visState & 2){
		//glNormal3f(0,0,-1); // unten
		v_Normal->push_back(0); v_Normal->push_back(0); v_Normal->push_back(-1);
		v_Normal->push_back(0); v_Normal->push_back(0); v_Normal->push_back(-1);
		v_Normal->push_back(0); v_Normal->push_back(0); v_Normal->push_back(-1);
		v_Normal->push_back(0); v_Normal->push_back(0); v_Normal->push_back(-1);

		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v5
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v6
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+0); v_Vertex->push_back(z+0); //v7
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+0); v_Vertex->push_back(z+0); //v8
	}
	if(visState & 4){
		//glNormal3f(-1,0,0); // links
		v_Normal->push_back(-1); v_Normal->push_back(0); v_Normal->push_back(0);
		v_Normal->push_back(-1); v_Normal->push_back(0); v_Normal->push_back(0);
		v_Normal->push_back(-1); v_Normal->push_back(0); v_Normal->push_back(0);
		v_Normal->push_back(-1); v_Normal->push_back(0); v_Normal->push_back(0);

		v_Vertex->push_back(x+0); v_Vertex->push_back(y+0); v_Vertex->push_back(z+0); //v8
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+0); v_Vertex->push_back(z+d); //v1
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v4
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v5
	}
	if(visState & 8){
		//glNormal3f(1,0,0); // rechts
		v_Normal->push_back(1); v_Normal->push_back(0); v_Normal->push_back(0);
		v_Normal->push_back(1); v_Normal->push_back(0); v_Normal->push_back(0);
		v_Normal->push_back(1); v_Normal->push_back(0); v_Normal->push_back(0);
		v_Normal->push_back(1); v_Normal->push_back(0); v_Normal->push_back(0);

		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v6
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v3
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+0); v_Vertex->push_back(z+d); //v2
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+0); v_Vertex->push_back(z+0); //v7
	}
	if(visState & 16){
		//glNormal3f(0,1,0); // vorne
		v_Normal->push_back(0); v_Normal->push_back(1); v_Normal->push_back(0);
		v_Normal->push_back(0); v_Normal->push_back(1); v_Normal->push_back(0);
		v_Normal->push_back(0); v_Normal->push_back(1); v_Normal->push_back(0);
		v_Normal->push_back(0); v_Normal->push_back(1); v_Normal->push_back(0);

		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v8
		v_Vertex->push_back(x+0); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v6
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+d); //v7
		v_Vertex->push_back(x+d); v_Vertex->push_back(y+d); v_Vertex->push_back(z+0); //v8
	}
	if(visState & 32){
		//glNormal3f(0,-1,0); // hinten
		v_Normal->push_back(0); v_Normal->push_back(-1); v_Normal->push_back(0);
		v_Normal->push_back(0); v_Normal->push_back(-1); v_Normal->push_back(0);
		v_Normal->push_back(0); v_Normal->push_back(-1); v_Normal->push_back(0);
		v_Normal->push_back(0); v_Normal->push_back(-1); v_Normal->push_back(0);

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
void FoxelManager::packVertices(std::vector<GLfloat> *v_Vertex, std::vector<GLfloat>* v_Normal){
	delete[] vertices;
	delete[] normals;
	vertexCount -= (long) anzVertex;
	polyCount -= (long) anzPolygon;
	anzVertex = (unsigned int) v_Vertex->size() /3;
	anzPolygon = anzVertex / 3;
	vertexCount += anzVertex;
	vertices = new GLfloat[v_Vertex->size()];
	normals = new GLfloat[v_Vertex->size()];
	for(unsigned int i = 0; i < v_Vertex->size(); i++){
		vertices[i] = v_Vertex->at(i);
		normals[i] = v_Normal->at(i);
	}
	// Creating Buffer and uploading data
	
	if(anzVertex > 0){
		glBindVertexArray(vao);

		// Vertex
		glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*v_Vertex->size(), vertices, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
		// Normals
		glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*v_Vertex->size(), normals, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,0);
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
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	PM::useProg(PROGRAM_FOXEL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	for(unsigned int i = 0; i < chunks.size(); i++){
		chunks.at(i)->drawChunk();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
	glUniform3f(PM::getUnifLoc(PROGRAM_FOXEL, "chunk_Position"),0.0f,0.0f,0.0f);
	PM::useProg(PROGRAM_NULL);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}
/*
	====================================
	Draws a single chunk at his Position
	====================================
 */
void FoxelManager::drawChunk(){
	Screen::ViewMatrix.translate((float)position.x,(float)position.y,(float)position.z);
	glUniformMatrix4fv(PM::getUnifLoc(PROGRAM_FOXEL, "viewMatrix"), 1, GL_FALSE, Screen::ViewMatrix.getMatrix());
	glUniform3f(PM::getUnifLoc(PROGRAM_FOXEL, "chunk_Position"),(float)-position.x,(float)-position.y,(float)-position.z);
	if(anzVertex > 0){
		// draw Foxel	
		glBindVertexArray(vao);
		glVertexAttrib4f(1,1.0f,0.25f,0.0125f,0.5f);
		glDrawArrays(GL_QUADS, 0, anzVertex);
		glBindVertexArray(NULL);
	}
	// draw a debugBox
	if(debug){
		glColor3f(1.0f,1.0f,1.0f);
		glVertexPointer(3,GL_FLOAT,0,debugChunkBoxV);
		glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, debugChunkBoxI);
	}
	Screen::ViewMatrix.translate((float)-position.x,(float)-position.y,(float)-position.z);
	glUniformMatrix4fv(PM::getUnifLoc(PROGRAM_FOXEL, "viewMatrix"), 1, GL_FALSE, Screen::ViewMatrix.getMatrix());
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

void FoxelManager::makeBlock(Vec3 start, Vec3 end, int id){
	std::vector<std::vector<int>> chunkIDs;
	std::vector<int> currentChunkID;
	int idCX, idCY, idCZ;

	int fx,fy,fz;
	for(int x = (int)start.x; x < (int)end.x; x++){
		for(int y = (int)start.y; y < (int)end.y; y++){
			for(int z = (int)start.z; z < (int)end.z; z++){
				currentChunkID.clear();
				// tracing Chunk id
				idCX = x / BITSIZE; 
				idCY = y / BITSIZE;
				idCZ = z / BITSIZE;

				if(x < 0) idCX--;
				if(y < 0) idCY--;
				if(z < 0) idCZ--;

				currentChunkID.push_back(idCX);
				currentChunkID.push_back(idCY);
				currentChunkID.push_back(idCZ);
				
				// chunk exist? no? create new ...
				if(idMap.find(currentChunkID) == idMap.end()){
					chunks.push_back(new FoxelManager(idCX,idCY,idCZ));
				}
				if(std::find(chunkIDs.begin(), chunkIDs.end(), currentChunkID) == chunkIDs.end()) {
					chunkIDs.push_back(currentChunkID);
				}

				// tracing Foxel position in chunk
				fx = x % (BITSIZE);
				fy = y % (BITSIZE);
				fz = z % (BITSIZE);

				if(x <= 0 && idCX < 0) fx += BITSIZE-1;
				if(y <= 0 && idCY < 0) fy += BITSIZE-1;
				if(z <= 0 && idCZ < 0) fz += BITSIZE-1;

				idMap[currentChunkID]->bitGrid[fx][fy][fz] = true;
			}
		}
	}

	// update Foxels
	for(int i = 0; i < chunkIDs.size(); i++){
		idMap[chunkIDs[i]]->setupFoxels();
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


