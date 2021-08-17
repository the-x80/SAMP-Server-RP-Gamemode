
#include "StackTrace.h"
#include <DbgHelp.h>
#include <accctrl.h>
#include <aclapi.h>

#pragma comment(lib, "Dbghelp.lib")


void GenerateStackTraceThread(StackTrace* st) {
#ifdef _DEBUG
	char cstr_DebugMessage[1024];
	memset(cstr_DebugMessage, 0, 1024);
	wsprintf(cstr_DebugMessage, "%s started.\n", __func__);
	OutputDebugString(cstr_DebugMessage);
#endif

#ifdef _DEBUG
	memset(cstr_DebugMessage, 0, 1024);
	wsprintf(cstr_DebugMessage, "Suspending thread 0x%p\n", st->h_Thread);
	OutputDebugString(cstr_DebugMessage);
#endif
	//Devloper note.
	//The thread doesent want to be suspended.
	//This is most likely to this threads security rights.
	//In the StackTrace constructor when you are creating a thread
	//Create it with elevated access.
	//See SECURITY_DESCRIPTOR documentation for more.
	SuspendThread(st->h_Thread);
	
	Sleep(1000);

#ifdef _DEBUG
	wsprintf(cstr_DebugMessage, "Getting thread context.\n");
	OutputDebugString(cstr_DebugMessage);
#endif
	CONTEXT* con_Context = new CONTEXT();

	SetLastError(0);
	BOOL b_GetThreadContextResult = GetThreadContext(st->h_Thread, con_Context);
	if (b_GetThreadContextResult == FALSE) {
#ifdef _DEBUG
		memset(cstr_DebugMessage, 0, 1024);
		wsprintf(cstr_DebugMessage, "Unable to get thread context.\n");
		OutputDebugString(cstr_DebugMessage);
#endif
		return;
	}
#ifdef _DEBUG
	wsprintf(cstr_DebugMessage, "Thread context retrieved. GetLastError = %d\n", GetLastError());
	OutputDebugString(cstr_DebugMessage);
#endif

	int n_GenStackTraceResult = st->GenerateStackTrace(con_Context, 0);
	if (n_GenStackTraceResult == false) {//Failed.
		OutputDebugString("Generating stack trace failed\n");
	}
	ResumeThread(st->h_Thread);
}

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
	HANDLE h_Thread = GetCurrentThread();
	
	BOOL b_DuplicateHandleResult = DuplicateHandle(this->h_Process, h_Thread, this->h_Process, &this->h_Thread, 0, FALSE, DUPLICATE_SAME_ACCESS);
	if (b_DuplicateHandleResult == FALSE) {
#ifdef _DEBUG
		memset(cstr_DebugMessage, 0, 1024);
		wsprintf(cstr_DebugMessage, "Duplicating handle failed. GetLastError = %d.\n", GetLastError());
		OutputDebugString(cstr_DebugMessage);
#endif
	}
#ifdef _DEBUG
	memset(cstr_DebugMessage, 0, 1024);
	wsprintf(cstr_DebugMessage, "Thread duplicated from 0x%p to 0x%p.\n", h_Thread, this->h_Thread);
	OutputDebugString(cstr_DebugMessage);
#endif

	SetLastError(0);
	PSID sid_Admin = NULL;
	EXPLICIT_ACCESS ea;
	PSECURITY_DESCRIPTOR sec_Descriptor = NULL;

	SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
	if (!AllocateAndInitializeSid(&SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0, &sid_Admin)) {
#ifdef _DEBUG
		memset(cstr_DebugMessage, 0, 1024);
		wsprintf(cstr_DebugMessage, "Failed to allocate and initialize SID. GetLastError = %d\n", GetLastError());
		OutputDebugString(cstr_DebugMessage);
#endif
	}

	//Filling out the explicit access structure
	ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
	ea.grfAccessPermissions = KEY_ALL_ACCESS;
	ea.grfAccessMode = SET_ACCESS;
	ea.grfInheritance = NO_INHERITANCE;
	ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea.Trustee.TrusteeType = TRUSTEE_IS_GROUP;
	ea.Trustee.ptstrName = (LPTSTR)sid_Admin;


	PACL p_ACL = NULL;
	int n_SetACLResult = SetEntriesInAcl(1, &ea, NULL, &p_ACL);
	if (n_SetACLResult != ERROR_SUCCESS) {
#ifdef _DEBUG
		memset(cstr_DebugMessage, 0, 1024);
		wsprintf(cstr_DebugMessage, "Failed to set entries in ALC. GetLastError = %d\n", GetLastError());
		OutputDebugString(cstr_DebugMessage);
#endif
	}

	sec_Descriptor = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	if (sec_Descriptor == NULL) {
#ifdef _DEBUG
		memset(cstr_DebugMessage, 0, 1024);
		wsprintf(cstr_DebugMessage, "Failed to allocate space for security descriptor. GetLastError = %d\n", GetLastError());
		OutputDebugString(cstr_DebugMessage);
#endif
	}


	int n_InitSecDescResult = InitializeSecurityDescriptor(sec_Descriptor, SECURITY_DESCRIPTOR_REVISION);
	if (n_InitSecDescResult == 0) {
#ifdef _DEBUG
		memset(cstr_DebugMessage, 0, 1024);
		wsprintf(cstr_DebugMessage, "Failed to initialize Security Descriptor. GetLastError = %d\n", GetLastError());
		OutputDebugString(cstr_DebugMessage);
#endif
		return;
	}


	if (!SetSecurityDescriptorDacl(sec_Descriptor, true, p_ACL, false)) {
#ifdef _DEBUG
		memset(cstr_DebugMessage, 0, 1024);
		wsprintf(cstr_DebugMessage, "Failed to set security descriptor DACL. GetLastError = %d\n", GetLastError());
		OutputDebugString(cstr_DebugMessage);
#endif
	}


	SECURITY_ATTRIBUTES sec_Attributes = { 0 };

	sec_Attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	sec_Attributes.lpSecurityDescriptor = sec_Descriptor;
	sec_Attributes.bInheritHandle = false;


