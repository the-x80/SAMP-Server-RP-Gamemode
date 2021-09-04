#ifndef FUNCTION_H
#define FUNCTION_H

/*
Devlog:
	02.09.2021:
		-Created Function template class.

Planned features:
	-Perform argument and return value checks

Developer notes:
	-Still hasnt been tested.
*/

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif

namespace Exceptions {
	class TargetInvocationException : public Exception {
		Exception* e_InnerException;

		TargetInvocationException();
	};
}

template <typename ReturnType, typename... Arguments> class Function {
	
public:
	enum class CallingConvention {
		cdecl_,
		clrcall,
		stdcall
	};
	typedef ReturnType(__cdecl FunctionPointerCDECL)(Arguments...);
	typedef ReturnType (__stdcall FunctionPointerSTDCALL)(Arguments...);
	ReturnType (*fn_Pointer)(Arguments...);
	CallingConvention callingConvention;

	inline Function() {
		this->fn_Pointer = nullptr;
	}
	inline Function(FunctionPointerCDECL* func_ptr) {
		this->fn_Pointer = (FunctionPointerCDECL*)func_ptr;
		this->callingConvention = CallingConvention::cdecl_;
	}
	inline Function(FunctionPointerSTDCALL* func_ptr) {
		this->fn_Pointer = (FunctionPointerCDECL*)func_ptr;
		this->callingConvention = CallingConvention::stdcall;
	}
	inline ~Function() {
		
	}

	inline ReturnType Invoke(Arguments... args) {
		
		ReturnType retVal = 0;
		try {
			switch (callingConvention) {
			case CallingConvention::cdecl_:
				__asm {

				}
				break;
			case CallingConvention::clrcall:
				__asm {

				}
				break;
			case CallingConvention::stdcall:
				//retVal = (FunctionPointerSTDCALL*)this->fn_Pointer(args...);
				//Since calling functions normally does not work
				//Call them in asssembler
				__asm {

				}
				break;

			}
			
		}
		catch (Exceptions::Exception* e) {

		}
		return retVal;
	}
};

#endif