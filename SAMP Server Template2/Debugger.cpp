
#include "Framework.h"//Basically this is included entirelly because it will be needed. All of it mostly.
#include "Debugger.h"

void DebuggerMainLoop(Debugging::Debugger* debugger) {
#ifdef DEBUGGER_DEBUG
    char cstr_DebugMessage[1024];
    wsprintf(cstr_DebugMessage, "Debugger thread started.\n");
    OutputDebugString(cstr_DebugMessage);
#endif
	if (debugger == nullptr) {
		return;
	}

	while (true) {
#ifdef DEBUGGER_DEBUG
        wsprintf(cstr_DebugMessage, "Waiting for debug event.\n");
        Debug::Log(cstr_DebugMessage);
#endif
        SetLastError(0);
        DEBUG_EVENT dbg_Event = { 0 };
        if (debugger->WaitForDebugEvent(&dbg_Event, INFINITE) == FALSE) {
#ifdef DEBUGGER_DEBUG
            wsprintf(cstr_DebugMessage, "WaitForDebugEvent failed. GetLastError returned %d\n", GetLastError());
            Debug::Log(cstr_DebugMessage);
#endif
            break;
        }

		switch (dbg_Event.dwDebugEventCode) {
		case EXCEPTION_DEBUG_EVENT:
            Debug::Log("Exception recieved.\n");
			break;
        case CREATE_THREAD_DEBUG_EVENT:
            // As needed, examine or change the thread's registers 
            // with the GetThreadContext and SetThreadContext functions; 
            // and suspend and resume thread execution with the 
            // SuspendThread and ResumeThread functions. 
#ifdef DEBUGGER_DEBUG
            wsprintf(cstr_DebugMessage, "CREATE_THREAD_DEBUG_EVENT\n");
            Debug::Log(cstr_DebugMessage);
#endif
            
            break;

        case CREATE_PROCESS_DEBUG_EVENT:
            // As needed, examine or change the registers of the
            // process's initial thread with the GetThreadContext and
            // SetThreadContext functions; read from and write to the
            // process's virtual memory with the ReadProcessMemory and
            // WriteProcessMemory functions; and suspend and resume
            // thread execution with the SuspendThread and ResumeThread
            // functions. Be sure to close the handle to the process image
            // file with CloseHandle.
#ifdef DEBUGGER_DEBUG
            wsprintf(cstr_DebugMessage, "CREATE_PROCESS_DEBUG_EVENT\n");
            Debug::Log(cstr_DebugMessage);
#endif
            
            break;

        case EXIT_THREAD_DEBUG_EVENT:
            // Display the thread's exit code. 
#ifdef DEBUGGER_DEBUG
            wsprintf(cstr_DebugMessage, "EXIT_THREAD_DEBUG_EVENT\n");
            Debug::Log(cstr_DebugMessage);
#endif
            
            break;

        case EXIT_PROCESS_DEBUG_EVENT:
            // Display the process's exit code. 
#ifdef DEBUGGER_DEBUG
            wsprintf(cstr_DebugMessage, "EXIT_PROCESS_DEBUG_EVENT\n");
            Debug::Log(cstr_DebugMessage);
#endif
            
            break;

        case LOAD_DLL_DEBUG_EVENT:
            // Read the debugging information included in the newly 
            // loaded DLL. Be sure to close the handle to the loaded DLL 
            // with CloseHandle.
#ifdef DEBUGGER_DEBUG
            wsprintf(cstr_DebugMessage, "LOAD_DLL_DEBUG_EVENT\n");
            Debug::Log(cstr_DebugMessage);
#endif
            
            break;

        case UNLOAD_DLL_DEBUG_EVENT:
            // Display a message that the DLL has been unloaded. 
#ifdef DEBUGGER_DEBUG
            wsprintf(cstr_DebugMessage, "UNLOAD_DLL_DEBUG_EVENT\n");
            Debug::Log(cstr_DebugMessage);
#endif
            
            break;

        case OUTPUT_DEBUG_STRING_EVENT:
            // Display the output debugging string. 
#ifdef DEBUGGER_DEBUG
            wsprintf(cstr_DebugMessage, "OUTPUT_DEBUG_STRING_EVENT\n");
            Debug::Log(cstr_DebugMessage);
#endif
            
            break;

        case RIP_EVENT:
#ifdef DEBUGGER_DEBUG
            wsprintf(cstr_DebugMessage, "RIP_EVENT\n");
            OutputDebugString(cstr_DebugMessage);
#endif
            break;
		}

		ContinueDebugEvent(dbg_Event.dwProcessId, dbg_Event.dwThreadId, DBG_CONTINUE);
	}
}

Debugging::Debugger::Debugger()
{
	//throw new ::Exceptions::NotImplementedException();
	this->dw_ProcessId = GetCurrentProcessId();
	this->b_IsAttached = false;
    this->h_Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->dw_ProcessId);
}

