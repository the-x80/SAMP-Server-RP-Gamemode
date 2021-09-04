#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Component.h"

namespace SAMP_SDK {
	class Player;
	class Vehicle;

	//Game object should be a generic base type in wich all of the objects inherrit from
	//It should have the bare minimum of controlls and should not be acessed directly
	class GameObject {
	private:
	protected:
		Array<Component*> a_c_OwnedComponents;

#pragma region Callback pointers
		Array<Delegate*> a_del_OnStart;
		Array<Delegate*> a_del_OnEnable;
		Array<Delegate*> a_del_OnDisable;
		Array<Delegate*> a_del_OnTick;
#pragma endregion

	public:
		GameObject();


#pragma region SAMP Callbacks
		virtual void OnPlayerConnect(Player* player);
		virtual void OnPlayerDisconnect(Player* player);

		virtual void OnPlayerSpawn(Player* player);

		virtual void OnPlayerDeath(Player* player, Player* killer, int reason);

		virtual void OnPlayerEnterVehicle(Player* player, Vehicle* vehicle, bool is_Passanger);
		virtual void OnPlayerExitVehicle(Player* player, Vehicle* vehicle);

		virtual void OnPlayerStateChanged(Player* player, int newstate, int oldstate);

		virtual void OnPlayerEnterCheckpoint(Player* player);
		virtual void OnPlayerLeaveCheckpoint(Player* player);

		virtual void OnPlayerEnterRaceCheckpoint(Player* player);
		virtual void OnPlayerLeaveRaceCheckpoint(Player* player);
		
		virtual void OnPlayerClickMap(Player* player, Vector3 position);

		virtual void OnPlayerRequestSpawn(Player* player);

		virtual void OnPlayerObjectMoved(Player* player, int objectid);//The object id will be replaced

		virtual void OnPlayerPickupPickup(Player* player, int pickupid);//Pickupid will be replaced

		virtual void OnPlayerUpdate(Player* player);

		virtual void OnPlayerText(Player* player, const char* text);
		virtual void OnPlayerCommandText(Player* player, const char* command);
#pragma endregion



		template <typename T> inline T* AddComponent() {
			T* gen_Component = new T();
			this->a_c_OwnedComponents.Add(T);
			T->go_OwnedBy = this;
			T->RegisterCallbacks();
			return gen_Component;
		}
		bool RemoveComponent(Component* c);
	};

}
#endif