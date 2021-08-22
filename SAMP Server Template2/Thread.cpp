#include <Windows.h>
#include "Debug.h"
#include "Thread.h"









Thread::Thread()
{
	this->lp_StartRoutine = nullptr;
	this->h_Thread = INVALID_HANDLE_VALUE;
	this->b_IsSuspended = false;
	this->b_IsAlive = false;
	this->n_SuspendCount = 0;

	this->ts_State = ThreadState::Unstarted;
}

Thread::Thread(LPTHREAD_START_ROUTINE lpRoutine)
{
	this->lp_StartRoutine = lpRoutine;
	this->h_Thread = INVALID_HANDLE_VALUE;
	this->b_IsSuspended = true;
	this->n_SuspendCount = 0;
	this->b_IsAlive = false;

	this->ts_State = ThreadState::Unstarted;
}

Thread::~Thread()
{
	this->Abort();
}

void Thread::Start()
{
	if (this->b_IsAlive == true) {
		Debug::Throw(new Exceptions::ThreadStateException());
	}
	this->h_Thread = CreateThread(NULL, 0, this->lp_StartRoutine, nullptr, CREATE_SUSPENDED, NULL);
	if (this->h_Thread == NULL) {
		Debug::Throw(new Exceptions::OutOfMemoryException());
		return;
	}

	ResumeThread(this->h_Thread);
	this->ts_State = ThreadState::Running;
}

void Thread::Start(void* param)
{
	if (this->b_IsAlive == true) {
		Debug::Throw(new Exceptions::ThreadStateException());
	}
	this->h_Thread = CreateThread(NULL, 0, this->lp_StartRoutine, param, CREATE_SUSPENDED, NULL);
	if (this->h_Thread == NULL) {
		Debug::Throw(new Exceptions::OutOfMemoryException());
		return;
	}

	ResumeThread(this->h_Thread);
	this->ts_State = ThreadState::Running;
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
	CloseHandle(this->h_Thread);
	this->h_Thread = NULL;
}

//Suspend is still WIP. There is no check for security descriptor information to see if the thread can be suspended.
//Thread must have THREAD_SUSPEND_RESUME security access to be suspended.
bool Thread::Suspend()
{
	int n_SuspendResult = SuspendThread(this->h_Thread);
	if (n_SuspendResult == -1) {//Some error has occured.
		
#ifdef _DEBUG

#endif
		
		switch (GetLastError()) {
		default:
			break;
		}

		return false;
	}
	this->n_SuspendCount = n_SuspendResult;
	this->b_IsSuspended = true;
	return true;
}

bool Thread::Resume()
{
	if (this->b_IsSuspended == false) {//This might be redundant.
		Debug::Throw(new Exceptions::ThreadNotSuspendedException());
	}

	int n_ResumeResult = ResumeThread(this->h_Thread);
	if (n_ResumeResult == -1) {//An error occured

#ifdef _DEBUG

#endif

		switch (GetLastError()) {
		default:
			break;
		}
		return false;
	}

	this->b_IsSuspended = false;
	return true;
}

bool Thread::IsSuspended()
{
	return b_IsSuspended;
}

bool Thread::IsAlive()
{
	return this->b_IsAlive;
}

CONTEXT Thread::GetContext()
{
	if (b_IsSuspended == false) {
		Debug::Throw(new Exceptions::ThreadNotSuspendedException());
	}
	CONTEXT retVal = { 0 };
	ZeroMemory(&retVal, sizeof(retVal));

	return retVal;
}

Thread Thread::GetCurrent()
{
	Thread retVal;
	HANDLE h_Thread = GetCurrentThread();
	int n_DuplicateHandleResult = DuplicateHandle(GetCurrentProcess(), h_Thread, GetCurrentProcess(), &retVal.h_Thread, NULL, FALSE, DUPLICATE_SAME_ACCESS);
	return retVal;
}








namespace Exceptions {
	ThreadException::ThreadException()
	{
		this->t_Current = Thread::GetCurrent();
	}
}