Debugging::Debugger::Debugger(DWORD dw_ProcessId)
{
	this->dw_ProcessId = dw_ProcessId;
	this->b_IsAttached = false;
    this->h_Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->dw_ProcessId);
}

Debugging::Debugger::~Debugger()
{
    CloseHandle(this->h_Process);
}

void Debugging::Debugger::Start()
{
#ifdef DEBUGGER_DEBUG
	char cstr_DebugMessage[1024];
	wsprintf(cstr_DebugMessage, "Starting debugger.\n");
	Debug::Log(cstr_DebugMessage);
#endif

    if (IsDebuggerPresent() == TRUE) {
#ifdef DEBUGGER_DEBUG
        wsprintf(cstr_DebugMessage, "Debugger is already attached to this process.\n");
        Debug::Log(cstr_DebugMessage);
#endif
        return;
    }
	
    if (this->SetDebugPrivilege(true) == FALSE) {
#ifdef DEBUGGER_DEBUG
        wsprintf(cstr_DebugMessage, "Unable to EnableDebugPriveleges.\n");
        Debug::Log(cstr_DebugMessage);
#endif
    }
    else {
#ifdef DEBUGGER_DEBUG
        wsprintf(cstr_DebugMessage, "Debug privileges granted.\n");
        Debug::Log(cstr_DebugMessage);
#endif
    }

	SetLastError(0);
	bool b_DebugActiveProcessResult = DebugActiveProcess(this->dw_ProcessId);
	if (b_DebugActiveProcessResult == false) {
#ifdef DEBUGGER_DEBUG
		wsprintf(cstr_DebugMessage, "Something went wrong while calling DebugActiveProcess(%d). GetLastError returned %d\n", this->dw_ProcessId, GetLastError());
        Debug::Log(cstr_DebugMessage);
#endif
		return;
	}




    this->t_MainThread = Thread((LPTHREAD_START_ROUTINE)DebuggerMainLoop);
    this->t_MainThread.Start(this);

	OutputDebugString("Debugger started.\n");
	this->b_IsAttached = true;
}

void Debugging::Debugger::Stop(bool b_KillProcess)
{
	DebugSetProcessKillOnExit(b_KillProcess);
	DebugActiveProcessStop(this->dw_ProcessId);
	this->b_IsAttached = false;
}

bool Debugging::Debugger::IsDebugged()
{
    return IsDebuggerPresent();
}

bool Debugging::Debugger::EnableDebugPrivileges()
{
#ifdef DEBUGGER_DEBUG
    char cstr_DebugMessage[1024];
    wsprintf(cstr_DebugMessage, "%s called.\n", __func__);
    Debug::Log(cstr_DebugMessage);
#endif
    HANDLE pToken = NULL;
    TOKEN_PRIVILEGES pTokenPrivileges;
    LUID luid;

    OpenProcessToken(this->h_Process, TOKEN_ALL_ACCESS, &pToken);

    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) { 
#ifdef DEBUGGER_DEBUG
        wsprintf(cstr_DebugMessage, "LoolupPrivilegeValue failed. GetLastError returned %d.\n", GetLastError());
        Debug::Log(cstr_DebugMessage);
#endif
        return FALSE; 
    }

    pTokenPrivileges.PrivilegeCount = 1;
    pTokenPrivileges.Privileges[0].Luid = luid;
    pTokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(pToken, FALSE, &pTokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) { 
#ifdef DEBUGGER_DEBUG
        wsprintf(cstr_DebugMessage, "AdjustTokenPrivileges failed. GetLastError returned %d.\n", GetLastError());
        Debug::Log(cstr_DebugMessage);
#endif
        return FALSE; 
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) { 
#ifdef DEBUGGER_DEBUG
        wsprintf(cstr_DebugMessage, "ERROR_NOT_ALL_ASSIGNED(%d)\n", GetLastError());
        Debug::Log(cstr_DebugMessage);
#endif
        return FALSE; 
    }

    return TRUE;
}

bool Debugging::Debugger::SetDebugPrivilege(bool state)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES token_privileges;
    DWORD dwSize;

    ZeroMemory(&token_privileges, sizeof(token_privileges));
    token_privileges.PrivilegeCount = 1;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
        return FALSE;

    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &token_privileges.Privileges[0].Luid))
    {
        CloseHandle(hToken);
        return FALSE;
    }

    if (state)
        token_privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    else
        token_privileges.Privileges[0].Attributes = SE_PRIVILEGE_REMOVED;

    if (!AdjustTokenPrivileges(hToken, FALSE, &token_privileges, 0, NULL, &dwSize))
    {
        CloseHandle(hToken);
        return FALSE;
    }

    return CloseHandle(hToken);
}

bool Debugging::Debugger::WaitForDebugEvent(LPDEBUG_EVENT Event, int dw_Milliseconds)
{
	return ::WaitForDebugEvent(Event, dw_Milliseconds);
}
