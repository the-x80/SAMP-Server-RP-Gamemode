
#include "main.h"
#include "sampgdk.h"

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit()
{
	Debug::Log(__func__);
	//Do your gamemode init code here
	SAMP_SDK::activeGamemode = new SAMP_SDK::GameMode();


	//Load the gamemode configuration file and set up everything gamemode related

	//Remove all of the default building entrances
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	ShowNameTags(1);
	EnableTirePopping(1);//Apparently this function is removed.
	EnableVehicleFriendlyFire();
	ManualVehicleEngineAndLights();
	ShowPlayerMarkers(0);
	LimitGlobalChatRadius(0);//Custom global chat handling
	UsePlayerPedAnims();//See if this will be necessary

	//Load the map
	//Not implemented yet
	

	//When map generation finishes create the vehicles
	
	//When vehicle creation finishes create actors
	//Not implemented yet.

	//Initializing the worker threads
	//throw new Exceptions::Exception();
	Debug::Log("Done");
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeExit() {
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	SAMP_SDK::Player* ply_Current = nullptr;
	try {
		ply_Current = SAMP_SDK::Player::Create(playerid);
	}
	catch(Exceptions::Exception e){

	}


	//ply_Current->AddComponent<SAMP_SDK::Component>();



	return true;
}
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	Debug::Log(__func__);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid)
{
	Debug::Log(__func__);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDeath(int playerid,int killerid, int reason)
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSpawn(int vehicleid)
{
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDeath(int playerid, int vehicleid)
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char* text) 
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char* text) 
{
	bool retVal = false;

	return retVal;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger) 
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid) 
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate) 
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid) 
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid)
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid)
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid)
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickMap(int playerid, float x, float y, float z) {
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconCommand(const char* command)
{
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestSpawn(int playerid) {
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnObjectMoved(int objectid) {
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerObjectMoved(int playerid, int objectid) {
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickupPickup(int playerid, int pickupid) {
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid) {
	
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid) {
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid) {
	return true;
}
PLUGIN_EXPORT bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z) {
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamIn(int playerid, int forplayerid) {
	return true;
}
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamOut(int playerid, int forplayerid) {
	return true;
}







PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char* inputtext) {
	
	return true;
}