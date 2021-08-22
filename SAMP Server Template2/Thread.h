#ifndef THREAD_H
#define THREAD_H

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif




enum class ThreadState {
	Stopped,
	Running,
	Suspended,
	Unstarted
};

class Thread
{
private:
	HANDLE h_Thread;
	LPTHREAD_START_ROUTINE lp_StartRoutine;
	
	bool b_IsSuspended;
	int n_SuspendCount;
	bool b_IsAlive;

	ThreadState ts_State;

	
public:
	Thread();
	Thread(LPTHREAD_START_ROUTINE lpRoutine);
	~Thread();

	void Start();//Starts the thread
	void Start(void* param);
	void Abort();
	bool Suspend();
	bool Resume();

	bool IsSuspended();//Is it suspended
	bool IsAlive();//Is it running

	CONTEXT GetContext();

	static Thread GetCurrent();
};








namespace Exceptions {
	class ThreadException : public Exception {
		
	private:
		Thread t_Current;

	public:
		ThreadException();
	};
	class ThreadNotSuspendedException : public Exceptions::ThreadException {

	};
	class ThreadStateException : public ThreadException {

	};
}
#endif