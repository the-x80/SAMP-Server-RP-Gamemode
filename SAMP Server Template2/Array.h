#ifndef ARRAY_H
#define ARRAY_H

template <typename T> class Array {
private:
	T* elements;
	int size;//Size on memory
	int length;//The number of elements
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
	inline bool Remove(T gen_Element) {
		bool b_Return = false;
		T* gen_Buffer = elements;//Copy the current contents into the buffer
		elements = new T[length - 1];//Create a new memory location with a smaller size.
		int n_Index = 0;
		for (int i = 0; i < length; i++) {
			if (gen_Buffer[i] == gen_Element) {
				b_Return = true;
				continue;
			}
			elements[n_Index] = gen_Buffer[i];
			n_Index++;
		}
		return b_Return;
	}

	int Length() {
		return length;
	}


	inline T& operator[](int index) {
		return elements[index];
	}
};

#endif