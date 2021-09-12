#define _CRT_SECURE_NO_WARNINGS
#include "Framework.h"
#include <Windows.h>
#include "SAMP IO.h"



#ifdef _DEBUG
#define DEBUG_INITIALIZE




#define DEBUG_START												\
				char* cstr_DebugMessage = new char[2048];		\
				memset(cstr_DebugMessage, 0, 2048*sizeof(char));
				

#define DEBUG_MESSAGE(msg, ...)												\
				memset(cstr_DebugMessage, 0, sizeof(char)*2048);			\
				sprintf(cstr_DebugMessage, "%s::%s", __func__, msg);		\
				{															\
					char* cstr_FormatedMessage = new char[2048];				\
					sprintf(cstr_FormatedMessage, cstr_DebugMessage, __VA_ARGS__);\
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
			DEBUG_MESSAGE("Execution time:%f\nQPCStart %u\nQPCEnd %u\n", ((float)(li_qpcEnd.LowPart - li_qpcStart.LowPart) / (float)li_qpcFreq.LowPart), li_qpcStart.LowPart, li_qpcEnd.LowPart);\
			DEBUG_MESSAGE("Tick count %u\n", li_qpcEnd.LowPart - li_qpcStart.LowPart);
#endif




void SAMP_SDK::IO::Initialize()
{
#ifdef DEBUG_INITIALIZE
	DEBUG_START;
	DEBUG_MESSAGE("Started\n")
#endif
	SearchForSanAndreasDirectory();

#ifdef DEBUG_INITIALIZE
	DEBUG_MESSAGE("Ended\n");
	DEBUG_END
#endif
}

void SAMP_SDK::IO::Close()
{
	//throw new ::Exceptions::NotImplementedException();
}

void SAMP_SDK::IO::SearchForSanAndreasDirectory()
{
	//throw new ::Exceptions::NotImplementedException();

#ifdef _DEBUG
	DEBUG_START;
	DIAGNOSTICS_START;
	DEBUG_MESSAGE("Started\n");
#endif
	char cstr_VolumeGUID[MAX_PATH] = "";
	HANDLE h_VolumeSearch = FindFirstVolume(cstr_VolumeGUID, ARRAYSIZE(cstr_VolumeGUID));
	while (true) {
		//Find out what logical volumes are linked to this volume
		BOOL b_GetVolumePathResult = FALSE;
		char* cstr_VolumePathNames = nullptr;
		int n_VolumePathNameSize = MAX_PATH;
		int n_VolumePathNameReturnSize = 0;
		do {
			if (cstr_VolumePathNames == nullptr) {
				cstr_VolumePathNames = new char[n_VolumePathNameSize];
			}
			else {
				delete[] cstr_VolumePathNames;
				n_VolumePathNameSize += n_VolumePathNameReturnSize;
				cstr_VolumePathNames = new char[n_VolumePathNameSize];
			}
			b_GetVolumePathResult = GetVolumePathNamesForVolumeName(cstr_VolumeGUID, cstr_VolumePathNames, n_VolumePathNameSize, (PDWORD)&n_VolumePathNameReturnSize);
		} while (b_GetVolumePathResult == FALSE);


		//Process the returned path names into sections
		for (int i = 0; cstr_VolumePathNames[i] != NULL;i = strlen(cstr_VolumePathNames + i)+1) {
#ifdef _DEBUG
			DEBUG_MESSAGE("Current drive path is \"%s\"\n", cstr_VolumePathNames + i);
#endif
			char* cstr_SearchPath = new char[MAX_PATH];
			memset(cstr_SearchPath, 0, sizeof(char) * MAX_PATH);
			sprintf(cstr_SearchPath, "%sProgram Files\\", cstr_VolumePathNames + i);
			int n_FullPathLength = MAX_PATH;
			char* cstr_FullPath = new char[n_FullPathLength];

			if (::IO::SearchFolderForFile("gta_sa.exe", cstr_SearchPath, cstr_FullPath, &n_FullPathLength, true) == true) {
#ifdef _DEBUG
				DEBUG_MESSAGE("gta_sa.exe found at location %s\n", cstr_FullPath);
#endif
			}
			else {
#ifdef _DEBUG
				DEBUG_MESSAGE("gta_sa.exe not found\n");
#endif
			}
			delete[] cstr_SearchPath;
		}






		BOOL b_FindVolumeNextResult = FindNextVolume(h_VolumeSearch, cstr_VolumeGUID, ARRAYSIZE(cstr_VolumeGUID));
		if (b_FindVolumeNextResult == FALSE) {
			switch (GetLastError()) {
			case ERROR_NO_MORE_FILES:
				break;
			}

			break;
		}
	}
	FindVolumeClose(h_VolumeSearch);
	h_VolumeSearch = INVALID_HANDLE_VALUE;
#ifdef _DEBUG
	DIAGNOSTICS_END;
	DEBUG_MESSAGE("Ended\n");
	DEBUG_END
#endif
}
