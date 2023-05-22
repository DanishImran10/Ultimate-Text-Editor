#pragma once
#include<string>
using namespace std;

class Line;
class Document;

class TextEditor
{
	friend class Document;
	friend class Line;
	int CRow = 0, CCol = 0, NODs, CDoci;
	Document* Doc;
public:
	TextEditor();
	TextEditor(string);
	void Run();
	void ShortcutsPrinter();
	void OpenMultipleDocs(string);
	void MergeDocs(Document, Document, string);
};
