#pragma once
#include <vector>

namespace Event{

	enum EventID{ SET_FOXEL, EXIT, PLAYMODE, EDITMODE };

	static int nextEvent;
	static int waitingEvents;

	class BasicEvent{
	private:
		static void deleteEvents();


	protected:
		short eventID;

	public:
		BasicEvent(void);
		BasicEvent(short id);
		static void initEventSystem();
		static BasicEvent* getNext();
		static bool isWaiting();
		short getID();
		~BasicEvent(void);
	};
	static std::vector<BasicEvent*> eventList;
}


