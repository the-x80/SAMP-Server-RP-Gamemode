#ifndef STACK_H
#define STACK_H


enum class StackMode {
	FIFO,
	FILO,
	LIFO,
	LILO
};

template <typename T> class Stack {
private:
	Array<T> a_StackObjects;
	StackMode sm_Mode;
public:
	inline Stack() {
		sm_Mode = StackMode::FIFO;
	}

	inline void Push(T gen_Object) {
		switch (sm_Mode)
		{
		case StackMode::FIFO:
		case StackMode::FILO:
			this->a_StackObjects.AddFirst(gen_Object);
			break;
		case StackMode::LIFO:
		case StackMode::LILO:
			this->a_StackObjects.Add(gen_Object);
			break;
		default:
			break;
		}
	}
	inline void Pop() {
		switch (sm_Mode) {
		case StackMode::FILO:
		case StackMode::LILO:
			this->a_StackObjects.RemoveLast();
			break;
		case StackMode::FIFO:
		case StackMode::LIFO:
			this->a_StackObjects.RemoveFirts();
			break;
		}
	}
	inline int GetLength() {
		return a_StackObjects->Length();
	}

	inline T& operator[](unsigned long index) {
		return a_StackObjects[index];
	}
};
#endif