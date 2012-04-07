#pragma once
#include <vector>

namespace Event{

	enum EventID{ SET_FOXEL = 128, EXIT = 0, PLAYMODE  = 1, EDITMODE = 2};

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


