#ifndef MODULE_INFO_H
#define MODULE_INFO_H

class ModuleInfo {
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