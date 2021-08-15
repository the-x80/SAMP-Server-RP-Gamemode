#include "StackTrace.h"
#include <Windows.h>
#include <DbgHelp.h>

#pragma comment(lib, "Dbghelp.lib")



//Developer note:
//Perform cleanup on every failure.
StackTrace::StackTrace()
{
	HANDLE h_Process = GetCurrentProcess();
	HANDLE h_Thread = GetCurrentThread();
	char* cstr_SymbolLocation = new char[MAX_PATH];
	STACKFRAME64 sf_StackFrame = { 0 };
	CONTEXT con_Context = { 0 };



	ZeroMemory(cstr_SymbolLocation, sizeof(char) * MAX_PATH);
	GetCurrentDirectory(MAX_PATH, cstr_SymbolLocation);


	BOOL b_SymInitResult = SymInitialize(h_Process, cstr_SymbolLocation, false);
	if (b_SymInitResult == false) {
		
	}




	GetThreadContext(h_Thread, &con_Context);

	BOOL b_StackWalkResult = FALSE;
	int n_StackWalkDepth = 0;
	do {
		b_StackWalkResult = StackWalk(IMAGE_FILE_MACHINE_I386,
			h_Process, h_Thread, (LPSTACKFRAME)&sf_StackFrame, &con_Context, NULL,
			(PFUNCTION_TABLE_ACCESS_ROUTINE)&SymFunctionTableAccess64,
			(PGET_MODULE_BASE_ROUTINE)&SymGetModuleBase64, NULL);

		int n_NameLength = 256;
		int n_SymbolInfoSize = n_NameLength - 1 + sizeof(SYMBOL_INFO);
		SYMBOL_INFO* si_Info = (SYMBOL_INFO*)calloc(1, n_SymbolInfoSize);
		if (si_Info == nullptr) {

			return;
		}
		si_Info->SizeOfStruct = sizeof(SYMBOL_INFO);
		si_Info->MaxNameLen = n_NameLength;

		BOOL b_SymFromAddrResult = SymFromAddr(h_Process, sf_StackFrame.AddrPC.Offset, 0, si_Info);
		if (b_SymFromAddrResult == FALSE) {

			return;
		}

		
		free(si_Info);


		if (sf_StackFrame.AddrPC.Offset == 0) {
			break;
		}
		n_StackWalkDepth++;
	} while (b_StackWalkResult);



	
	BOOL b_SymCleanResult = SymCleanup(h_Process);
	if (b_SymCleanResult == FALSE) {
		
	}
}
