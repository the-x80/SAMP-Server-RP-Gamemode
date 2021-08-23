#include "Framework.h"

#include "GameObject.h"

SAMP_SDK::GameObject::GameObject()
{
}

bool SAMP_SDK::GameObject::RemoveComponent(Component* c)
{
    return a_c_OwnedComponents.Remove(c);
}
