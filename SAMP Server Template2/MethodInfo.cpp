#define _CRT_SECURE_NO_WARNINGS

#include <string>

#pragma comment(lib, "Dbghelp.lib")

#include "Exceptions.h"
#include "MethodInfo.h"

MethodInfo::MethodInfo()
{
	this->cstr_MethodName = nullptr;
}

MethodInfo::MethodInfo(SYMBOL_INFO* si_Info)
{
	try {
		this->cstr_MethodName = new char[si_Info->NameLen + 1];
	}
	catch (std::bad_alloc e) {
		throw new ::Exceptions::BadAllocationException();
	}
	memset(cstr_MethodName, 0, si_Info->NameLen + 1);
	strcpy(cstr_MethodName, si_Info->Name);
}

MethodInfo::~MethodInfo()
{
	if (this->cstr_MethodName != nullptr) {
		delete[] this->cstr_MethodName;
		this->cstr_MethodName = nullptr;
	}
}

DebugMethodInfo::DebugMethodInfo()
{
	this->cstr_MethodName = nullptr;
	this->a_ParameterTypes = nullptr;
	this->cstr_SourceFileDirectory = nullptr;
	this->cstr_SourceFileName = nullptr;
}

DebugMethodInfo::DebugMethodInfo(long dw_Address, bool b_InitializeSymbols)
{
#ifdef _DEBUG
	char cstr_DebugMessage[1024];
	ZeroMemory(cstr_DebugMessage, 1024 * sizeof(char));
#endif

	HANDLE h_Process = GetCurrentProcess();







	if (b_InitializeSymbols) {
		SetLastError(0);
		BOOL b_SymInitResult = SymInitialize(h_Process, NULL, TRUE);
		if (b_SymInitResult == FALSE) {
#ifdef _DEBUG
			sprintf(cstr_DebugMessage, "Symbol initialization failed. GetLastError returned %d\n", GetLastError());
			OutputDebugString(cstr_DebugMessage);
#endif
		}

	}

#pragma region Get Method Name From Address
	SYMBOL_INFO* si_Info;
	si_Info = (SYMBOL_INFO*)malloc(sizeof(si_Info) + 256);
	if (si_Info == nullptr) {
		SymCleanup(GetCurrentProcess());
		return;
	}
	ZeroMemory(si_Info, sizeof(si_Info) + 256);
	si_Info->SizeOfStruct = sizeof(SYMBOL_INFO);
	si_Info->MaxNameLen = 255;
	DWORD64 dw_Displacement;

	SetLastError(0);
	bool b_SymFromAddeResult = SymFromAddr(h_Process, dw_Address, &dw_Displacement, si_Info);
	if (b_SymFromAddeResult == FALSE) {
#ifdef _DEBUG
		sprintf(cstr_DebugMessage, "Retrieving symbol from address failed. GetLastError returned %d\n", GetLastError());
		OutputDebugString(cstr_DebugMessage);
#endif
	}

	if ((si_Info->Flags & SYMFLAG_FUNCTION) == 0) {
#ifdef _DEBUG
		sprintf(cstr_DebugMessage, "Selected address is not a function\n");
		OutputDebugString(cstr_DebugMessage);
#endif
		free(si_Info);
		if (b_InitializeSymbols) {
			SymCleanup(GetCurrentProcess());
		}
		return;
	}


	this->cstr_MethodName = new char[si_Info->NameLen + 1];
	strcpy(this->cstr_MethodName, si_Info->Name);
#pragma endregion







	if (b_InitializeSymbols) {
		SymCleanup(GetCurrentProcess());
	}
}

DebugMethodInfo::DebugMethodInfo(SYMBOL_INFO* si_Info) : MethodInfo::MethodInfo(si_Info)
{
}

DebugMethodInfo::~DebugMethodInfo()
{
}


