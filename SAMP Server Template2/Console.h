#ifndef CONSOLE_H
#define CONSOLE_H

//Work in progress-

namespace Console {
	enum class ForegroundColor {

	};
	enum class BackgroundColor {

	};

	void Write(const char* cstr_Text);
	void WriteLine(const char* cstr_Text);

	bool ReadKey(int* n_KeyCode);
	bool PeekKey(int* n_KeyCode);
};

#endif