#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <Windows.h>

#include "Framework.h"
#include "String.h"

String::String()
{
	DEBUG_START(1024);
	DEBUG_MESSAGE("this -> 0x%p\n", (void*)this);
	cstr_Text = new char[1];
	DEBUG_MESSAGE("new this->cstr_Text @ 0x%p\n", (void*)this->cstr_Text);
	memset(this->cstr_Text, 0, 1 * sizeof(char));
	this->n_Length = 0;
	this->n_Size = 1;
	DEBUG_END();
}

String::String(char* cstr_text)
{
	DEBUG_START(1024);
	DEBUG_MESSAGE("this -> 0x%p\n", (void*)this);
	if (cstr_text == nullptr) {
		throw new Exceptions::ArgumentNullException();
	}
	this->cstr_Text = new char[strlen(cstr_text) + 1];
	DEBUG_MESSAGE("new this->cstr_Text @ 0x%p\n", (void*)this->cstr_Text);
	memset(this->cstr_Text, 0, (strlen(cstr_text) + 1) * sizeof(char));
	strcpy(this->cstr_Text, cstr_text);
	this->n_Length = strlen(cstr_text);
	this->n_Size = (this->n_Length + 1) * sizeof(char);
	DEBUG_END();
}

String::~String()
{
	DEBUG_START(1024);
	DEBUG_MESSAGE("this -> 0x%p", (void*)this);
	if (this->cstr_Text != nullptr) {
		DEBUG_MESSAGE("delete[] this->cstr_Text @ 0x%p\n", (void*)this->cstr_Text);
		delete[] this->cstr_Text;
	}
	this->cstr_Text = nullptr;

	this->n_Length = 0;
	this->n_Size = 0;
	DEBUG_END();
}



String& String::operator=(String other)
{
	// TODO: String& String::operator=::Optimize it a bit.
	DEBUG_START(1024);

	DEBUG_MESSAGE("%s = %s\n", this->cstr_Text, other);
	int n_ResultLength = strlen(other.cstr_Text);
	DEBUG_MESSAGE("n_ResultLength = %d\n", n_ResultLength);
	char* cstr_ResultText = nullptr;
	try {
		cstr_ResultText = new char[n_ResultLength];
		
	}
	catch(std::bad_alloc e){
	}
	catch (std::exception e) {

	}

	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s", other.cstr_Text);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	DEBUG_END();
	return *this;
}
/*
String& String::operator=(short other)
{
	int n_ResultLength = (64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%d", other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator=(int other)
{
	int n_ResultLength = (64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%d", other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator=(long other)
{
	int n_ResultLength = (64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%d", other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator=(float other)
{
	int n_ResultLength = (64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%f", other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator=(double other)
{
	int n_ResultLength = (64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%f", other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator=(char other)
{
	int n_ResultLength = (64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%c", other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator=(char* other)
{
	if (other == nullptr) {
		throw new Exceptions::NullPointerException();
	}
	int n_ResultLength = (strlen(other) + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s", other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator=(const char* other)
{
	if (other == nullptr) {
		throw new Exceptions::NullPointerException();
	}
	int n_ResultLength = (strlen(other) + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s", other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator=(unsigned short other)
{
	// TODO: insert return statement here
	return *this;
}

String& String::operator=(unsigned int other)
{
	// TODO: insert return statement here
	return *this;
}

String& String::operator=(unsigned long other)
{
	// TODO: insert return statement here
	return *this;
}

String& String::operator=(unsigned char other)
{
	// TODO: insert return statement here
	return *this;
}
*/

String& String::operator+(String other)
{
	int n_ResultLength = (strlen(this->cstr_Text) + strlen(other.cstr_Text) + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%s", this->cstr_Text, other.cstr_Text);
	String retVal = String(cstr_ResultText);
	delete[] cstr_ResultText;
	return retVal;
}

String& String::operator+(short other)
{
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%d", this->cstr_Text, other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator+(int other)
{
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%d", this->cstr_Text, other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator+(long other)
{
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%d", this->cstr_Text, other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator+(float other)
{
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%f", this->cstr_Text, other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator+(double other)
{
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%f", this->cstr_Text, other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator+(char other)
{
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%c", this->cstr_Text, other);
	String retVal = String(cstr_ResultText);
	delete[] cstr_ResultText;
	return retVal;
}
String& String::operator+(char* other)
{
	if (other == nullptr) {
		throw new Exceptions::NullPointerException();
	}
	int n_ResultLength = (strlen(this->cstr_Text) + strlen(other) + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%s", this->cstr_Text, other);
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}
String& String::operator+(const char* other)
{
	DEBUG_START(1024);
	if (other == nullptr) {
		throw new Exceptions::NullPointerException();
	}
	DEBUG_MESSAGE("%s + %s\n", this->cstr_Text, other);
	int n_ResultLength = (strlen(this->cstr_Text) + strlen(other) + 1) * sizeof(char);
	DEBUG_MESSAGE("n_ResultLength = %d\n", n_ResultLength);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	DEBUG_MESSAGE("memset(cstr_ResultText, 0, n_ResultLength); -> cstr_ResultText = %s\n", cstr_ResultText);
	sprintf(cstr_ResultText, "%s%s", this->cstr_Text, other);
	DEBUG_MESSAGE("sprintf() -> cstr_ResultText = %s\n", cstr_ResultText);

	DEBUG_MESSAGE("Creating retVal string object.\n");
	String retVal=String(cstr_ResultText);
	DEBUG_MESSAGE("Created retVal string object.\n");


	DEBUG_MESSAGE("delete[] cstr_ResultText; ->  0x%p\n", (void*)cstr_ResultText);
	delete[] cstr_ResultText;
	DEBUG_END();
	return retVal;
}

String& String::operator+(unsigned short other)
{
	// TODO: insert return statement here
	return *this;
}

String& String::operator+(unsigned int other)
{
	// TODO: insert return statement here
	return *this;
}

String& String::operator+(unsigned long other)
{
	// TODO: insert return statement here
	return *this;
}

String& String::operator+(unsigned char other)
{
	// TODO: insert return statement here
	return *this;
}

String& String::operator+(void* other)
{
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s0x%p", this->cstr_Text, other);
	
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator+=(String other)
{
	return *this + other;
}

String& String::operator+=(short other)
{
	return *this + other;
}

String& String::operator+=(int other)
{
	return *this + other;
}

String& String::operator+=(long other)
{
	return *this + other;
}

String& String::operator+=(float other)
{
	return *this + other;
}

String& String::operator+=(double other)
{
	return *this + other;
}

String& String::operator+=(char other)
{
	return *this + other;
}

String& String::operator+=(char* other)
{
	if (other == nullptr) {
		throw new Exceptions::NullPointerException();
	}
	return *this + other;
}

String& String::operator+=(const char* other)
{
	if (other == nullptr) {
		throw new Exceptions::NullPointerException();
	}
	return *this + other;
}

String& String::operator+=(unsigned short other)
{
	return *this + other;
}

String& String::operator+=(unsigned int other)
{
	return *this + other;
}

String& String::operator+=(unsigned long other)
{
	return *this + other;
}

String& String::operator+=(unsigned char other)
{
	return *this + other;
}

String::operator char* ()
{
	return this->cstr_Text;
}
