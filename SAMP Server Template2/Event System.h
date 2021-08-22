#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

namespace EventSystem {
	class Event {
	public:
		int n_ID;
		char* cstr_Name;
		int n_NameLen;

		Event();
		~Event();

		void SetName(const char* cstr_name);
	};



	static Array<Event*> a_Events;



	void RegisterEvent(Event* e_Event);
	void UnregristerEvent(Event* e_Event);

	Event* FindEventByName(const char* cstr_Name);
}



#endif
