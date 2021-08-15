#pragma once
//Very rudimental debug printing system
#include <Windows.h>

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
public:
	static bool logToFile;
	static HANDLE h_Mutex;


	static void Initialize();
	static void Release();


	static void Log(const char* msg);
	static void LogWarning(const char* msg);
	static void LogError(const char* msg);

	static void Break();
private:
	
};

