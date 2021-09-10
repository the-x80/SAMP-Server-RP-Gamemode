#ifndef IO_H
#define IO_H

#ifndef _WINDOWS_
#include <Windows.h>
#endif
#ifndef EXCEPTION_H
#include "Exceptions.h"
#endif

namespace IO {
	namespace Exceptions {
		/// <summary>
		/// Thrown when an IO exception occurs.
		/// </summary>
		class IOException : public ::Exceptions::Exception {

		};
	}

	/// <summary>
	/// Retrieves the number of logical drives and returns the result
	/// </summary>
	/// <returns>The number of logical drives.</returns>
	/// <exception cref="IO::Exceptions::IOException">Thrown when an unknown io exception occurs</exception>
	int GetLogicalDriveCount();


	//int EnumerateLogicalDrives(); Unused for now
}

#endif