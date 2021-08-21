#include <Windows.h>
#include <DbgHelp.h>
#include "SymbolHelper.h"

#pragma comment(lib, "Dbghelp.lib")

void DebugSymbolHelper::Initialize()
{
	HANDLE h_Process = GetCurrentProcess();

	SetLastError(0);
	bool b_SymInitResult = SymInitialize(h_Process, NULL, TRUE);
	if (b_SymInitResult == FALSE) {
		//Some error has occured.
		//See GetLastError for more information
		throw new Exceptions::SymInitializationException();
	}

	DebugSymbolHelper::b_IsInitialized = true;
	return;
}

void DebugSymbolHelper::Cleanup()
{
	HANDLE h_Process = GetCurrentProcess();
	SymCleanup(h_Process);
	DebugSymbolHelper::b_IsInitialized = false;
}
