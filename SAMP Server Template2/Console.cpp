#define _CRT_SECURE_NO_WARNINGS

#include "Console.h"

namespace Console {
	static HANDLE h_Input = INVALID_HANDLE_VALUE;
	static HANDLE h_Output = INVALID_HANDLE_VALUE;
	static HANDLE h_Error = INVALID_HANDLE_VALUE;




	void Write(const char* cstr_Text)
	{
		if (h_Output == INVALID_HANDLE_VALUE) {
			h_Output = ::GetStdHandle(STD_OUTPUT_HANDLE);
			if (h_Output == INVALID_HANDLE_VALUE) {//The application was unable to get standard output handle
				//Handle the error accordingly

			}
		}

		int n_TextSize = strlen(cstr_Text);
		int n_CharsWritten = 0;
		BOOL b_WriteConsoleResult = WriteConsole(h_Output, cstr_Text, n_TextSize, (LPDWORD)&n_CharsWritten, NULL);
		if (b_WriteConsoleResult == false) {//Write failed. Perform error check.

		}
	}

	void WriteLine(const char* cstr_Text)
	{
		int n_NewTextSize = strlen(cstr_Text) + 2;
		char* cstr_NewText = new char[n_NewTextSize];
		memset(cstr_NewText, 0, n_NewTextSize);
		sprintf(cstr_NewText, "%s\n", cstr_Text);
		Write(cstr_NewText);
		delete[] cstr_NewText;
		return;
	}

	bool ReadKey(int* n_KeyCode)
	{
		if (h_Input == INVALID_HANDLE_VALUE) {
			h_Input = ::GetStdHandle(STD_INPUT_HANDLE);
			if (h_Input == INVALID_HANDLE_VALUE) {
				//Handle the error accordingly.

			}
		}

		int n_NumConsoleEvents = 0;
		GetNumberOfConsoleInputEvents(h_Input, (LPDWORD)&n_NumConsoleEvents);

		INPUT_RECORD* ir_Events = nullptr;
		try {
			ir_Events = new INPUT_RECORD[n_NumConsoleEvents];
		}
		catch (std::bad_alloc e) {

		}

		int n_EventsRead = 0;
		BOOL b_ReadConInputResult = ReadConsoleInput(h_Input, ir_Events, n_NumConsoleEvents, (LPDWORD)&n_EventsRead);
		if (b_ReadConInputResult == FALSE) {

		}
		return false;
	}

}