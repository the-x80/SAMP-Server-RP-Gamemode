#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H
#include <functional>

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
		Array<EventListener> listeners;
	public:
		Dispatcher();

		void RegisterListener(EventListener l);
		void UnregisterListener(EventListener l);
	};

	static Array<Dispatcher*> a_DispatcherPool;

	void Create();
	void Release();

	Dispatcher* CreateDispatcher();
	bool FreeDispatcher(Dispatcher* d);
}



#endif
