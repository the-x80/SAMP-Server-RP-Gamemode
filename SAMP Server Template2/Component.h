#ifndef COMPONENT_H
#define COMPONENT_H



namespace SAMP_SDK {
	class GameObject;

	//This is the base class of all components.
	//It is used to extend the functionality of the GameObject class and its derrivatives
	class Component {
	private:
		char* cstr_Name;

		/// <summary>
		/// Specifies weather the Component is enabled and wether the GameObject calls the registered 
		/// messages.
		/// </summary>
		bool b_Enabled;

		/// <summary>
		/// References the owner of this component.
		/// </summary>
		GameObject* go_OwnedBy;

		EventSystem::EventListener* eventListener;
	public:



		char* GetName();
		void SetName(char* name);

		virtual void RegisterCallbacks();

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
	};
}

#endif
