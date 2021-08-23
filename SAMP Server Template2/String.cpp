#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <Windows.h>
#include "String.h"

String::String()
{
	cstr_Text = new char[1];
	memset(this->cstr_Text, 0, 1 * sizeof(char));
	this->n_Length = 0;
	this->n_Size = 1;
}

String::String(char* cstr_text)
{
#ifdef STRING_DEBUG
	char cstr_DebugMessage[512];
	sprintf(cstr_DebugMessage, "%s(char* cstr_text=%s) started.\n", __func__, cstr_text);
	OutputDebugString(cstr_DebugMessage);
#endif
	this->cstr_Text = new char[strlen(cstr_text) + 1];
	memset(this->cstr_Text, 0, (strlen(cstr_text) + 1) * sizeof(char));
	strcpy(this->cstr_Text, cstr_text);
	this->n_Length = strlen(cstr_text);
	this->n_Size = (this->n_Length + 1) * sizeof(char);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:Done\n.String::cstr_Text = %s\n", __func__, this->cstr_Text);
	OutputDebugString(cstr_DebugMessage);
#endif
}

String::~String()
{
	delete[] this->cstr_Text;
	this->cstr_Text = nullptr;

	this->n_Length = 0;
	this->n_Size = 0;
}

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
#ifdef STRING_DEBUG
	char cstr_DebugMessage[512];
	sprintf(cstr_DebugMessage, "%s started.\n", __func__);
	OutputDebugString(cstr_DebugMessage);
#endif
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:n_ResultLength = %d\n", __func__, n_ResultLength);
	OutputDebugString(cstr_DebugMessage);
#endif
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%d", this->cstr_Text, other);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:cstr_ResultText = %s\n", __func__, cstr_ResultText);
	OutputDebugString(cstr_DebugMessage);
#endif
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator+(int other)
{
#ifdef STRING_DEBUG
	char cstr_DebugMessage[512];
	sprintf(cstr_DebugMessage, "%s started.\n", __func__);
	OutputDebugString(cstr_DebugMessage);
#endif
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:n_ResultLength = %d\n", __func__, n_ResultLength);
	OutputDebugString(cstr_DebugMessage);
#endif
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%d", this->cstr_Text, other);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:cstr_ResultText = %s\n", __func__, cstr_ResultText);
	OutputDebugString(cstr_DebugMessage);
#endif
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator+(long other)
{
#ifdef STRING_DEBUG
	char cstr_DebugMessage[512];
	sprintf(cstr_DebugMessage, "%s started.\n", __func__);
	OutputDebugString(cstr_DebugMessage);
#endif
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:n_ResultLength = %d\n", __func__, n_ResultLength);
	OutputDebugString(cstr_DebugMessage);
#endif
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%d", this->cstr_Text, other);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:cstr_ResultText = %s\n", __func__, cstr_ResultText);
	OutputDebugString(cstr_DebugMessage);
#endif
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator+(float other)
{
#ifdef STRING_DEBUG
	char cstr_DebugMessage[512];
	sprintf(cstr_DebugMessage, "%s started.\n", __func__);
	OutputDebugString(cstr_DebugMessage);
#endif
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:n_ResultLength = %d\n", __func__, n_ResultLength);
	OutputDebugString(cstr_DebugMessage);
#endif
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%f", this->cstr_Text, other);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:cstr_ResultText = %s\n", __func__, cstr_ResultText);
	OutputDebugString(cstr_DebugMessage);
#endif
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}

String& String::operator+(double other)
{
#ifdef STRING_DEBUG
	char cstr_DebugMessage[512];
	sprintf(cstr_DebugMessage, "%s started.\n", __func__);
	OutputDebugString(cstr_DebugMessage);
#endif
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:n_ResultLength = %d\n", __func__, n_ResultLength);
	OutputDebugString(cstr_DebugMessage);
#endif
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%f", this->cstr_Text, other);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:cstr_ResultText = %s\n", __func__, cstr_ResultText);
	OutputDebugString(cstr_DebugMessage);
#endif
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
#ifdef STRING_DEBUG
	char cstr_DebugMessage[512];
	sprintf(cstr_DebugMessage, "%s started.\n", __func__);
	OutputDebugString(cstr_DebugMessage);
#endif
	int n_ResultLength = (strlen(this->cstr_Text) + strlen(other) + 1) * sizeof(char);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:n_ResultLength = %d\n", __func__, n_ResultLength);
	OutputDebugString(cstr_DebugMessage);
#endif
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%s", this->cstr_Text, other);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:cstr_ResultText = %s\n", __func__, cstr_ResultText);
	OutputDebugString(cstr_DebugMessage);
#endif
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}
String& String::operator+(const char* other)
{
#ifdef STRING_DEBUG
	char cstr_DebugMessage[512];
	sprintf(cstr_DebugMessage, "%s started.\n", __func__);
	OutputDebugString(cstr_DebugMessage);
#endif
	int n_ResultLength = (strlen(this->cstr_Text) + strlen(other) + 1) * sizeof(char);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:n_ResultLength = %d\n", __func__, n_ResultLength);
	OutputDebugString(cstr_DebugMessage);
#endif
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s%s", this->cstr_Text, other);
#ifdef STRING_DEBUG
	sprintf(cstr_DebugMessage, "%s:cstr_ResultText = %s\n", __func__, cstr_ResultText);
	OutputDebugString(cstr_DebugMessage);
#endif
	delete[] this->cstr_Text;
	this->cstr_Text = new char[n_ResultLength];
	memcpy(this->cstr_Text, cstr_ResultText, n_ResultLength);
	delete[] cstr_ResultText;
	return *this;
}
/*
String& String::operator+(unsigned short other)
{
	// TODO: insert return statement here
}

String& String::operator+(unsigned int other)
{
	// TODO: insert return statement here
}

String& String::operator+(unsigned long other)
{
	// TODO: insert return statement here
}

String& String::operator+(unsigned char other)
{
	// TODO: insert return statement here
}
*/
String& String::operator+(void* other)
{
	int n_ResultLength = (strlen(this->cstr_Text) + 64 + 1) * sizeof(char);
	char* cstr_ResultText = new char[n_ResultLength];
	memset(cstr_ResultText, 0, n_ResultLength);
	sprintf(cstr_ResultText, "%s0x%p", this->cstr_Text, other);
	
	delete[] cstr_ResultText;
	return *this;
}

String::operator char* ()
{
#ifdef STRING_DEBUG
	char cstr_DebugMessage[512];
	sprintf(cstr_DebugMessage, "String::operator char* started.\n");
	OutputDebugString(cstr_DebugMessage);
#endif
	return this->cstr_Text;
}
