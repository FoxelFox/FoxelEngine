#pragma once
#include "Event.h"
#include "Vec3d.h"
namespace Event{
	class setFoxel : public Event::BasicEvent{
	private:
		Vec3d* position;
		char newFoxelID;

	public:
		setFoxel(Vec3d* pos, char id);
		Vec3d* getPosition();
		char getNewFoxelID();
		~setFoxel(void);
	};
}