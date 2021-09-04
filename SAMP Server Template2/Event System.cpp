#define _CRT_SECURE_NO_WARNINGS
#include <string>

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#include "Framework.h"
#include "Event System.h"

EventSystem::Dispatcher::Dispatcher()
{
	this->listeners = Array<EventListener*>();
}

void EventSystem::Dispatcher::RegisterListener(EventListener* l)
{
	this->listeners.Add(l);
}

void EventSystem::Dispatcher::UnregisterListener(EventListener* l)
{
	this->listeners.Remove(l);
}

void EventSystem::Dispatcher::TriggerEvent(Event e)
{
	for (int i = 0; i < listeners.Length(); i++) {
		EventListener* currentListener = listeners[i];

		try {
			//Call the events function
		}
		catch (std::bad_function_call e) {

		}
		catch (Exceptions::Exception* e) {
			//Generic exception block for unknown exceptions

		}
	}
}

void EventSystem::Create()
{
	EventSystem::a_DispatcherPool = Array<EventSystem::Dispatcher*>();
	EventSystem::a_DispatcherPool.Add(new EventSystem::Dispatcher());
}

void EventSystem::Release()
{
	EventSystem::a_DispatcherPool.Clear();
}

EventSystem::Dispatcher* EventSystem::CreateDispatcher()
{
	Dispatcher* retVal = new Dispatcher();

	EventSystem::a_DispatcherPool.Add(retVal);
	return retVal;
}

bool EventSystem::FreeDispatcher(Dispatcher* d)
{
	EventSystem::a_DispatcherPool.Remove(d);
	delete d;
	return false;
}