#ifdef _DEBUG
	memset(cstr_DebugMessage, 0, 1024);
	wsprintf(cstr_DebugMessage, "Creating worker thread.\n");
	OutputDebugString(cstr_DebugMessage);
#endif
	HANDLE h_StackTraceThread = CreateThread(&sec_Attributes, 0, (LPTHREAD_START_ROUTINE)GenerateStackTraceThread, this, CREATE_SUSPENDED, 0);
	if (h_StackTraceThread == NULL) {
#ifdef _DEBUG
		memset(cstr_DebugMessage, 0, 1024);
		wsprintf(cstr_DebugMessage, "Unable to CreateThread. GetLastError = %d.\n", GetLastError());
		OutputDebugString(cstr_DebugMessage);
#endif
		return;
	}
	ResumeThread(h_StackTraceThread);
	Sleep(3000);
}

bool StackTrace::GenerateStackTrace(CONTEXT* ctx, int skip)
{
#ifdef _DEBUG
	char cstr_DebugMessage[1024];
	memset(cstr_DebugMessage, 0, 1024);
	wsprintf(cstr_DebugMessage, "%s started.\n", __func__);
	OutputDebugString(cstr_DebugMessage);
#endif
	STACKFRAME64 sf = {};

	HANDLE process = GetCurrentProcess();
	HANDLE thread = GetCurrentThread();

#if defined(_M_IX86) || defined(_M_X64)
#ifdef _M_X64
	sf.AddrPC.Offset = ctx->Rip;
	sf.AddrFrame.Offset = ctx->Rbp;
	sf.AddrStack.Offset = ctx->Rsp;
#else
	sf.AddrPC.Offset = ctx->Eip;
	sf.AddrFrame.Offset = ctx->Ebp;
	sf.AddrStack.Offset = ctx->Esp;
#endif
#ifdef _M_X64
	int n_Machine = IMAGE_FILE_MACHINE_AMD64;
#else
	int n_Machine = IMAGE_FILE_MACHINE_I386;
#endif
#endif

	for (int i=0;;i++)
	{
#ifdef _DEBUG
		memset(cstr_DebugMessage, 0, 1024);
		wsprintf(cstr_DebugMessage, "Reading stack at index %d\nsf.AddrPC.Offset= %d\nsf.AddrFrame.Offset = %d\nsf.AddrStack.Offset = %d\n", i, sf.AddrPC.Offset, sf.AddrFrame.Offset, sf.AddrStack.Offset);
		OutputDebugString(cstr_DebugMessage);
#endif


		SetLastError(0);
		BOOL stack_walk_ok = StackWalk64(n_Machine, process, thread, &sf,
			ctx, 0, &SymFunctionTableAccess64,
			&SymGetModuleBase64, 0);
		if (GetLastError() != 0) {
#ifdef _DEBUG
			memset(cstr_DebugMessage, 0, 1024);
			wsprintf(cstr_DebugMessage, "StackWalk function failed. GetLastError = %d\n", GetLastError());
			OutputDebugString(cstr_DebugMessage);
#endif
			return false;
		}

		if (!stack_walk_ok || !sf.AddrFrame.Offset) break;

		if (skip)
		{
			--skip;
		}
		else
		{
			// write the address
			a_StackWalkAddresses.Add(sf.AddrPC.Offset);
		}
	}
	return true;
}
