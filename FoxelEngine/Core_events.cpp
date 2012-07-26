#include "Core.h"
#include <iostream>

using namespace Event;

BasicEvent* curentEvent;
setFoxel* p;

void Core::events(){

	while(BasicEvent::isWaiting()){
		curentEvent = BasicEvent::getNext();
		p = (setFoxel*)curentEvent;
		switch(curentEvent->getID()){
			case SET_FOXEL: FoxelManager::settingFoxel((setFoxel*)curentEvent);break;
			case PLAYMODE: startGame(); break;
			case EDITMODE: startEditor(); break;
			case EXIT:	   running = false;
						   break;
						
						
		default: break;
		}
	}
}