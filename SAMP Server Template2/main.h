#pragma warning(disable: 4793)

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS


//Theese are debug switches.
//Used when the app is running outside the IDE or debug program
//
#ifdef _DEBUG

#define _DEBUG_SAMP_CALLBACKS



#ifdef _DEBUG_SAMP_CALLBACKS

#define _DEBUG_ON_GAMEMODE_INIT
#define _DEBUG_ON_PLAYER_CONNECT
#define _DEBUG_ON_PLAYER_DISCONNECT

#endif

#endif

/*
#include <Windows.h>
#include "Shlwapi.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>

#pragma comment(lib, "Shlwapi.lib")
*/
#include "Framework.h"
#include "SAMP SDK.h"

#define MAX_PLAYER_COUNT 1000 //Its not really used but its nice to limit he number of players anyways for compatibility reasons
#define MAX_VEHICLE_COUNT 1000
#define MAX_ACTOR_COUNT 1000
#define MAX_NPC_COUNT 1000

#define SCRIPTFILES_DIRECTORY "scriptfiles\\"
#define GAMEMODE_DIRECTORY "gamemode\\"






