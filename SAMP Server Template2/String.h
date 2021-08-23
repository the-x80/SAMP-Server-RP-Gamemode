#ifndef STRING_H
#define STRING_H

#ifdef _DEBUG
//#define STRING_DEBUG
#endif


class String {
protected:
	char* cstr_Text;
	long n_Length;//Length in characters-
	long n_Size;//Size in bytes.
public:
	String();
	String(char* cstr_text);
	~String();




	String& operator +(String other);
	String& operator +(short other);
	String& operator +(int other);
	String& operator +(long other);
	String& operator +(float other);
	String& operator +(double other);
	String& operator +(char other);
	String& operator +(char* other);
	String& operator +(const char* other);

	String& operator +(unsigned short other);
	String& operator +(unsigned int other);
	String& operator +(unsigned long other);
	String& operator +(unsigned char other);

	String& operator +(void* other);

	operator char* ();
};

#endif
