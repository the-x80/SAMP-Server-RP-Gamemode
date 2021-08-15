#ifndef JSON_DOCUMENT_H
#define JSON_DOCUMENT_H

class JSONDocumentEntry {


};

class JSONDocumentValue : public JSONDocumentEntry{
public:
	char* name;
	char* data;
};
class JSONDocumentObject : public JSONDocumentEntry {
public:
	Array<JSONDocumentEntry*> entries;
};
class JSONDocument {
private:
	char* rawText;
	Array<JSONDocumentEntry*> entries;
public:
	JSONDocument();
};





#endif

