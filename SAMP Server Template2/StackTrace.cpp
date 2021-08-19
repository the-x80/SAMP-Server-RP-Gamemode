
#include "StackTrace.h"
#include <DbgHelp.h>
#include <accctrl.h>
#include <aclapi.h>

#pragma comment(lib, "Dbghelp.lib")

//Developer note:
//Perform cleanup on every failure.
StackTrace::StackTrace()
{
#ifdef _DEBUG
	char cstr_DebugMessage[1024];
	memset(cstr_DebugMessage, 0, 1024);
	wsprintf(cstr_DebugMessage, "%s started.\n", __func__);
	OutputDebugString(cstr_DebugMessage);
#endif
	this->h_Process = GetCurrentProcess();
	this->h_Thread = GetCurrentThread();
	


	CONTEXT con_Context;
#ifdef _M_IX86
	ZeroMemory(&con_Context, sizeof(CONTEXT));

	con_Context.ContextFlags = CONTEXT_CONTROL;

	//
	// Those three registers are enough.
	//
	__asm
	{
	Label:
		mov[con_Context.Ebp], ebp;
		mov[con_Context.Esp], esp;
		mov eax, [Label];
		mov[con_Context.Eip], eax;
	}
#else
	RtlCaptureContext(&con_Context);
#endif
	STACKFRAME64 sf_StackFrame;
	DWORD dw_MachineType;


	ZeroMemory(&sf_StackFrame, sizeof(STACKFRAME64));
#ifdef _M_IX86
	dw_MachineType = IMAGE_FILE_MACHINE_I386;
	sf_StackFrame.AddrPC.Offset = con_Context.Eip;
	sf_StackFrame.AddrPC.Mode = AddrModeFlat;
	sf_StackFrame.AddrFrame.Offset = con_Context.Ebp;
	sf_StackFrame.AddrFrame.Mode = AddrModeFlat;
	sf_StackFrame.AddrStack.Offset = con_Context.Esp;
	sf_StackFrame.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
	dw_MachineType = IMAGE_FILE_MACHINE_AMD64;
	sf_StackFrame.AddrPC.Offset = con_Context.Rip;
	sf_StackFrame.AddrPC.Mode = AddrModeFlat;
	sf_StackFrame.AddrFrame.Offset = con_Context.Rsp;
	sf_StackFrame.AddrFrame.Mode = AddrModeFlat;
	sf_StackFrame.AddrStack.Offset = con_Context.Rsp;
	sf_StackFrame.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
	dw_MachineType = IMAGE_FILE_MACHINE_IA64;
	sf_StackFrame.AddrPC.Offset = con_Context.StIIP;
	sf_StackFrame.AddrPC.Mode = AddrModeFlat;
	sf_StackFrame.AddrFrame.Offset = con_Context.IntSp;
	sf_StackFrame.AddrFrame.Mode = AddrModeFlat;
	sf_StackFrame.AddrBStore.Offset = con_Context.RsBSP;
	sf_StackFrame.AddrBStore.Mode = AddrModeFlat;
	sf_StackFrame.AddrStack.Offset = con_Context.IntSp;
	sf_StackFrame.AddrStack.Mode = AddrModeFlat;
#else
#error "StackTrace::Unsupported platform"
#endif


	//EnterCriticalSection(&DbgHelpLock); Implement multithreading later
	SymInitialize(GetCurrentProcess(), NULL, TRUE);

	//Using for loop for more flexibility. Might be used in the future
	for (;;) {
		bool b_StackWalkResult = StackWalk64(dw_MachineType, GetCurrentProcess(),
			GetCurrentThread(), &sf_StackFrame, &con_Context, NULL, SymFunctionTableAccess64,
			SymGetModuleBase64, NULL);

		if (b_StackWalkResult == false) {//StackWalk failed.
			//This could happen if the end of the stack has been reached
			//Or it could be that some other error has occured.
			//GetLastError is not reliably set ba StackWalk64
			//So debbuging here is pointless.

			break;
		}


		if (sf_StackFrame.AddrPC.Offset != 0) {
			//Valid frame
			StackTraceEntry sf_Entry;
			sf_Entry.dw_Address = sf_StackFrame.AddrPC.Offset;

			

			this->a_StackWalkEntries.Add(sf_Entry);

#if _DEBUG
			char cstr_DebugMessage[1024];
			wsprintf(cstr_DebugMessage, "sf_StackFrame.AddrPC.Offset = 0x%p\n", (void*)sf_StackFrame.AddrPC.Offset);
			OutputDebugString(cstr_DebugMessage);
#endif

		}
		else {
			//Base of stack reached.
			break;
		}
	}

	SymCleanup(GetCurrentProcess());
	//LeaveCriticalSection( &DbgHelpLock );
}