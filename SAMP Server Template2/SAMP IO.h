#ifndef SAMP_IO_H
#define SAMP_IO_H

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif // !EXCEPTIONS_H


namespace SAMP_SDK {
	namespace IO {
		const char* cstr_SanAndreasDirectory;//The root directory for San Andreas
		

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