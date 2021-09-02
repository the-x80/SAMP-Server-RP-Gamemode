#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#ifndef _FUNCTIONAL_
#include <functional>
#endif

//About
//	Basic Event system used to call relevant functions inside the Component objects of GameObjects
//	
//Developer notes
//
//Changelog
//	28.8.2021
//		-Started development
//		-Added a TriggerEvent method in the Dispatcher object

namespace EventSystem{
	class Event {
	public:
		String name;

		/// <summary>
		/// Specifies the functions to be called when this event fires.
		/// </summary>
		Stack<std::function<void()>> functions;
	};
	class EventListener {
	public:
		Array<Event> assignedEvents;

	};
	class Dispatcher {
	private:
		Array<EventListener*> listeners;
	public:
		Dispatcher();

		void RegisterListener(EventListener* l);
		void UnregisterListener(EventListener* l);

		void TriggerEvent(Event e);
	};

	static Array<Dispatcher*> a_DispatcherPool;
	static const Dispatcher* main_Dispatcher = a_DispatcherPool[0];

	void Create();
	void Release();

	Dispatcher* CreateDispatcher();
	bool FreeDispatcher(Dispatcher* d);
}



#endif
