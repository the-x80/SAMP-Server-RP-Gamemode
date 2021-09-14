#ifndef MODULE_INFO_H
#define MODULE_INFO_H

#include "InfoObject.h"

class ModuleInfo : public InfoObject{
public:
	void* p_ModuleAddress;
	char* cstr_ModuleName;

	ModuleInfo();
};
class DebugModuleInfo : public ModuleInfo {
public:
	DebugModuleInfo();
};

#endif