#ifndef STACK_TRACE_H
#define STACK_TRACE_H

#ifdef _DEBUG
#define STACK_TRACE_DEBUG
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif
#ifndef ARRAY_H
#include "Array.h"
#endif


class StackTrace {
private:
protected:
	
public:
	HANDLE h_Process;
	HANDLE h_Thread;
	Array<DWORD64> a_StackWalkAddresses;

	StackTrace();

	bool GenerateStackTrace(CONTEXT* ctx, int skip);
};


#endif