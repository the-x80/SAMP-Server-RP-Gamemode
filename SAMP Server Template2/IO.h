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
		class InvalidPathException : public IOException{
		public:
			InvalidPathException();
			InvalidPathException(char* message);
		};
	}

	/// <summary>
	/// Retrieves the number of logical drives and returns the result
	/// </summary>
	/// <returns>The number of logical drives.</returns>
	/// <exception cref="IO::Exceptions::IOException">Thrown when an unknown io exception occurs</exception>
	int GetLogicalDriveCount();

	/// <summary>
	/// Searches for a file or directory inside a directory
	/// </summary>
	/// <param name="cstr_Filename">The file or folder name used to perform the search</param>
	/// <param name="cstr_FolderPath">The folders path where to search.</param>
	/// <param name="cstr_FullPath">The string containing the result of the search</param>
	/// <param name="cstr_FullPathLength">The length of the string containing the result of the search</param>
	/// <param name="b_SearchSubdirectories">If set to true subdirectories are searched aswell.</param>
	/// <returns>True if the file has been found otherwise false.</returns>
	/// <remarks>
	/// This function is very slow since it has to access the hard drive for each file.
	/// There could be a posibility to speed up the process by multithreading.
	/// </remarks>
	/// <exception cref="::Exceptions::ArgumentNullException"></exception>
	/// <exception cref="::Exceptions::OutOfMemoryException"></exception>
	/// <exception cref="::IO::Exceptions::IOException"></exception>
	/// <exception cref="::IO::Exceptions::InvalidPathException"></exception>
	bool SearchFolderForFile(char* cstr_Filename, char* cstr_FolderPath, char* cstr_FullPath, int* cstr_FullPathLength, bool b_SearchSubdirectories);
	bool SearchDriveForFile(char* cstr_Filename, char* cstr_DriveGUID, char* cstr_FullPath);
	bool SearchSystemForFile(char* cstr_Filename, char* cstr_FullPath);

	//int EnumerateLogicalDrives(); Unused for now
}

#endif