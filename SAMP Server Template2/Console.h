#ifndef CONSOLE_H
#define CONSOLE_H

//Work in progress-

/*
Description:
	Set of tools used to handle basic console interaction.

Devlog:
	04.09.2021:
		-Console namespace created.
*/

#ifndef _WINDOWS_
#include <Windows.h>
#endif
#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif



namespace Console {
	enum class ForegroundColor {

	};
	enum class BackgroundColor {

	};

	void Allocate();
	void Free();

	void Write(const char* cstr_Text);
	void WriteLine(const char* cstr_Text);

	/// <summary>
	/// Reads a console key from the input buffer and pops it out
	/// </summary>
	/// <param name="n_KeyCode">The key code of the read key.</param>
	/// <returns></returns>
	bool ReadKey(int* n_KeyCode);
	bool PeekKey(int* n_KeyCode);


	namespace Exceptions {
		/// <summary>
		/// Base Exception class for console exceptions
		/// </summary>
		class ConsoleException : public ::Exceptions::Exception {
		public:
			int n_LastErrorCode;
		};


		/// <summary>
		/// Thrown when the console could not be allocated.
		/// </summary>
		class ConsoleAllocationException : public ConsoleException {

		};
	}
};

#endif