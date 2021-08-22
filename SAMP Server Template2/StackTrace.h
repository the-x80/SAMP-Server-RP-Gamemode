#ifndef STACK_TRACE_H
#define STACK_TRACE_H

#ifdef _DEBUG
//#define STACK_TRACE_DEBUG
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif
#ifndef ARRAY_H
#include "Array.h"
#endif

class StackTraceEntry {
public:
	DWORD64 dw_Address;
	DebugMethodInfo* dmi_Method;
};
class StackTrace {
private:
protected:
	
public:
	HANDLE h_Process;
	HANDLE h_Thread;
	Array<StackTraceEntry> a_StackWalkEntries;

	StackTrace();
	StackTrace(int n_Skip);

	void GenerateStackTrace(int n_Skip);
};


#endif