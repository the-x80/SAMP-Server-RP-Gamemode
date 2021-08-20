#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
#include <exception>
#include "MethodInfo.h"

class StackTrace;

namespace Exceptions {
	class Exception : public std::exception {
	protected:
		/// <summary>
		/// Contains the full printable message used by ToString() method.
		/// </summary>
		char* cstr_FullMessage;
		char* message;

		int n_SourceFileLine;

		StackTrace* stackTrace;
		/// <summary>
		/// Describes the method that the exception was thrown in.
		/// </summary>
		DebugMethodInfo mi_Method;
	public:
		Exception() noexcept;
		Exception(const char* msg) noexcept;
		~Exception() noexcept;

		virtual char* ToString();
	protected:
		void PrintToOutput();
	};
	class NullPointerException : public Exception {
	public:
		NullPointerException() noexcept;
		NullPointerException(const char* msg) noexcept;
		~NullPointerException() noexcept;
	};
	class OutOfMemoryException : public Exception{

	};
	class BadAllocationException : public std::bad_alloc {
		
	};


	class IndexOutOfBoundsException : public Exception {

	};

	class DivisionByZeroException : public Exception {

	};


	class NotImplementedException : Exception {

	};
}
#endif