#ifndef SYMBOL_HELPER_H
#define SYMBOL_HELPER_H
#include "Exceptions.h"

namespace DebugSymbolHelper {
	static bool b_IsInitialized;

	/// <summary>
	/// Initializes the Symbols for this process
	/// </summary>
	void Initialize();
	/// <summary>
	/// Cleans up the initialized symbols for this process.
	/// </summary>
	void Cleanup();

	SYMBOL_INFO* GetSymInfoFromAddr(DWORD64 dw_Address);
	/// <summary>
	/// Retrieves a MethodInfo structure that describes the function at the given address.
	/// </summary>
	/// <param name="dw_Address">Address of the function</param>
	/// <returns>A pointer to a DebugMethodInfo structure describing the function.</returns>
	DebugMethodInfo* GetDebugMethodInfoFromAddress(DWORD64 dw_Address);

	bool GetMethodNameFromAddress(DWORD64 dw_Address, char* cstr_Name);


	namespace Exceptions {
		class SymInitializationException : public ::Exceptions::Exception {
		public:
			int n_LastError;
		};
	}
};

#endif