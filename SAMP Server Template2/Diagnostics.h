#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "TypeInfo.h"
#include "MethodInfo.h"
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