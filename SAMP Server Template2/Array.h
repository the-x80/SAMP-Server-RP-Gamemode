#ifndef ARRAY_H
#define ARRAY_H

//Developer notes
//	-Switch from using new to using malloc. Slight speed increase.
//	-The Clear function needs a better implementation. See inside the function block for more info.
//Changelog
//28.8::
//	-Added Clear function to the Array class.

template <typename T> class Array {
private:
	T* elements;
	unsigned long size;//Size on memory
	unsigned long length;//The number of elements
public:
	inline Array()
	{
		this->elements = new T[0];
		this->length = 0;
		this->size = 0;
	}
	inline Array(int n_StartLength) {
		this->elements = new T[n_StartLength];
		this->length = n_StartLength;
		this->size = n_StartLength * sizeof(T);
	}
	inline ~Array()
	{
		delete[] elements;

		this->length = 0;
		this->size = 0;
	}

	inline void Add(T element)
	{
		T* buffer = this->elements;
		this->elements = new T[this->length + 1];
		memcpy_s(this->elements, this->length * sizeof(T), buffer, this->length * sizeof(T));
		delete[] buffer;
		this->elements[this->length] = element;
		this->length += 1;
		this->size = this->length * sizeof(T);
	}
	inline void AddFirst(T gen_Element) {
		T* buffer = this->elements;
		this->elements = new T[this->length + 1];
		memcpy_s(this->elements + sizeof(T), 
			(this->length * sizeof(T)) - sizeof(T), 
			buffer, 
			(this->length * sizeof(T)) - sizeof(T));
		delete[] buffer;
		this->elements[0] = element;
		this->length += 1;
		this->size = this->length * sizeof(T);
	}
	inline void InsertAt(T gen_Element, int index) {
		int n_SizePreInsert = sizeof(T)*index;
		int n_SizePostInsert = ((this->length+1)*sizeof(T))-n_SizePreInsert-sizeof(T);
		int n_InsertOffset = sizeof(T) * index;
		int n_PostInsertOffset = n_InsertOffset + sizeof(T);

		T* gen_Buffer = this->elements;
		this->elements = new T[this->length + 1];
		memcpy(this->elements, gen_Buffer, n_SizePreInsert);
		memcpy(this->elements + n_InsertOffset, gen_Element, sizeof(T));
		memcpy(this->elements + n_PostInsertOffset, gen_Buffer, n_SizePostInsert);
		delete[] gen_Buffer;
		this->length += 1;
		this->size = this->length * sizeof(T);
	}
	inline bool Remove(T gen_Element) {
		bool b_Return = false;
		T* gen_Buffer = elements;//Copy the current contents into the buffer
		elements = new T[length - 1];//Create a new memory location with a smaller size.
		int n_Index = 0;
		for (unsigned long i = 0; i < length; i++) {
			if (&gen_Buffer[i] == &gen_Element) {
				b_Return = true;
				continue;
			}
			elements[n_Index] = gen_Buffer[i];
			n_Index++;
		}
		return b_Return;
	}
	inline bool RemoveAt(int index) {
		throw new Exceptions::NotImplementedException();
		
		if ((index >= this->length) || (index < 0)) {
			throw new Exceptions::IndexOutOfBoundsException();
		}


	}
	inline bool RemoveLast() {
		int n_NewSize = (this->length - 1) * sizeof(T);
		T* gen_Buffer = this->elements;
		this->elements = new T[this->length - 1];
		memcpy(this->elements, gen_Buffer, n_NewSize);
		delete[] gen_Buffer;
		this->length -= 1;
		this->size = this->length * sizeof(T);
	}
	inline bool RemoveFirst() {
		int n_NewSize = (this->length - 1) * sizeof(T);
		T* gen_Buffer = this->elements;
		this->elements = new T[this->length - 1];
		memcpy(this->elements, gen_Buffer + sizeof(T), n_NewSize);
		delete[] gen_Buffer;
		this->length -= 1;
		this->size = this->length * sizeof(T);
	}

	/// <summary>
	/// Clears the contents of the array.
	/// </summary>
	inline void Clear() {
		delete[] this->elements;
		this->size = 0;
		this->length = 0;
		this->elements = nullptr;

		//This is where it becomes dangerous.
		//The allocation could fail and therefore
		//The elements will be nullptr wich the class does not expect.
		//Design around this. Either by adding if nullptr checks or by avoiding the exception
		//Thrown when new is called.
		try {
			this->elements = new T[0];
		}
		catch (std::bad_alloc e) {

		}
	}

	int Length() {
		return length;
	}


	inline T& operator[](unsigned long index) {
		if ((index >= this->length) || (index < 0)) {
			throw new Exceptions::IndexOutOfBoundsException();
		}
		return elements[index];
	}
};

#endif