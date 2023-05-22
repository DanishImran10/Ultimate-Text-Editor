#pragma once
#include<iostream>
#include<string>
using namespace std;

class Line;
class TextEditor;
class Document
{
	friend class TextEditor;
	friend class Line;
	Line* Ls;
	int NOLs;
	string DName;
	int dri = 0, dci = 0;
	int strLEN(string);
public:
	Document();
	Document(string);
	void DeepCopy(const Document&);
	void Load(string);
	void LoadEncodedFile(string Fname, const string);
	void SimpleUpdater(ofstream&);
	string UpdaterEncodedFiles(ofstream&, bool&);
	void Enter_AddNewLine(int, int);
	void BackSpace_LineRemover(int);
	double AvgWordLen();
	int SmallestWordLen();
	int LargestWordLength();
	int WordCount();
	int SpecialCharCount();
	int SentencesCount();
	int ParagraphCount();
	int** FindAllSubStrings(string, int*&, bool);
	void Prefix(string, string, bool);
	void PostFix(string, string, bool);
	void FindAndReplaceFirst(string, string, bool);
	void FindAndReplaceAll(string, string, bool);
	bool FindNext(string, const int, const int, int&, bool);
	bool FindPrev(string, const int, const int, int&, bool);
	int** FindAllNext(string, const int, const int, int*&, bool);
	int** FindAllPrev(string, const int, const int, int*&, bool);
	void FindReplaceNext(string, string, int, int, int&, bool);
	void FindReplacePrev(string, string, int, int, int&, bool);
	void FindReplaceAllNext(string, string, int, int, int*&, bool);
	void FindReplaceAllPrev(string, string, int, int, int*&, bool);
	bool FindSentence(string, int&, int&, bool);
	void PrintDocument(int, int);
	void PrintDocument(int, int, int);
	void PrintDocument(int, int, int, int);
	~Document();
};
