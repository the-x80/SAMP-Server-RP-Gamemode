#include "Framework.h"
#include "SAMPExceptions.h"
#include "GameObject.h"
#include "Player.h"
#include "Vehicle.h"

#include "sampgdk.h"

Array<SAMP_SDK::Vehicle*> SAMP_SDK::Vehicle::a_VehiclePool;

SAMP_SDK::Vehicle::Vehicle()
{
	this->n_Color1 = 0;
	this->n_Color2 = 0;
	this->n_ID = 0;
}

SAMP_SDK::Vehicle::~Vehicle()
{
}

bool SAMP_SDK::Vehicle::AttachTrailer(int n_VehicleID)
{
	//Since the documentation states that AttachTrailerToVehicle always return 1
	//It would be smart to do some sanity checks before.
	//Since this function is rarely used you could make it as thorough as possible
	int n_Result = AttachTrailerToVehicle(n_VehicleID, this->n_ID);
	return true;
}

bool SAMP_SDK::Vehicle::AddModification(int n_ModificationID)
{
	int n_Result = AddVehicleComponent(this->n_ID, n_ModificationID);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
		return false;
	}
	return true;
}

bool SAMP_SDK::Vehicle::ChangeColor(int col1, int col2)
{
	int n_Result = ChangeVehicleColor(this->n_ID, this->n_Color1, this->n_Color2);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
		return false;
	}
	return true;
}

bool SAMP_SDK::Vehicle::ChangePaintjob(int n_PaintjobID)
{
	ChangeVehiclePaintjob(this->n_ID, n_PaintjobID);
	return true;
}

int SAMP_SDK::Vehicle::GetModificationInSlot(int n_SlotID)
{
	int n_Result = GetVehicleComponentInSlot(this->n_ID, n_SlotID);
	return n_Result;
}

bool SAMP_SDK::Vehicle::GetDamageStatus(int* n_Panels, int* n_Doors, int* n_Lights, int* n_Tyres)
{
	int n_Result = GetVehicleDamageStatus(this->n_ID, n_Panels, n_Doors, n_Lights, n_Tyres);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
		return false;
	}
	return true;
}

bool SAMP_SDK::Vehicle::GetPanelDamageStatus(bool* front_left_panel, bool* front_right_panel, bool* rear_left_panel, bool* rear_right_panel, bool* windshield, bool* front_bumper, bool* rear_bumper)
{
	int panels;
	try {
		this->GetDamageStatus(&panels, nullptr, nullptr, nullptr);
	}
	catch(SAMP_SDK::Exceptions::VehicleDoesNotExist* e){
		return false;
	}
	return true;
}

float SAMP_SDK::Vehicle::GetHealth()
{
	float f_Health = 0.0f;
	int n_Result = GetVehicleHealth(this->n_ID, &f_Health);
	if (n_Result == 0) {//Function failed. Debug the result.
		if (this->n_ID < 0) {
			throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
		}
		else if (this->n_ID > 1000) {
			throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
		}
		else {
			throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
		}
		return 0.0f;
	}
	return f_Health;
}

int SAMP_SDK::Vehicle::GetModel()
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if(n_ID > 1000){
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}


	int n_Result = GetVehicleModel(this->n_ID);
	if (n_Result == 0) {//An error occured.
		//Most likely the vehicle does not exist.
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
	}
	return 0;
}

Vector3 SAMP_SDK::Vehicle::GetPosition()
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}

	float f_x, f_y, f_z;
	int n_Result = GetVehiclePos(this->n_ID, &f_x, &f_y, &f_z);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
	}
	return Vector3(f_x, f_y, f_z);
}

int SAMP_SDK::Vehicle::GetTrailerID()
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	return GetVehicleTrailer(this->n_ID);
}

Vector3 SAMP_SDK::Vehicle::GetVelocity()
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}

	Vector3 v3_Return;
	int n_Result = GetVehicleVelocity(this->n_ID, &v3_Return.x, &v3_Return.y, &v3_Return.z);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
	}
	return v3_Return;
}

int SAMP_SDK::Vehicle::GetVirtualWorldID()
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	return GetVehicleVirtualWorld(this->n_ID);
}

float SAMP_SDK::Vehicle::GetHeading()
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	float f_Return;
	int n_Result = GetVehicleZAngle(this->n_ID, &f_Return);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
	}
	return f_Return;
}

bool SAMP_SDK::Vehicle::IsTrailerAttached()
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	return IsTrailerAttachedToVehicle(this->n_ID);
}

bool SAMP_SDK::Vehicle::IsStreamedInForPlayer(int n_PlayerID)
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	if (n_PlayerID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsPlayerID();
	}
	else if (n_PlayerID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsPlayerID();
	}


	bool b_Return = IsVehicleStreamedIn(this->n_ID, n_PlayerID);

	return b_Return;
}

