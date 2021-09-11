#ifndef SAMP_IO_H
#define SAMP_IO_H

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif // !EXCEPTIONS_H


namespace SAMP_SDK {
	namespace IO {
		static char* cstr_SanAndreasDirectory = nullptr;//The root directory for San Andreas
		
		/// <summary>
		/// Initializes the San Andreas IO System
		/// </summary>
		void Initialize();
		/// <summary>
		/// Frees the memory from the initialization
		/// </summary>
		void Close();

		/// <summary>
		/// Looks for the San Andreas directory on the system.
		/// </summary>
		/// <remarks>
		/// This function is super slow since it searches the entire storage for the san andreas executable
		/// </remarks>
		void SearchForSanAndreasDirectory();


		namespace Exceptions {
			class SanAndreasDirectoryNotFound : public ::Exceptions::IOException {

			};
		}
	}
}

#endif