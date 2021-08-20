#ifndef DELEGATE_H
#define DELEGATE_H
class Delegate {
private:
protected:
	void* (*pointer)();
	void** params;
	int parameterCount;
public:
	Delegate();
	Delegate(void* (*ptr)());//Adds a function with no arguments
	Delegate(void* (*ptr)(), int argCount);//Adds a function with arguments


	void Invoke();
};
#endif