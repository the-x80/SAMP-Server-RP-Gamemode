#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

namespace EventSystem {
	namespace Events {
		class BaseEventType {
		public:

			BaseEventType();
		};
	}
}


#include "GenericEventTypes.h"








namespace EventSystem{
	class EventListener {
	public:


	};
	class Dispatcher {
	public:
		Dispatcher();
	};
}



#endif
