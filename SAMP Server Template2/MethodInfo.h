#ifndef METHOD_INFO_H
#define METHOD_INFO_H

#include "ModuleInfo.h"
#include "TypeInfo.h"

class MethodInfo {
public:
	char* cstr_MethodName;
	int n_ParameterCount;
	TypeInfo* a_ParameterTypes;
	TypeInfo ti_ReturnType;
	ModuleInfo m_Module;
};
class DebugMethodInfo : public MethodInfo {
public:
	DebugTypeInfo* a_ParameterTypes;
	DebugTypeInfo ti_ReturnType;
	DebugModuleInfo m_Module;

	char* cstr_SourceFileDirectory;
	char* cstr_SourceFileName;
	int n_SourceFileLineNumber;

	DebugMethodInfo();
	DebugMethodInfo(long dw_Address, bool b_InitializeSymbols);
	~DebugMethodInfo();
};

#endif