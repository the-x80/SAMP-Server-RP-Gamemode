#define _CRT_SECURE_NO_WARNINGS
#include <string>

#include "Array.h"
#include "Event System.h"

EventSystem::Event::Event()
{
	this->n_ID = 0;
	this->cstr_Name = new char[0];
	this->n_NameLen = 0;
}

EventSystem::Event::~Event()
{
	delete[] this->cstr_Name;
	this->n_NameLen = 0;
}

void EventSystem::Event::SetName(const char* cstr_name)
{
	delete[] this->cstr_Name;
	this->cstr_Name = new char[strlen(cstr_name) + 1];
	memset(this->cstr_Name, 0, strlen(cstr_name) + 1);
	strcpy(this->cstr_Name, cstr_name);
	this->n_NameLen = strlen(this->cstr_Name);
}

void EventSystem::RegisterEvent(Event e_Event)
{
	EventSystem::a_Events.Add(e_Event);
}

void EventSystem::UnregristerEvent(Event e_Event)
{
	EventSystem::a_Events.Remove(e_Event);
}
