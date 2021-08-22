#include "Framework.h"
#include "sampgdk.h"
#include "SAMP SDK.h"

#pragma region Plugin callbacks
//Native functions
extern void* pAMXFunctions;

cell AMX_NATIVE_CALL HelloWorld(AMX* amx, cell* params)
{

	return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

Debugging::Debugger* debugger;
PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{

	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];

	//ToDo:
	//Perform startup sanity checks
	//Perform file system sanity check
	//Create a server GUI Winodw
	//Create a server debug window if debug build is specified.
	//Create a server for maintanence
	//Perform settings file operations
	//Perform file structure sanity check

	debugger = new Debugging::Debugger();
	debugger->Start();
	return sampgdk::Load(ppData);
}
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	
	sampgdk::Unload();
	debugger->Stop(false);
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "HelloWorld", HelloWorld },
{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
	return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{

	return AMX_ERR_NONE;
}


//Be carefull with the process tick method.
//Overloading this might induce a freeze.
//Try and design an anti freeze option to the server
PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
#ifdef _DEBUG

#endif
	sampgdk::ProcessTick();


#ifdef _DEBUG

#endif
}

#pragma endregion

