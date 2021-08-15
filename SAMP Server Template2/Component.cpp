#include "Framework.h"
#include "GameObject.h"
#include "Component.h"

char* SAMP_SDK::Component::GetName()
{
    return this->cstr_Name;
}

void SAMP_SDK::Component::SetName(char* name)
{
    delete[] cstr_Name;
    this->cstr_Name = name;
}

void SAMP_SDK::Component::RegisterCallbacks()
{
    return;
}
