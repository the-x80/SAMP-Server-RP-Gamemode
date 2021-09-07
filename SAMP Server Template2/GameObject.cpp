#include "Framework.h"
#include "SAMP SDK.h"

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
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerConnect(player);
    }
}
void SAMP_SDK::GameObject::OnPlayerDisconnect(Player* player)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerDisconnect(player);
    }
}
void SAMP_SDK::GameObject::OnPlayerSpawn(Player* player)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerSpawn(player);
    }
}
void SAMP_SDK::GameObject::OnPlayerDeath(Player* player, Player* killer, int reason)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerDeath(player, killer, reason);
    }
}
void SAMP_SDK::GameObject::OnPlayerEnterVehicle(Player* player, Vehicle* vehicle, bool is_Passanger)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerEnterVehicle(player, vehicle, is_Passanger);
    }
}
void SAMP_SDK::GameObject::OnPlayerExitVehicle(Player* player, Vehicle* vehicle)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerExitVehicle(player, vehicle);
    }
}
void SAMP_SDK::GameObject::OnPlayerStateChanged(Player* player, int newstate, int oldstate)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerStateChanged(player, newstate, oldstate);
    }
}
void SAMP_SDK::GameObject::OnPlayerEnterCheckpoint(Player* player)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerEnterCheckpoint(player);
    }
}
void SAMP_SDK::GameObject::OnPlayerLeaveCheckpoint(Player* player)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerLeaveCheckpoint(player);
    }
}
void SAMP_SDK::GameObject::OnPlayerEnterRaceCheckpoint(Player* player)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerEnterRaceCheckpoint(player);
    }
}
void SAMP_SDK::GameObject::OnPlayerLeaveRaceCheckpoint(Player* player)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerLeaveRaceCheckpoint(player);
    }
}
void SAMP_SDK::GameObject::OnPlayerClickMap(Player* player, Vector3 position)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerClickMap(player, position);
    }
}
void SAMP_SDK::GameObject::OnPlayerRequestSpawn(Player* player)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerRequestSpawn(player);
    }
}
void SAMP_SDK::GameObject::OnPlayerObjectMoved(Player* player, int objectid)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerObjectMoved(player, objectid);
    }
}
void SAMP_SDK::GameObject::OnPlayerPickupPickup(Player* player, int pickupid)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerPickupPickup(player, pickupid);
    }
}
void SAMP_SDK::GameObject::OnPlayerUpdate(Player* player)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerUpdate(player);
    }
}
void SAMP_SDK::GameObject::OnPlayerText(Player* player, const char* text)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerText(player, text);
    }
}
void SAMP_SDK::GameObject::OnPlayerCommandText(Player* player, const char* command)
{
    if (this->a_c_OwnedComponents.Length() == 0) {
        return;
    }

    for (int i = 0; i < this->a_c_OwnedComponents.Length(); i++) {
        Component* currentComponent = this->a_c_OwnedComponents[i];

        currentComponent->OnPlayerCommandText(player, command);
    }
}
#pragma endregion