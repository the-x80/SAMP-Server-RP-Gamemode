#define _CRT_SECURE_NO_WARNINGS

#include <string>

#pragma comment(lib, "Dbghelp.lib")

#include "Exceptions.h"
#include "MethodInfo.h"

MethodInfo::MethodInfo()
{
	this->cstr_MethodName = nullptr;
	this->n_ParameterCount = 0;
	this->a_ParameterTypes = nullptr;
	this->ti_ReturnType = nullptr;
	this->m_Module = nullptr;
}

MethodInfo::MethodInfo(DWORD64 dw_Address, bool b_InitializeSymbols)
{
#ifdef _DEBUG
	char cstr_DebugMessage[1024];
	ZeroMemory(cstr_DebugMessage, 1024 * sizeof(char));
#endif

	this->cstr_MethodName = nullptr;
	this->n_ParameterCount = 0;
	this->a_ParameterTypes = nullptr;
	this->ti_ReturnType = nullptr;
	this->m_Module = nullptr;



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
		sprintf(cstr_DebugMessage, "Retrieving symbol from address 0x%p failed. GetLastError returned %d\n", (void*)dw_Address, GetLastError());
		OutputDebugString(cstr_DebugMessage);
#endif
		switch (GetLastError()) {
		case ERROR_MOD_NOT_FOUND:
#ifdef _DEBUG
			sprintf(cstr_DebugMessage, "The specified module could not be found.\n");
			OutputDebugString(cstr_DebugMessage);
#endif
			break;
		case ERROR_INVALID_ADDRESS:
#ifdef _DEBUG
			sprintf(cstr_DebugMessage, "Attempt to access invalid address.\n");
			OutputDebugString(cstr_DebugMessage);
#endif
			break;
		}
	}

	/*
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
	*/
	this->cstr_MethodName = new char[si_Info->NameLen + 1];
	memset(this->cstr_MethodName, 0, (si_Info->NameLen + 1) * sizeof(char));
	strcpy(this->cstr_MethodName, si_Info->Name);
	free(si_Info);
#pragma endregion







	if (b_InitializeSymbols) {
		SymCleanup(GetCurrentProcess());
	}
}

MethodInfo::MethodInfo(SYMBOL_INFO* si_Info)
{
	this->cstr_MethodName = nullptr;
	this->n_ParameterCount = 0;
	this->a_ParameterTypes = nullptr;
	this->ti_ReturnType = nullptr;
	this->m_Module = nullptr;


	try {
		this->cstr_MethodName = new char[si_Info->NameLen + 1];
	}
	catch (std::bad_alloc e) {
		throw new ::Exceptions::BadAllocationException();
		return;
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
	this->a_ParameterTypes = nullptr;
	this->ti_ReturnType = nullptr;
	this->m_Module = nullptr;
	this->cstr_SourceFileDirectory = nullptr;
	this->cstr_SourceFileName = nullptr;
	this->n_SourceFileLineNumber = 0;
}

DebugMethodInfo::DebugMethodInfo(DWORD64 dw_Address, bool b_InitializeSymbols) :
	MethodInfo::MethodInfo(dw_Address, b_InitializeSymbols)
{
	this->a_ParameterTypes = nullptr;
	this->ti_ReturnType = nullptr;
	this->m_Module = nullptr;
	this->cstr_SourceFileDirectory = nullptr;
	this->cstr_SourceFileName = nullptr;
	this->n_SourceFileLineNumber = 0;
}

DebugMethodInfo::DebugMethodInfo(SYMBOL_INFO* si_Info) : MethodInfo::MethodInfo(si_Info)
{
	this->a_ParameterTypes = nullptr;
	this->ti_ReturnType = nullptr;
	this->m_Module = nullptr;
	this->cstr_SourceFileDirectory = nullptr;
	this->cstr_SourceFileName = nullptr;
	this->n_SourceFileLineNumber = 0;


	this->cstr_MethodName = new char[si_Info->NameLen + 1];
	strcpy(this->cstr_MethodName, si_Info->Name);
}

DebugMethodInfo::~DebugMethodInfo()
{
}


