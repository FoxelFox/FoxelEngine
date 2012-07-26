#include "Foxel_Interaction.h"

using namespace Event;

setFoxel::setFoxel(Vec3d* pos, char id) : BasicEvent(){
	eventID = Event::SET_FOXEL;
	newFoxelID = id;
	position = pos;

}

Vec3d* setFoxel::getPosition(){
	return position;
}

setFoxel::~setFoxel(void){
}
