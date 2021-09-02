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

template <typename Return, typename... Arguments> class Function {
	Return(*fn_Pointer)(Arguments...);

	inline Function() {
		this->fn_Pointer = nullptr;
	}
	inline Function(Return(*fn_ptr)(Arguments...)) {
		this->fn_Pointer = fn_ptr;
	}
	inline ~Function() {
		this->fn_Pointer = nullptr;
	}

	inline Return Invoke(Arguments... args) {
		if (this->fn_Pointer == nullptr) {
			throw new Exceptions::NullPointerException();
		}

		Return retVal;
		try {
			retVal = this->fn_Pointer(Arguments);
		}
		catch (Exceptions::Exception* e) {

		}
		return retVal;
	}
};

#endif