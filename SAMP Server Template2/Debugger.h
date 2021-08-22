#ifndef DEBUGGER_H
#define DEBUGGER_H

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifdef _DEBUG
//#define DEBUGGER_DEBUG
#endif

namespace Debugging {
	class Debugger {
	private:
		bool b_IsAttached;
		DWORD dw_ProcessId;
		Thread t_MainThread;
	public:

		Debugger();//Attaches a debugger to this process.
		Debugger(DWORD dw_ProcessId);//Attaches a debugger to another process.

		void Start();
		void Stop(bool b_KillProcess);

		bool IsDebugged();

		bool EnableDebugPrivileges();

		//Used as a wrapper for the windows WaitForDebugEvent.
		//Purely for scalability reasons. Might introduce new functionality into it.
		bool WaitForDebugEvent(LPDEBUG_EVENT Event, int dw_Milliseconds);
	};

	namespace Exceptions {
		class TargetProcessNotFound : public ::Exceptions::Exception {

		};
	}
}

#endif