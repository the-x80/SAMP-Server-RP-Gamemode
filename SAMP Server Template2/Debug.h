#ifndef DEBUG_H
#define DEBUG_H
#include <Windows.h>

#ifndef ARRAY_H
#include "Array.h"
#endif
#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif

class Debug
{
private:
	
public:
	class Entry {
	public:
		enum class Type {
			Null,
			Log,
			Warning,
			Error
		};
		Type type;
	};

	static Array<Exceptions::Exception*> a_Exceptions;
public:
	static bool logToFile;
	static HANDLE h_Mutex;


	static void Initialize();
	static void Release();


	static void Log(const char* msg);
	static void LogWarning(const char* msg);
	static void LogError(const char* msg);

	static void Throw(Exceptions::Exception* e_Exception);

	static void Break();
private:
	
};

#endif