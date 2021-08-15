#ifndef DELEGATE_H
#define DELEGATE_H
class Delegate {
private:
protected:
	void* (*pointer)();
	int parameterCount;
public:
	Delegate();
	Delegate(void* (*ptr)());//Adds a function with no arguments
	Delegate(void* (*ptr)(), int argCount);//Adds a function with no arguments


	void Invoke();
};
#endif