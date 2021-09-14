#ifndef DEBUG_MACROS_H
#define DEBUG_MACROS_H
#ifdef _DEBUG

	#ifndef _INC_STDIO
		#include <stdio.h>
	#endif
	#ifndef _WINDOWS_
		#include <Windows.h>
	#endif



	
	#ifdef _CRT_SECURE_NO_WARNINGS
		#define DEBUG_START(bufferSize)\
			int n_DebugMessageSize = bufferSize;\
			char cstr_DebugMessage[bufferSize] = "";

		#define DEBUG_MESSAGE(msg, ...)\
			{\
				sprintf(cstr_DebugMessage, "%s::%s", __func__, msg);\
				char* cstr_OutputMessage = new char[n_DebugMessageSize];\
				sprintf(cstr_OutputMessage, cstr_DebugMessage, __VA_ARGS__);\
				OutputDebugString(cstr_OutputMessage);\
				delete[] cstr_OutputMessage;\
			}

		#define DEBUG_STOP
	#else
		#define DEBUG_START(bufferSize)\
			int n_DebugMessageSize = bufferSize;\
			char cstr_DebugMessage[bufferSize] = "";

		#define DEBUG_MESSAGE(msg, ...)\
			{\
				sprintf_s(cstr_DebugMessage,n_DebugMessageSize, "%s::%s", __func__, msg);\
				char* cstr_OutputMessage = new char[n_DebugMessageSize];\
				sprintf_s(cstr_OutputMessage,n_DebugMessageSize, cstr_DebugMessage, __VA_ARGS__);\
				OutputDebugString(cstr_OutputMessage);\
				delete[] cstr_OutputMessage;\
			}

		#define DEBUG_STOP


	#endif

	#define DIAGNOSTICS_START\
				LARGE_INTEGER li_qpcStart;\
				QueryPerformanceCounter(&li_qpcStart);

	#define DIAGNOSTICS_END\
				LARGE_INTEGER li_qpcEnd;\
				LARGE_INTEGER li_qpcFreq;\
				QueryPerformanceCounter(&li_qpcEnd);\
				QueryPerformanceFrequency(&li_qpcFreq);\
				{\
					DEBUG_START(1024);\
					DEBUG_MESSAGE("Execution time:%f\nQPCStart %u\nQPCEnd %u\n", ((float)(li_qpcEnd.LowPart - li_qpcStart.LowPart) / (float)li_qpcFreq.LowPart), li_qpcStart.LowPart, li_qpcEnd.LowPart);\
					DEBUG_MESSAGE("Tick count %u\n", li_qpcEnd.LowPart - li_qpcStart.LowPart);\
					DEBUG_STOP;\
				}
#endif


#endif