#include "Event.h"
using namespace Event;
BasicEvent::BasicEvent(void){
	eventList.push_back(this);
	waitingEvents++;
}

BasicEvent::BasicEvent(short id){
	eventID = id;
	eventList.push_back(this);
	waitingEvents++;
}

void BasicEvent::initEventSystem(){
	waitingEvents = 0;
	nextEvent = -1;
}

BasicEvent* BasicEvent::getNext(){
	nextEvent++;
	waitingEvents--;
	if(nextEvent  <= (int)eventList.size()){
		return eventList[nextEvent];
	}else{
		deleteEvents();
		return NULL;
	}
}

short BasicEvent::getID(){
	return eventID;
}

bool BasicEvent::isWaiting(){
	if(waitingEvents > 0) return true;
	else return false;
}

void BasicEvent::deleteEvents(){
	for(unsigned int i = 0; i < eventList.size(); i++){
		delete eventList[i];
	}
	eventList.clear();
}

BasicEvent::~BasicEvent(void){
}
