#ifndef TYPE_INFO_H
#define TYPE_INFO_H

class TypeInfo {
public:
	char* cstr_TypeName;
};
class DebugTypeInfo : public TypeInfo {
public:
	char* cstr_SourceFileDirectory;
	char* cstr_SourceFileName;
	int n_SourceFileLineNumber;
};

#endif