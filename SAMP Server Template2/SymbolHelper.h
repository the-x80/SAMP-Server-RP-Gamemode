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




	namespace Exceptions {
		class SymInitializationException : public ::Exceptions::Exception {
		public:
			int n_LastError;
		};
	}
};

#endif