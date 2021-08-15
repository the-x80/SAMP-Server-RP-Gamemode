#include "Framework.h"
#include "SAMPExceptions.h"

#include "GameObject.h"
#include "Vehicle.h"
#include "Player.h"

#include "sampgdk.h"


Array<SAMP_SDK::Player*> SAMP_SDK::Player::a_PlayerPool;


SAMP_SDK::Player::Player()
{
	this->n_ID = 0;
}

SAMP_SDK::Player::~Player()
{
}



SAMP_SDK::Vehicle* SAMP_SDK::Player::GetCurrentVehicle()
{
	if (this->n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsPlayerID();
	}
	else if (this->n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsPlayerID();
	}


	int n_VehicleID = GetPlayerVehicleID(this->n_ID);
	if (n_VehicleID == 0) {
		return nullptr;
	}
	return SAMP_SDK::Vehicle::FindVehicleByID(n_VehicleID);
}

SAMP_SDK::Player* SAMP_SDK::Player::Create(int n_ID)
{
	if (n_ID < 0) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsPlayerID();
	}
	else if (n_ID > 1000) {
		throw new SAMP_SDK::Exceptions::OutOfBoundsPlayerID();
	}

	Player* ply_Created = new Player();
	if (ply_Created == nullptr) {//Could not allocate memory for player
		throw new ::Exceptions::OutOfMemoryException();
	}
	ply_Created->n_ID = n_ID;
	Player::a_PlayerPool.Add(ply_Created);
	return ply_Created;
}

void SAMP_SDK::Player::Destroy(Player* ply)
{
	if (ply == nullptr) {
		throw ::Exceptions::NullPointerException();
	}
	Player::a_PlayerPool.Remove(ply);
	delete ply;
}
