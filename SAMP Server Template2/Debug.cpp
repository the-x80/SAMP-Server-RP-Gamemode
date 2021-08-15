#include <Windows.h>

#include "Debug.h"
#include "Exceptions.h"
#include <stdio.h>


int CalculateTimestampSize() {
	int n_RetVal = 22;
	return n_RetVal;
}
void GenerateTimestamp(char* timestamp)
{
#ifdef _DEBUG
	if (timestamp == nullptr) {
		throw new Exceptions::NullPointerException();
	}
#endif

	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);

	SetLastError(0);
	int n_Result = wsprintf(timestamp, "[%.2d/%.2d/%.4d, %.2d/%.2d/%.2d]", sysTime.wDay, sysTime.wMonth, sysTime.wYear, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	int n_CalculatedSize = CalculateTimestampSize();
	if (n_Result != n_CalculatedSize) {
		char* cstr_DebugMessage = new char[1024];
		wsprintf(cstr_DebugMessage, "%s::ERROR::Calculated and formated timestamp size mistmatch. Calculated size is %d and formated size is %d. Formated string is %s. GetLastError returned %d.\n", __func__, n_CalculatedSize, n_Result, timestamp, GetLastError());
		OutputDebugString(cstr_DebugMessage);
		delete[] cstr_DebugMessage;
	}
}


HANDLE Debug::h_Mutex;

void Debug::Initialize()
{
	
}

void Debug::Release()
{

}

void Debug::Log(const char* msg)
{
	//Data required to write to console window
	HANDLE h_StdOutput = INVALID_HANDLE_VALUE;
	int n_NumberOfCharsWritten = 0;


	//Calculate the required memory allocation
	int n_FullMessageLength = strlen(msg);//Initialize it to the msg length since that is the shortest it could be

	//Calculate the size of the timestamp.
	//The format should be "[dd/mm/YYYY, hh/mm/ss]"
	int n_TimestampLength = CalculateTimestampSize();
	char* cstr_Timestamp = new char[n_TimestampLength+1];
	ZeroMemory(cstr_Timestamp, n_TimestampLength + 1);
	GenerateTimestamp(cstr_Timestamp);
	n_FullMessageLength += n_TimestampLength;

	int n_NumberOfTabSpaces = 4;
	char* cstr_TabSpaces = new char[n_NumberOfTabSpaces+1];
	memset(cstr_TabSpaces, '\0', n_NumberOfTabSpaces+1);
	memset(cstr_TabSpaces, ' ', n_NumberOfTabSpaces);
	n_FullMessageLength += n_NumberOfTabSpaces;

	n_FullMessageLength += 3;//Two more characters for new lines
	char* cstr_OutputMessage = new char[n_FullMessageLength+1];
	ZeroMemory(cstr_OutputMessage, n_FullMessageLength + 1);
	int n_Result = snprintf(cstr_OutputMessage, n_FullMessageLength,
							"%s\n%s%s\n", cstr_Timestamp, cstr_TabSpaces, msg);

	h_StdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//The color change should mbe made before writting to the console.
	WriteConsole(h_StdOutput, cstr_OutputMessage, n_FullMessageLength, (LPDWORD)&n_NumberOfCharsWritten, nullptr);
	
	//Cleanup
	delete[] cstr_OutputMessage;
	delete[] cstr_TabSpaces;
	delete[] cstr_Timestamp;
}

void Debug::LogWarning(const char* msg)
{
}

void Debug::LogError(const char* msg)
{
}

