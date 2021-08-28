#ifndef STRING_H
#define STRING_H

#ifdef _DEBUG
#define STRING_DEBUG

#ifdef STRING_DEBUG

#define DEBUG_START(message_Size)\
					char cstr_DebugMessage[message_Size];\
					char cstr_FormatString[message_Size];\
					memset(cstr_DebugMessage, 0, (message_Size)*sizeof(char));\
					sprintf(cstr_DebugMessage, "%s::Debug started.\n", __func__);\
					OutputDebugString(cstr_DebugMessage);\



#define DEBUG_MESSAGE(format, ...)\
					sprintf(cstr_FormatString, "%s::%s",__func__, format);\
					sprintf(cstr_DebugMessage, cstr_FormatString, __VA_ARGS__);\
					OutputDebugString(cstr_DebugMessage);\

#define DEBUG_END() DEBUG_MESSAGE("Debug has ended.\n");


#endif
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

	void Format(String formatString, ...);

	void TrimLeft(int n_Characters);
	void TrimRight(int n_Characters);
	void PadLeft(int n_Characters, char c_PadCharacter = ' ');
	void PadRight(int n_Characters, char c_PadCharacter = ' ');

	Array<String> Split(const char c_Delimiter);
	Array<String> Split(const char* c_Delimiters, int n_DelimiterCount);

	void Replace(String what, String with);


	
	String& operator =(String other);
	/*
	String& operator =(short other);
	String& operator =(int other);
	String& operator =(long other);
	String& operator =(float other);
	String& operator =(double other);
	String& operator =(char other);
	*/

	String& operator =(char* other);
	String& operator =(const char* other);

	/*
	String& operator =(unsigned short other);
	String& operator =(unsigned int other);
	String& operator =(unsigned long other);
	String& operator =(unsigned char other);
	*/

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

	String& operator +=(String other);
	String& operator +=(short other);
	String& operator +=(int other);
	String& operator +=(long other);
	String& operator +=(float other);
	String& operator +=(double other);
	String& operator +=(char other);
	String& operator +=(char* other);
	String& operator +=(const char* other);

	String& operator +=(unsigned short other);
	String& operator +=(unsigned int other);
	String& operator +=(unsigned long other);
	String& operator +=(unsigned char other);

	

	operator char* ();
};

#endif
