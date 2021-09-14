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
	n_WindowsLastErrorCode = GetLastError();

	int n_MessageLength = strlen(msg);
	this->message = new char[n_MessageLength+1];
	memcpy_s(this->message, n_MessageLength+1, '\0', n_MessageLength+1);
	strcpy_s(this->message, n_MessageLength, msg);

	this->cstr_FullMessage = new char[0];
	this->stackTrace = new StackTrace(1);

	this->e_InnerException = nullptr;

	this->mi_Method = DebugMethodInfo();

	this->n_SourceFileLine = 0;
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

