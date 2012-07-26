#include "BrushBox.h"
#include "Editor.h"
#include "Map.h"

using namespace MapEditor;

BrushBox::BrushBox(void){
	size.x = size.y = size.z = 16.0f;
	snapedPosition.x = snapedPosition.y = snapedPosition.y = 16.0f;
	anzIndex = 24;
	anzVertex = 8;
	indices = BoxI;
	colors = BoxC;
	vertices = BoxV;
	rebuildMesh();
	painting = false;
}

BrushBox::~BrushBox(void)
{
}

void BrushBox::rebuildMesh(){
	vertices[ 3] = size.x;
	                       vertices[ 7] = size.y;
	                                              vertices[11] = size.z;
	vertices[12] = size.x; vertices[13] = size.y; vertices[14] = size.z;
	                       vertices[16] = size.y; vertices[17] = size.z;
	vertices[18] = size.x;                        vertices[20] = size.z;
	vertices[21] = size.x; vertices[22] = size.y;
	load(); // update to GPU
}

void BrushBox::draw(){
	Screen::ViewMatrix.translate(snapedPosition.x,snapedPosition.y,snapedPosition.z);
	Screen::updateViewMatix();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawElements(GL_LINES,anzIndex,GL_UNSIGNED_INT,indices);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
	Screen::ViewMatrix.translate(-snapedPosition.x,-snapedPosition.y,-snapedPosition.z);
	Screen::updateViewMatix();
}

void BrushBox::move(Vec3 value){
	moved += value;
	bool was_moved = false;
	if(moved.x > Editor::getGridDeep()){
		was_moved = true;
		snapedPosition.x += Editor::getGridDeep();
	}else if(moved.x < -Editor::getGridDeep()){
		was_moved = true;
		snapedPosition.x -= Editor::getGridDeep();
	}
	if(moved.y > Editor::getGridDeep()){
		was_moved = true;
		snapedPosition.y += Editor::getGridDeep();
	}else if(moved.y < -Editor::getGridDeep()){
		was_moved = true;
		snapedPosition.y -= Editor::getGridDeep();
	}
	if(moved.z > Editor::getGridDeep()){
		was_moved = true;
		snapedPosition.z += Editor::getGridDeep();
	}else if(moved.z < -Editor::getGridDeep()){
		was_moved = true;
		snapedPosition.z -= Editor::getGridDeep();
	}
	if(was_moved){
		moved.x = 0;
		moved.y = 0;
		moved.z = 0;
	}
}

void BrushBox::makeBlock(){
	Vec3 start, stop;

	if(paintStart.x <= paintStop.x){
		start.x = paintStart.x; stop.x = paintStop.x + size.x-1;
	}else{
		start.x = paintStop.x; stop.x = paintStart.x + size.x-1;
	}
	if(paintStart.y <= paintStop.y){
		start.y = paintStart.y; stop.y = paintStop.y + size.y-1;
	}else{
		start.y = paintStop.y; stop.y = paintStart.y + size.y-1;
	}
	if(paintStart.z <= paintStop.z){
		start.z = paintStart.z; stop.z = paintStop.z + size.z-1;
	}else{
		start.z = paintStop.z; stop.z = paintStart.z + size.z-1;
	}
	/*
	if(start.x < 0){ start.x++;}
	if(start.y < 0){ start.y++;}
	if(start.z < 0){ start.z++;}
	if(stop.x < 0){ stop.x++;}
	if(stop.y < 0){ stop.y++;}
	if(stop.z < 0){ stop.z++;}
	*/
	std::cout << "Start: " << start.x << "\t" << start.y << "\t" << start.z << std::endl;
	std::cout << "Stop:  " << stop.x << "\t" << stop.y << "\t" << stop.z << std::endl;
	Map::createBlock(start,stop,paintID, color);
}

void BrushBox::startPaint(){
	if(!painting){
		paintStart = snapedPosition;
		painting = true;
	}
}

void BrushBox::stopPaint(){
	if(painting){
		paintStop = snapedPosition;
		painting = false;
		makeBlock();
	}
}

void BrushBox::setPaintID(int id){
	paintID = id;
}

void BrushBox::setColor(Color color){
	this->color = color;
}