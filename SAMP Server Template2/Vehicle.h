#ifndef VEHICLE_H
#define VEHICLE_H


//Developer note.
//This has full SAMP functionality now.
//But some of the custom features are missing.
//Features like a method for setting individual panels,doors,lights,tyres to be damaged.
//Getting the Vehicle object from its ID


namespace SAMP_SDK {
	class GameObject;

	class Vehicle : public GameObject {
	private:
		static Array<Vehicle*> a_VehiclePool;
	protected:
		int n_ID;
		int n_Color1;
		int n_Color2;

	public:
		Vehicle();
		~Vehicle();

		/// <summary>
		/// Attaches a trailer vehicle to this vehicle.
		/// </summary>
		/// <param name="n_VehicleID">The trailer vehicle id that needs to be attached</param>
		/// <returns>Always true. This will not be the case in the future.</returns>
		bool AttachTrailer(int n_VehicleID);

		/// <summary>
		/// Sets a modification on the vehicle
		/// </summary>
		/// <param name="n_ModificationID">
		///		The modification id.
		///		See https://sampwiki.blast.hk/wiki/Car_Component_ID for more info.
		/// </param>	
		/// <returns>True if sucsess false if fail</returns>
		/// <exception cref="SAMP_SDK::Exceptions::VehicleDoesNotExist">
		/// Thrown if the car does not exist
		/// </exception>
		bool AddModification(int n_ModificationID);

		/// <summary>
		///		Changes the color of this vehicle
		/// </summary>
		/// <param name="col1">
		///		The first color
		/// </param>
		/// <param name="col2">
		///		The second color
		/// </param>
		/// <returns>
		///		True if sucsessfull, false if failed.
		/// </returns>
		/// <exception cref="SAMP_SDK::Exceptions::VehicleDoesNotExist">
		/// Thrown if the car does not exist
		/// </exception>
		bool ChangeColor(int col1, int col2);

		/// <summary>
		/// Changes the vehicles painjob if applicable
		/// </summary>
		/// <param name="n_PaintjobID">
		/// The paintjob id. See https://sampwiki.blast.hk/wiki/Paintjob for more details
		/// </param>
		/// <returns>Always true.</returns>
		bool ChangePaintjob(int n_PaintjobID);

		/// <summary>
		///	<para>
		/// Retrieves the installed component ID (modshop mod(ification)) on a vehicle in a specific slot.
		/// See https://sampwiki.blast.hk/wiki/GetVehicleComponentInSlot for more info.
		/// </para>
		/// </summary>
		/// <returns>
		/// The ID of the component installed in the specified slot. Returns 0 if no component in specified vehicle's specified slot, or if vehicle doesn't exist.
		/// </returns>
		int GetModificationInSlot(int n_SlotID);

		/// <summary>
		/// Retrieve the damage statuses of a vehicle.
		/// </summary>
		/// <param name="n_Panels">A variable to store the panel damage data in, passed by reference. Passing nullptr results in undefined behaviour.</param>
		/// <param name="n_Doors">A variable to store the door damage data in, passed by reference. Passing nullptr results in undefined behaviour.</param>
		/// <param name="n_Lights">A variable to store the light damage data in, passed by reference. Passing nullptr results in undefined behaviour.</param>
		/// <param name="n_Tyres">A variable to store the tire damage data in, passed by reference. Passing nullptr results in undefined behaviour.</param>
		/// <returns></returns>
		bool GetDamageStatus(int* n_Panels, int* n_Doors, int* n_Lights, int* n_Tyres);

		bool GetPanelDamageStatus(bool* front_left_panel, bool* front_right_panel, bool* rear_left_panel, bool* rear_right_panel, bool* windshield, bool* front_bumper, bool* rear_bumper);

		/// <summary>
		/// Retrieves the health of the current vehicle.
		/// </summary>
		/// <returns>The health of the vehicle</returns>
		/// <exception cref="SAMP_SDK::Exceptions::OutOfBoundsVehicleID">Thrown when the ID is out of bounds.</exception>
		/// <exception cref="SAMP_SDK::Exceptions::VehicleDoesNotExist">Thrown when the ID doesent belong to any vehicle.</exception>
		float GetHealth();

		/// <summary>
		/// Gets the model ID of a vehicle. See "https://sampwiki.blast.hk/wiki/Vehicle_Models" for more info.
		/// </summary>
		/// <returns>The vehicle's model ID</returns>
		/// <exception cref="SAMP_SDK::Exceptions::OutOfBoundsVehicleID">Thrown when the ID is out of bounds.</exception>
		/// <exception cref="SAMP_SDK::Exceptions::VehicleDoesNotExist">Thrown when the ID doesent belong to any vehicle.</exception>
		int GetModel();

		Vector3 GetPosition();

		/// <summary>
		/// Retrieves trailer vehicle id.
		/// </summary>
		/// <returns>The vehicle ID of the trailer or 0 if no trailer is attached.</returns>
		int GetTrailerID();

		Vector3 GetVelocity();

		int GetVirtualWorldID();

		float GetHeading();

		bool IsTrailerAttached();

		bool IsStreamedInForPlayer(int n_PlayerID);

		bool SetInterior(int n_InteriorID);

		bool RemoveModification(int n_ModificationID);

		bool Repair();
		bool RepairVisual();

		bool SetHealth(float f_Health);

		//bool SetParamsForPlayer(); Might need a bit of restructuring. IDK if I want to keep it here.

		bool SetPosition(Vector3 v3_Position);

		bool SetVelocity(Vector3 v3_Velocity);

		bool SetVirtualWorldID(int n_VWorldID);

		bool SetHeading(float f_Heading);

		bool SetPanelDamageStatus(int panels, int doors, int lights, int tyres);





		static Vehicle* Create(int n_ModelID, Vector3 vec3_Position, float f_Heading, int n_Color1, int n_Color2, int n_RespawnDelay, bool b_AddSiren);
		static Vehicle* CreateStatic(int n_ModelID, Vector3 vec3_Position, float f_Heading, int n_Color1, int n_Color2, int n_RespawnDelay, bool b_AddSiren);
		static Vehicle* FindVehicleByID(int n_ID);


	};
}
#endif