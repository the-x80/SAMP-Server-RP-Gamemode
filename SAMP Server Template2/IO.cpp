#define _CRT_SECURE_NO_WARNINGS
#include "IO.h"



#ifdef _DEBUG
#define DEBUG_INITIALIZE




#define DEBUG_START												\
				char* cstr_DebugMessage = new char[2048];		\
				memset(cstr_DebugMessage, 0, 2048*sizeof(char));


#define DEBUG_MESSAGE(msg, ...)												\
				memset(cstr_DebugMessage, 0, sizeof(char)*2048);			\										\
				sprintf_s(cstr_DebugMessage, 2048 * sizeof(char), "%s::%s", __func__, msg);		\
				{															\
					char* cstr_FormatedMessage = new char[2048];			\
					sprintf_s(cstr_FormatedMessage, 2048*sizeof(char), cstr_DebugMessage, __VA_ARGS__);\
					OutputDebugString(cstr_FormatedMessage);				\
					delete[] cstr_FormatedMessage;							\
				}


#define DEBUG_END							\
				delete[] cstr_DebugMessage;	\
				cstr_DebugMessage = nullptr;


#define DIAGNOSTICS_START\
			LARGE_INTEGER li_qpcStart;\
			QueryPerformanceCounter(&li_qpcStart);

#define DIAGNOSTICS_END\
			LARGE_INTEGER li_qpcEnd;\
			LARGE_INTEGER li_qpcFreq;\
			QueryPerformanceCounter(&li_qpcEnd);\
			QueryPerformanceFrequency(&li_qpcFreq);\
			DEBUG_MESSAGE("Execution time:%f\nQPCStart %u\nQPCEnd %u\n", (float)((li_qpcEnd.LowPart - li_qpcStart.LowPart) / li_qpcFreq.LowPart), li_qpcStart.LowPart, li_qpcEnd.LowPart);\
			DEBUG_MESSAGE("Tick count %u\n", li_qpcEnd.LowPart - li_qpcStart.LowPart);
#endif








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
	}

	bool b_RetVal = false;
	do {
		if (strcmp(cstr_Filename, fd_FindData.cFileName) == 0) {
			b_RetVal = true;

			int n_RequiredFullPathLength = strlen(cstr_SearchPath) + strlen(fd_FindData.cFileName);
			if (n_RequiredFullPathLength > *cstr_FullPathLength) {
				throw new ::Exceptions::OutOfMemoryException();
			}

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

bool IO::SearchDriveForFile(char* cstr_Filename, char* cstr_DriveLetter, char* cstr_FullPath)
{
	return false;
}
