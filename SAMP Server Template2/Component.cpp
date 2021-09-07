#include "Framework.h"
#include "SAMP SDK.h"
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

void SAMP_SDK::Component::OnPlayerConnect(Player* player)
{
}

void SAMP_SDK::Component::OnPlayerDisconnect(Player* player)
{
}

void SAMP_SDK::Component::OnPlayerSpawn(Player* player)
{
}

void SAMP_SDK::Component::OnPlayerDeath(Player* player, Player* killer, int reason)
{
}

void SAMP_SDK::Component::OnPlayerEnterVehicle(Player* player, Vehicle* vehicle, bool is_Passanger)
{
}

void SAMP_SDK::Component::OnPlayerExitVehicle(Player* player, Vehicle* vehicle)
{
}

void SAMP_SDK::Component::OnPlayerStateChanged(Player* player, int newstate, int oldstate)
{
}

void SAMP_SDK::Component::OnPlayerEnterCheckpoint(Player* player)
{
}

void SAMP_SDK::Component::OnPlayerLeaveCheckpoint(Player* player)
{
}

void SAMP_SDK::Component::OnPlayerEnterRaceCheckpoint(Player* player)
{
}

void SAMP_SDK::Component::OnPlayerLeaveRaceCheckpoint(Player* player)
{
}

void SAMP_SDK::Component::OnPlayerClickMap(Player* player, Vector3 position)
{
}

void SAMP_SDK::Component::OnPlayerRequestSpawn(Player* player)
{
}

void SAMP_SDK::Component::OnPlayerObjectMoved(Player* player, int objectid)
{
}

void SAMP_SDK::Component::OnPlayerPickupPickup(Player* player, int pickupid)
{
}

void SAMP_SDK::Component::OnPlayerUpdate(Player* player)
{
}

void SAMP_SDK::Component::OnPlayerText(Player* player, const char* text)
{
}

void SAMP_SDK::Component::OnPlayerCommandText(Player* player, const char* command)
{
}
