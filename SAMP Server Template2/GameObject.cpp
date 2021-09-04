#include "Framework.h"

#ifndef PLAYER_H
#include "Player.h"
#endif

#ifndef VEHICLE_H
#include "Vehicle.h"
#endif


#include "GameObject.h"

SAMP_SDK::GameObject::GameObject()
{
}

bool SAMP_SDK::GameObject::RemoveComponent(Component* c)
{
    return a_c_OwnedComponents.Remove(c);
}

#pragma region SAMP Callbacks
void SAMP_SDK::GameObject::OnPlayerConnect(Player* player)
{
}

void SAMP_SDK::GameObject::OnPlayerDisconnect(Player* player)
{
}
void SAMP_SDK::GameObject::OnPlayerSpawn(Player* player)
{
}
void SAMP_SDK::GameObject::OnPlayerDeath(Player* player, Player* killer, int reason)
{
}
void SAMP_SDK::GameObject::OnPlayerEnterVehicle(Player* player, Vehicle* vehicle, bool is_Passanger)
{
}
void SAMP_SDK::GameObject::OnPlayerExitVehicle(Player* player, Vehicle* vehicle)
{
}
void SAMP_SDK::GameObject::OnPlayerStateChanged(Player* player, int newstate, int oldstate)
{
}
void SAMP_SDK::GameObject::OnPlayerEnterCheckpoint(Player* player)
{
}
void SAMP_SDK::GameObject::OnPlayerLeaveCheckpoint(Player* player)
{
}
void SAMP_SDK::GameObject::OnPlayerEnterRaceCheckpoint(Player* player)
{
}
void SAMP_SDK::GameObject::OnPlayerLeaveRaceCheckpoint(Player* player)
{
}
void SAMP_SDK::GameObject::OnPlayerClickMap(Player* player, Vector3 position)
{
}
void SAMP_SDK::GameObject::OnPlayerRequestSpawn(Player* player)
{
}
void SAMP_SDK::GameObject::OnPlayerObjectMoved(Player* player, int objectid)
{
}
void SAMP_SDK::GameObject::OnPlayerPickupPickup(Player* player, int pickupid)
{
}
void SAMP_SDK::GameObject::OnPlayerUpdate(Player* player)
{
}
void SAMP_SDK::GameObject::OnPlayerText(Player* player, const char* text)
{
}
void SAMP_SDK::GameObject::OnPlayerCommandText(Player* player, const char* command)
{
}
#pragma endregion