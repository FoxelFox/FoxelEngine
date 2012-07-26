#include "Map.h"
#include "FoxelManager.h"
#include <fstream>

using namespace std;
string Map::name = "Empty";

Map::Map(){
}

Map::~Map(void){
}

void Map::createBlock(Vec3 start, Vec3 end, short id, Color color){
	int cidX, cidY, cidZ;
	stack<ChunkBrush> chunkBrushes;
	vector<int> chunkID = FoxelManager::tracingChunkID(start);

	// splitting up in seperate Chunk-Brushes
	Vec3 cStart;

	int sx,sy,sz,ex,ey,ez;

	cidX = chunkID[0];
	cStart.x = start.x;
	sx = (int)cStart.x % 128;

	int xmod = (int)start.x % 128;
	int ymod = (int)start.y % 128;
	int zmod = (int)start.z % 128;

	if(xmod < 0) xmod *= -1;
	if(ymod < 0) ymod *= -1;
	if(zmod < 0) zmod *= -1;

	while(cStart.x - xmod < end.x){
		if(cStart.x > start.x) sx = 0;
			//            brush between 2 chunks
		int cxmod = (int)cStart.x % 128;
		if(cxmod < 0) cxmod *= -1;
		if(cStart.x + 128 - cxmod < end.x){
			ex = 127;
		}else{
			ex = (int)end.x % 128;;
		}

		cidY = chunkID[1];
		cStart.y = start.y;
		sy = (int)cStart.y % 128;
		while(cStart.y - ymod < end.y){
			if(cStart.y > start.y) sy = 0;
				//            brush between 2 chunks
			int cymod = (int)cStart.y % 128;
			if(cymod < 0) cymod *= -1;
			if(cStart.y + 128 - cymod  < end.y){
				ey = 127;
			}else{
				ey = (int)end.y % 128;;
			}

			cidZ = chunkID[2];
			cStart.z = start.z;
			sz = (int)cStart.z % 128;
			while(cStart.z - zmod < end.z){
				if(cStart.z > start.z) sz = 0;
					//            brush between 2 chunks
				int czmod = (int)cStart.z % 128;
				if(czmod < 0) czmod *= -1;
				if(cStart.z + 128 - czmod  < end.z){
					ez = 127;
				}else{
					ez = (int)end.z % 128;;
				}

				ChunkBrush cBrush;
				
				if(sx < 0) sx += 128;
				if(sy < 0) sy += 128;
				if(sz < 0) sz += 128;

				if(ex < 0) ex += 128;
				if(ey < 0) ey += 128;
				if(ez < 0) ez += 128;

				cBrush.sX = sx;
				cBrush.sY = sy;
				cBrush.sZ = sz;

				cBrush.eX = ex;
				cBrush.eY = ey;
				cBrush.eZ = ez;

				cBrush.idX = cidX;
				cBrush.idY = cidY;
				cBrush.idZ = cidZ;

				cBrush.cR = color.getRed();
				cBrush.cG = color.getGreen();
				cBrush.cB = color.getBlue();
				cBrush.em = color.getAlpha();

				cBrush.id = id;

				chunkBrushes.push(cBrush);
				cStart.z += 128;
				cidZ++;
			}
			cStart.y += 128;
			cidY++;
		}
		cStart.x += 128;
		cidX++;
	}

	// send to FoxelManager
	while(chunkBrushes.size() != 0){
		FoxelManager::addBrush(chunkBrushes.top());
		chunkBrushes.pop();
	}
	//FoxelManager::update();
}

void Map::update(){
	FoxelManager::update();
}

bool Map::load(string mapName){
	FoxelManager::deleteAll();
	name = mapName;
	char header;
	fstream file;
	FoxelManager* chunk;
	// TODO Error catching
	file.open("Maps/" + mapName + ".foxel", ios::in);
	
	if(file.good()){
		unsigned short sX,sY,sZ;		// Start Point x y z;
		unsigned short eX,eY,eZ;		// End Point x y z;
		unsigned short cR,cG,cB,em;	// Color
		short id;					// Foxel id

		while(!file.eof()){
			file >> header;
			switch(header){
				case 'C':
					int idX,idY,idZ;
					file >> idX >> idY >> idZ;
					chunk = new FoxelManager(idX,idY,idZ);
					break;
				case 'B':
					file >> sX >> sY >> sZ >> eX >> eY >> eZ >> id >> cR >> cG >> cB >> em;
					chunk->brushes.push_back(new Brush((unsigned char)sX,(unsigned char)sY,(unsigned char)sZ,(unsigned char)eX,(unsigned char)eY,(unsigned char)eZ,id,(unsigned char)cR,(unsigned char)cG,(unsigned char)cB,(unsigned char)em));
					break;
				default: break;
			}
		}
	}
	FoxelManager::loadAllChunks();
	return true;
}

void Map::save(string mapName){
	name = mapName;
	fstream file;
	file.open("Maps/" + mapName + ".foxel", ios::out);
	std::vector<FoxelManager*>* fm = FoxelManager::getChunkList();

	for(int i = 0; i < fm->size(); i++){
		if(fm->at(i)->brushes.size() > 0){ // is there any brush?
			file << "C " << fm->at(i)->myID[0] << " " << fm->at(i)->myID[1] << " " << fm->at(i)->myID[2] << endl;
			for(int j = 0; j < fm->at(i)->brushes.size(); j++){
				file << "B " << (short)fm->at(i)->brushes[j]->sX << " " << (short)fm->at(i)->brushes[j]->sY << " " << (short)fm->at(i)->brushes[j]->sZ
				<< " " << (short)fm->at(i)->brushes[j]->eX << " " << (short)fm->at(i)->brushes[j]->eY << " " << (short)fm->at(i)->brushes[j]->eZ
				<< " " << (short)fm->at(i)->brushes[j]->id << " " << (short)fm->at(i)->brushes[j]->cR << " " << (short)fm->at(i)->brushes[j]->cG
				<< " " << (short)fm->at(i)->brushes[j]->cB << " " << (short)fm->at(i)->brushes[j]->em << endl;
			}
			file << endl;
		}
	}
	file.close();
}