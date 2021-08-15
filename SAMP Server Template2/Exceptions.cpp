#include "Exceptions.h"

#include <string>

Exceptions::Exception::Exception() noexcept
{
	const char msg[] = "Exception";
	int n_MessageLength = strlen(msg);
	this->message = new char[strlen(msg)+1];//This is slow but its insignificant to the rest of the code
	memcpy_s(this->message, n_MessageLength+1, '\0', n_MessageLength+1);
	strcpy_s(this->message, n_MessageLength, msg);

	cstr_FullMessage = new char[0];
}

Exceptions::Exception::Exception(const char* msg) noexcept
{
	int n_MessageLength = strlen(msg);
	this->message = new char[n_MessageLength+1];
	memcpy_s(this->message, n_MessageLength+1, '\0', n_MessageLength+1);
	strcpy_s(this->message, n_MessageLength, msg);
}

Exceptions::Exception::~Exception()
{
	delete[] this->message;
	delete[] this->cstr_FullMessage;
}

char* Exceptions::Exception::ToString()
{
	return this->cstr_FullMessage;
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

