#define _CRT_SECURE_NO_WARNINGS
#include "IO.h"
#include "DebugMacros.h"

IO::Exceptions::IOException::IOException()
{
}

IO::Exceptions::IOException::IOException(char* message) : ::Exceptions::Exception(message)
{
	
}

IO::Exceptions::InvalidPathException::InvalidPathException()
{
}

IO::Exceptions::InvalidPathException::InvalidPathException(char* message) : Exceptions::IOException(message)
{
	
}




int IO::GetLogicalDriveCount()
{
	return 0;
}

bool IO::SearchFolderForFile(char* cstr_Filename, char* cstr_FolderPath, char* cstr_FullPath, int* cstr_FullPathLength, bool b_SearchSubdirectories)
{
#pragma region Sanity checks
	if (cstr_Filename == nullptr) {
		throw new ::Exceptions::ArgumentNullException();
	}
	if (cstr_FolderPath == nullptr) {
		throw new ::Exceptions::ArgumentNullException();
	}
	if (cstr_FullPath == nullptr) {
		throw new ::Exceptions::ArgumentNullException();
	}

	if (memcmp(cstr_FolderPath, "\\\\.\\", sizeof(char)*strlen("\\\\.\\")) == 0) {
		throw new IO::Exceptions::InvalidPathException("cstr_FolderPath argument has a device namespace prefix.");
	}

	//Check if the csrt_FolderPath ends with a trailing slash
	//If not add the trailing slash to the string.
	char cstr_SearchPath[MAX_PATH*2] = "";
#ifndef _CRT_SECURE_NO_WARNINGS
	if (cstr_FolderPath[strlen(cstr_FolderPath) - 1] != '\\') {
		sprintf_s(cstr_SearchPath, sizeof(char) * MAX_PATH * 2, "%s\\*", cstr_FolderPath);
	}
	else {
		sprintf_s(cstr_SearchPath, sizeof(char) * MAX_PATH * 2, "%s*", cstr_FolderPath);
	}
#else
	if (cstr_FolderPath[strlen(cstr_FolderPath) - 1] != '\\') {
		sprintf(cstr_SearchPath, "%s\\*", cstr_FolderPath);
	}
	else {
		sprintf(cstr_SearchPath, "%s*", cstr_FolderPath);
	}
#endif
#pragma endregion

	WIN32_FIND_DATA fd_FindData = { 0 };
	HANDLE h_FindFile = FindFirstFile(cstr_SearchPath, &fd_FindData);
	if (h_FindFile == INVALID_HANDLE_VALUE) {
		//Handle the error.
		throw Exceptions::IOException();
	}

	bool b_RetVal = false;
	do {
		if (strcmp(cstr_Filename, fd_FindData.cFileName) == 0) {
			b_RetVal = true;

			int n_RequiredFullPathLength = strlen(cstr_SearchPath) + strlen(fd_FindData.cFileName);
			if (n_RequiredFullPathLength > *cstr_FullPathLength) {
				throw new ::Exceptions::OutOfMemoryException();
			}

			memset(cstr_FullPath, 0, *cstr_FullPathLength);
			memcpy_s(cstr_FullPath, *cstr_FullPathLength, cstr_SearchPath, strlen(cstr_SearchPath) - 1);
			memcpy_s(cstr_FullPath + (strlen(cstr_FullPath)), *cstr_FullPathLength - (strlen(cstr_FullPath)), fd_FindData.cFileName, strlen(fd_FindData.cFileName));
			*cstr_FullPathLength = strlen(cstr_FullPath);
			break;
		}
		else {
			if ((fd_FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (b_SearchSubdirectories)) {
				if (strcmp(fd_FindData.cFileName, ".") == 0) {
					continue;
				}
				if (strcmp(fd_FindData.cFileName, "..") == 0) {
					continue;
				}

				char cstr_SubFolderPath[MAX_PATH*2] = "";
#ifndef _CRT_SECURE_NO_WARNINGS
				sprintf_s(cstr_SubFolderPath, sizeof(char) * MAX_PATH*2, "%s%s\\", cstr_FolderPath, fd_FindData.cFileName);
#else
				sprintf(cstr_SubFolderPath, "%s%s\\", cstr_FolderPath, fd_FindData.cFileName);
#endif
				b_RetVal = FALSE;
				try {
					b_RetVal = SearchFolderForFile(cstr_Filename, cstr_SubFolderPath, cstr_FullPath, cstr_FullPathLength, b_SearchSubdirectories);
				}
				catch (::Exceptions::ArgumentNullException* e) {
					b_RetVal = FALSE;
				}
				catch (::Exceptions::OutOfMemoryException* e) {
					b_RetVal = FALSE;
				}
				catch (::Exceptions::Exception* e) {
					b_RetVal = FALSE;
				}
				if (b_RetVal == true) {
					break;
				}
			}
		}
	} while (FindNextFile(h_FindFile, &fd_FindData));
	BOOL b_FindCloseResult = FindClose(h_FindFile);
	if (b_FindCloseResult == FALSE) {
		//Handle the error.
	}

	return b_RetVal;
}

struct LogicalDriveWorkerThreadData {

};
void SearchDriveForFileLogicalDriveWorkerThread(char* cstr_DriveLetter) {

}
bool IO::SearchDriveForFile(char* cstr_Filename, char* cstr_DriveGUID, char* cstr_FullPath)
{
	return false;
}

struct DriveWorkerThreadData {

};
void SearchSystemForFileDriveWorkerThread(char* cstr_DriveGUID) {

}
bool IO::SearchSystemForFile(char* cstr_Filename, char* cstr_FullPath)
{
	char cstr_VolumeGUID[MAX_PATH] = "";
	HANDLE h_VolumeSearch = FindFirstVolume(cstr_VolumeGUID, ARRAYSIZE(cstr_VolumeGUID));
	while (true) {
		IO::SearchDriveForFile(cstr_Filename, cstr_VolumeGUID, cstr_FullPath);
		BOOL b_FindVolumeNextResult = FindNextVolume(h_VolumeSearch, cstr_VolumeGUID, ARRAYSIZE(cstr_VolumeGUID));
		if (b_FindVolumeNextResult == FALSE) {
			switch (GetLastError()) {
			case ERROR_NO_MORE_FILES:
				break;
			}

			break;
		}
	}
	return false;
}