bool SAMP_SDK::Vehicle::SetInterior(int n_InteriorID)
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}


	int n_Result = LinkVehicleToInterior(this->n_ID, n_InteriorID);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
	}
	return false;
}

bool SAMP_SDK::Vehicle::RemoveModification(int n_ModificationID)
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}


	RemoveVehicleComponent(this->n_ID, n_ModificationID);
	return false;
}

bool SAMP_SDK::Vehicle::Repair()
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	int n_Result = RepairVehicle(this->n_ID);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
		return false;
	}
	return true;
}

bool SAMP_SDK::Vehicle::RepairVisual()
{
	return false;
}

bool SAMP_SDK::Vehicle::SetHealth(float f_Health)
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}

	int n_Result = SetVehicleHealth(this->n_ID, f_Health);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
	}
	return false;
}

bool SAMP_SDK::Vehicle::SetPosition(Vector3 v3_Position)
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}

	int n_Result = SetVehiclePos(this->n_ID, v3_Position.x, v3_Position.y, v3_Position.z);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
	}
	return false;
}

bool SAMP_SDK::Vehicle::SetVelocity(Vector3 v3_Velocity)
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}

	int n_Result = SetVehicleVelocity(this->n_ID, v3_Velocity.x, v3_Velocity.y, v3_Velocity.z);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
	}
	return false;
}

bool SAMP_SDK::Vehicle::SetVirtualWorldID(int n_VWorldID)
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}

	int n_Result = SetVehicleVirtualWorld(this->n_ID, n_VWorldID);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
	}
	return false;
}

bool SAMP_SDK::Vehicle::SetHeading(float f_Heading)
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsVehicleID();
	}

	int n_Result = SetVehicleZAngle(this->n_ID, f_Heading);
	if (n_Result == 0) {
		throw new SAMP_SDK::Exceptions::VehicleDoesNotExist();
	}
	return false;
}

bool SAMP_SDK::Vehicle::SetPanelDamageStatus(int panels, int doors, int lights, int tyres)
{
	int n_Result = UpdateVehicleDamageStatus(this->n_ID, panels, doors, lights, tyres);
	return false;
}

SAMP_SDK::Vehicle* SAMP_SDK::Vehicle::Create(int n_ModelID, Vector3 vec3_Position, float f_Heading, int n_Color1, int n_Color2, int n_RespawnDelay, bool b_AddSiren)
{
	int n_VehicleID = CreateVehicle(n_ModelID, vec3_Position.x,
		vec3_Position.y, vec3_Position.z,
		f_Heading, n_Color1, n_Color2, n_RespawnDelay,
		b_AddSiren);
	if (n_VehicleID == INVALID_VEHICLE_ID) {
		//Vehicle was not created (vehicle limit reached or invalid vehicle model ID passed)

	}

	SAMP_SDK::Vehicle* veh_Created = new SAMP_SDK::Vehicle();
	if (veh_Created == nullptr) {
		throw new ::Exceptions::OutOfMemoryException();
	}
	veh_Created->n_ID = n_VehicleID;
	veh_Created->n_Color1 = n_Color1;
	veh_Created->n_Color2 = n_Color2;
	
	SAMP_SDK::Vehicle::a_VehiclePool.Add(veh_Created);
	return veh_Created;
}

SAMP_SDK::Vehicle* SAMP_SDK::Vehicle::CreateStatic(int n_ModelID, Vector3 vec3_Position, float f_Heading, int n_Color1, int n_Color2, int n_RespawnDelay, bool b_AddSiren)
{
	int n_VehicleID = AddStaticVehicleEx(n_ModelID, vec3_Position.x,
		vec3_Position.y, vec3_Position.z,
		f_Heading, n_Color1, n_Color2, n_RespawnDelay,
		b_AddSiren);
	if (n_VehicleID == INVALID_VEHICLE_ID) {
		//Vehicle was not created (vehicle limit reached or invalid vehicle model ID passed)

	}

	SAMP_SDK::Vehicle* veh_Created = new SAMP_SDK::Vehicle();
	if (veh_Created == nullptr) {
		throw new ::Exceptions::OutOfMemoryException();
	}
	veh_Created->n_ID = n_VehicleID;
	veh_Created->n_Color1 = n_Color1;
	veh_Created->n_Color2 = n_Color2;

	SAMP_SDK::Vehicle::a_VehiclePool.Add(veh_Created);
	return veh_Created;
}

SAMP_SDK::Vehicle* SAMP_SDK::Vehicle::FindVehicleByID(int n_ID)
{
	for (int i = 0; i < SAMP_SDK::Vehicle::a_VehiclePool.Length(); i++) {
		Vehicle* veh_Current = SAMP_SDK::Vehicle::a_VehiclePool[i];
		if (veh_Current->n_ID == n_ID) {
			return veh_Current;
		}
	}
	return nullptr;
}
