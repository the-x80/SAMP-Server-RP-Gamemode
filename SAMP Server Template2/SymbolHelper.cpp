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
	SetLastError(0);
	SymCleanup(h_Process);
	DebugSymbolHelper::b_IsInitialized = false;
}

SYMBOL_INFO* DebugSymbolHelper::GetSymInfoFromAddr(DWORD64 dw_Address)
{
	HANDLE h_Process = GetCurrentProcess();
	SYMBOL_INFO* si_Info;
	si_Info = (SYMBOL_INFO*)malloc(sizeof(si_Info) + 256);
	if (si_Info == nullptr) {
		throw new ::Exceptions::BadAllocationException();
		return nullptr;
	}
	ZeroMemory(si_Info, sizeof(si_Info) + 256);
	si_Info->SizeOfStruct = sizeof(SYMBOL_INFO);
	si_Info->MaxNameLen = 255;
	DWORD64 dw_Displacement;

	bool b_SymFrimAddeResult = SymFromAddr(h_Process, dw_Address, &dw_Displacement, si_Info);
	if (b_SymFrimAddeResult == FALSE) {
		//Something broke. Debug it.

		return nullptr;
	}
	return si_Info;
}

DebugMethodInfo* DebugSymbolHelper::GetDebugMethodInfoFromAddress(DWORD64 dw_Address)
{
	SYMBOL_INFO* si_Info = nullptr;
	try {
		si_Info = DebugSymbolHelper::GetSymInfoFromAddr(dw_Address);
	}
	catch (::Exceptions::BadAllocationException* e) {
		throw e;
	}
	//Sucsess. Fill out a DebugMethodInfo structure
	DebugMethodInfo* retVal = nullptr;
	try {
		retVal = new DebugMethodInfo(si_Info);
	}catch(std::bad_alloc){
		throw new ::Exceptions::BadAllocationException();
	}
	free(si_Info);

	return retVal;
}

bool DebugSymbolHelper::GetMethodNameFromAddress(DWORD64 dw_Address, char* cstr_Name)
{
	if (cstr_Name == nullptr) {
		throw new ::Exceptions::ArgumentNullException();
	}


	return false;
}
