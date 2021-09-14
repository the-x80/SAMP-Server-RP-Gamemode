#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "SymbolHelper.h"
#include "InfoObject.h"
#include "TypeInfo.h"
#include "MethodInfo.h"
#include "DeviceInfo.h"
#include "StackTrace.h"
#include "Exceptions.h"


class Diagnostics {
public:
	class DiagnosticsEntry{
	public:
		void ExecutionStart();
		void ExecutionEnd();
	};
};
#endif