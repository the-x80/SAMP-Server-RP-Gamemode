#pragma once
#include <exception>

namespace Exceptions {
	class Exception : public std::exception {
	protected:
		/// <summary>
		/// Contains the full printable message used by ToString() method.
		/// </summary>
		char* cstr_FullMessage;
		char* message;
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


	class NotImplementedException : Exception {

	};
}