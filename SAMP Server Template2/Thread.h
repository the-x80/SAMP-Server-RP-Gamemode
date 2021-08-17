#ifndef THREAD_H
#define THREAD_H


class Thread
{
private:
	HANDLE h_Thread;
	LPTHREAD_START_ROUTINE lp_StartRoutine;
	
	
	Thread();
public:
	Thread(LPTHREAD_START_ROUTINE lpRoutine);
	~Thread();

	void Start();//Starts the thread
	void Abort();
	void Suspend();
	void Resume();

	bool IsSuspended();//Is it suspended
	bool IsAlive();//Is it running


	static Thread GetCurrent();
};
#endif