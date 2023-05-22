#pragma once
#include<string>
#include<iostream>
#include"Header.h"
using namespace std;

class Document;
class TextEditor;

class Line
{
	friend class TextEditor;
	friend class Document;
	int size;
	char* Cs;
	static bool isChar(char);
	static bool islower(char);
	static bool isupper(char);
	static int STRLEN(string);
	static char tolower(char);
	static char toupper(char);
public:
	Line();
	Line(const Line&);
	void Load(ifstream& Rdr);
	void InsertCharAt_i(int i, char ch);
	void CharRemoverAt_i(int);
	int* SubStrings(string, int&, bool);
	bool IsAWord(string, const int);
	void AddPrefix(string, string, bool);
	void AddPostfix(string, string, bool);
	bool ReplaceFirst(string, string, bool);
	void ReplaceAll(string, string, bool);
	bool FindNextOnly(string, const int, int&, bool);
	bool FindPrevOnly(string, const int, int&, bool);
	int* FindNextAll(string, const int, int&, bool);
	int* FindPrevAll(string, const int, int&, bool);
	bool FindAndReplaceNextOnly(string, string, const int, int&, bool);
	bool FindAndReplacePrevOnly(string, string, const int, int&, bool);
	void FindAndReplaceNextAll(string, string, const int, int&, bool);
	void FindAndReplacePrevAll(string, string, const int, int&, bool);
	void PrintLine(int);
	void PrintLine(int, int);
	void Writer(ofstream&);
	~Line();
};