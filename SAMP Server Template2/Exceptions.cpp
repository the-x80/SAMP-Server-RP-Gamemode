#include "Exceptions.h"
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

#define _WIN32_WINNT 0x0400

#include <Windows.h>
#include <DbgHelp.h>

#pragma comment(lib, "Dbghelp.lib")

#include "Debug.h"
#include "Array.h"
#include "StackTrace.h"

#include <string>
#undef _DEBUG
#include "DebugMacros.h"




#pragma region Exception Window
class ExceptionWindow {
public:
	HWND hwnd_Handle;
	RECT r_Rect;
	Exceptions::Exception* e_DisplayingException;

	inline ExceptionWindow() {
		hwnd_Handle = (HWND)INVALID_HANDLE_VALUE;
		r_Rect = RECT();
		e_DisplayingException = nullptr;
	}



	void Create() {

	}
};
#pragma endregion














Exceptions::Exception::Exception() noexcept
{
	n_WindowsLastErrorCode = GetLastError();
	
	this->message = new char[0];
	this->cstr_FullMessage = new char[0];

	this->e_InnerException = nullptr;

	this->n_SourceFileLine = 0;

	//Note StackTrace does not have full functionality for now.
	this->stackTrace = new StackTrace(1);
	this->mi_Method = DebugMethodInfo();

	//A debugger is attached. What you could do is to display a Window detailing the exception.
	if (IsDebuggerPresent() == TRUE) {
		
	}
}

Exceptions::Exception::Exception(const char* msg) noexcept
{
	DEBUG_START(1024);
	DEBUG_MESSAGE("Started\n");
	n_WindowsLastErrorCode = GetLastError();

	DEBUG_MESSAGE("Formatting the message \"%s\"\n", msg);
	int n_MessageLength = strlen(msg);
	try {
		this->message = new char[n_MessageLength + 1];
	}
	catch (std::bad_alloc e) {
		DEBUG_MESSAGE("Bad allocation exception.\n");
	}
	DEBUG_MESSAGE("Zeroing out the message\n");
	memset(this->message, 0, n_MessageLength+1);
	DEBUG_MESSAGE("Copying the message. Size of the message is %d\n", n_MessageLength);
	memcpy_s(this->message, n_MessageLength, msg, n_MessageLength);

	this->cstr_FullMessage = new char[0];

	DEBUG_MESSAGE("Performing StackTrace.\n");
	this->stackTrace = new StackTrace(1);

	DEBUG_MESSAGE("Setting this->e_InnerException to nullptr.\n");
	this->e_InnerException = nullptr;

	DEBUG_MESSAGE("Creating a DebugMethodInfo object.\n");
	this->mi_Method = DebugMethodInfo();

	this->n_SourceFileLine = 0;
	DEBUG_MESSAGE("Ended\n");
	DEBUG_STOP;
}

Exceptions::Exception::~Exception()
{
	delete[] this->message;
	delete[] this->cstr_FullMessage;
	delete this->stackTrace;
}

char* Exceptions::Exception::ToString()
{
	return this->cstr_FullMessage;
}

void Exceptions::Exception::PrintToOutput()
{
}

Exceptions::NullPointerException::NullPointerException() noexcept
{
}

Exceptions::NullPointerException::NullPointerException(const char* msg) noexcept : Exception::Exception(msg)
{
}

Exceptions::NullPointerException::~NullPointerException()
{
}

