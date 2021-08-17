#include <Windows.h>
#include "Thread.h"

Thread::Thread()
{
	this->lp_StartRoutine = nullptr;
	this->h_Thread = INVALID_HANDLE_VALUE;
}

Thread::Thread(LPTHREAD_START_ROUTINE lpRoutine)
{
	this->lp_StartRoutine = lpRoutine;
	this->h_Thread = INVALID_HANDLE_VALUE;
}

Thread::~Thread()
{
	this->Abort();
	CloseHandle(this->h_Thread);
}

void Thread::Start()
{
	this->h_Thread = CreateThread(NULL, 0, this->lp_StartRoutine, nullptr, CREATE_SUSPENDED, NULL);
}

void Thread::Abort()
{
	if (this->h_Thread == INVALID_HANDLE_VALUE) {
		return;
	}
	BOOL b_TerminateThreadResult = TerminateThread(this->h_Thread, 0);
	if (b_TerminateThreadResult == FALSE) {
		//You could throw an exception here.
	}
}

void Thread::Suspend()
{
}

void Thread::Resume()
{
}

Thread Thread::GetCurrent()
{
	Thread retVal;
	HANDLE h_Thread = GetCurrentThread();
	int n_DuplicateHandleResult = DuplicateHandle(GetCurrentProcess(), h_Thread, GetCurrentProcess(), &retVal.h_Thread, NULL, FALSE, DUPLICATE_SAME_ACCESS);
	return retVal;
}
