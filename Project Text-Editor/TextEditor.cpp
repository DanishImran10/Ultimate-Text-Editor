#include"TextEditor.h"
#include"Document.h"
#include"Line.h"
#include<Windows.h>
#include<conio.h>
#include"Header.h"
#include<fstream>
using namespace std;

void gotoRowColT(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void PrintSpacesT(int rci, int sci)
{
	for (int i = sci; i < CCOLS; i++)
	{
		gotoRowColT(rci, i);
		cout << ' ';
	}
}

TextEditor::TextEditor()
{
	this->NODs = 0;
	this->CDoci;
	this->Doc = nullptr;
}

TextEditor::TextEditor(string fname)
{
	this->NODs = 0;
	this->CDoci;
	this->Doc = new Document[1]{ {"fname"} };
}

void TextEditor::Run()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	int cri = 0, cci = 0;
	int ch;
	cout << "\t\t\t\t\tWelcome To The Ultimate Text Editor!\n"
		<< "1. New File.\n"
		<< "2. Saved File.\n";
	int o;
	cin >> o;
	PrintSpacesT(0, 0);
	PrintSpacesT(1, 0);
	PrintSpacesT(2, 0);
	PrintSpacesT(3, 0);
	switch (o)
	{
	case 1:
		this->Doc = new Document[this->NODs + 1];
		this->NODs++;
		this->CDoci = this->NODs - 1;
		break;
	case 2:
		this->Doc = new Document[this->NODs + 1];
		this->NODs++;
		this->CDoci = this->NODs - 1;
		gotoRowColT(0, 0);
		cout << "Enter Filename: ";
		cin >> this->Doc[CDoci].DName;
		PrintSpacesT(0, 0);
		this->Doc[CDoci].Load(this->Doc[CDoci].DName);
		gotoRowColT(0, 0);
		this->Doc[CDoci].PrintDocument(0, 0);
		break;
	}
	while (true)
	{
		gotoRowColT(cri, cci);
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case UP:
					if (cri != 0)
						cri--;
					break;
				case DOWN:
					if (cri < this->Doc[CDoci].NOLs - 1)
						cri++;
					break;
				case RIGHT:
					if (cci < this->Doc[CDoci].Ls[cri].size - 1)
						cci++;
					break;
				case LEFT:
					if (cci != 0)
						cci--;
					break;
				}
				if (ch == 83)
				{
					this->Doc[CDoci].Ls[cri].CharRemoverAt_i(cci);
					gotoRowColT(cri, 0);
					this->Doc[CDoci].Ls[cri].PrintLine(0);
				}
			}
			else if (ch == 27)
			{
				gotoRowColT(48, 0);
				cout << "Enter Filename: ";
				cin >> this->Doc[CDoci].DName;
				ofstream Wtr(this->Doc[CDoci].DName);
				this->Doc[CDoci].SimpleUpdater(Wtr);
				return;
			}
			else if (ch == 15)
			{
				//ifstream Rdr("Document.txt");
				this->Doc[CDoci].Load("Document.txt");
			}
			else if (ch == 8 && cci != 0)
			{
				cci--;
				this->Doc[CDoci].Ls[cri].CharRemoverAt_i(cci);
				gotoRowColT(cri, 0);
				this->Doc[CDoci].Ls[cri].PrintLine(0);
			}
			else if (ch == 21)
			{
				string str;
				bool CaseSens;
				gotoRowColT(2, 92);
				cout << "Enter SubString:\n";
				gotoRowColT(3, 92);
				cin >> str;
				gotoRowColT(4, 92);
				cout << "Case Sensitivity(0/1): ";
				cin >> CaseSens;
				int* count = 0;
				int** subs = this->Doc[CDoci].FindAllSubStrings(str, count, CaseSens);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
				for (int i = 0; i < this->Doc[CDoci].NOLs; i++)
				{
					for (int j = 0; j < count[i]; j++)
					{
						gotoRowColT(i, subs[i][j]);
						cout << str;
					}
				}
				_getch();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				for (int i = 0; i < this->Doc[CDoci].NOLs; i++)
				{
					for (int j = 0; j < count[i]; j++)
					{
						gotoRowColT(i, subs[i][j]);
						cout << str;
					}
				}
				PrintSpacesT(2, 92);
				PrintSpacesT(3, 92);
				PrintSpacesT(4, 92);
			}
			else if (ch == 16)
			{
				string W, P;
				bool CaseSens;
				gotoRowColT(2, 92);
				cout << "Add Prefix:\n";
				gotoRowColT(3, 92);
				cout << "Enter The Word: ";
				cin >> W;
				gotoRowColT(4, 92);
				cout << "Enter Prefix: ";
				cin >> P;
				gotoRowColT(5, 92);
				cout << "Case Sensitivity(0/1): ";
				cin >> CaseSens;
				this->Doc[CDoci].Prefix(W, P, CaseSens);
				gotoRowColT(0, 0);
				this->Doc[CDoci].PrintDocument(0, 0);
				_getch();
				PrintSpacesT(2, 92);
				PrintSpacesT(3, 92);
				PrintSpacesT(4, 92);
				PrintSpacesT(5, 92);
			}
			else if (ch == 17)
			{
				string W, P;
				bool CaseSens;
				gotoRowColT(2, 92);
				cout << "Add Postfix:\n";
				gotoRowColT(3, 92);
				cout << "Enter The Word: ";
				cin >> W;
				gotoRowColT(4, 92);
				cout << "Enter Postfix: ";
				cin >> P;
				gotoRowColT(5, 92);
				cout << "Case Sensitivity(0/1): ";
				cin >> CaseSens;
				this->Doc[CDoci].PostFix(W, P, CaseSens);
				gotoRowColT(0, 0);
				this->Doc[CDoci].PrintDocument(0, 0);
				_getch();
				PrintSpacesT(2, 92);
				PrintSpacesT(3, 92);
				PrintSpacesT(4, 92);
				PrintSpacesT(5, 92);
			}
			else if (ch == 18)
			{
				string W, R;
				bool CaseSens;
				char n = 'F';
				gotoRowColT(2, 92);
				cout << "Replace A Word:\n";
				gotoRowColT(3, 92);
				cout << "Replace First Or All (F/A): ";
				cin >> n;
				gotoRowColT(4, 92);
				cout << "Enter Word: ";
				cin >> W;
				gotoRowColT(5, 92);
				cout << "Enter Replacement: ";
				cin >> R;
				gotoRowColT(6, 92);
				cout << "Case Sensitivity(0/1): ";
				cin >> CaseSens;
				switch (n)
				{
				case 'F':
					this->Doc[CDoci].FindAndReplaceFirst(W, R, CaseSens);
					gotoRowColT(0, 0);
					this->Doc[CDoci].PrintDocument(0, 0);
					_getch();
					PrintSpacesT(2, 92);
					PrintSpacesT(3, 92);
					PrintSpacesT(4, 92);
					PrintSpacesT(5, 92);
					PrintSpacesT(6, 92);
					break;
				case 'A':
					this->Doc[CDoci].FindAndReplaceAll(W, R, CaseSens);
					gotoRowColT(0, 0);
					this->Doc[CDoci].PrintDocument(0, 0);
					_getch();
					PrintSpacesT(2, 92);
					PrintSpacesT(3, 92);
					PrintSpacesT(4, 92);
					PrintSpacesT(5, 92);
					PrintSpacesT(6, 92);
					break;
				default:
					break;
				}
			}
			else if (ch == 7)
			{
				string W;
				int i = 0, opt, * count = nullptr;
				bool f, CaseSens;
				int** F;
				gotoRowColT(2, 92);
				cout << "Find A Word:";
				gotoRowColT(3, 92);
				cout << "1. Find Next Only";
				gotoRowColT(4, 92);
				cout << "2. Find Next All";
				gotoRowColT(5, 92);
				cout << "3. Find Prev Only";
				gotoRowColT(6, 92);
				cout << "4. Find Prev All";
				gotoRowColT(7, 92);
				cin >> opt;
				PrintSpacesT(3, 92);
				PrintSpacesT(4, 92);
				PrintSpacesT(5, 92);
				PrintSpacesT(6, 92);
				PrintSpacesT(7, 92);
				gotoRowColT(3, 92);
				switch (opt)
				{
				case 1:
					cout << "Find Next Only";
					gotoRowColT(4, 92);
					cout << "Enter The Word: ";
					cin >> W;
					gotoRowColT(5, 92);
					cout << "Case Sensitivity(0/1): ";
					cin >> CaseSens;
					f = this->Doc[CDoci].FindNext(W, cri, cci, i, CaseSens);
					if (f)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
						gotoRowColT(cri, i);
						cout << W;
						_getch();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
						gotoRowColT(cri, i);
						this->Doc[CDoci].PrintDocument(cri, i);
					}
					gotoRowColT(cri, i);
					PrintSpacesT(2, 92);
					PrintSpacesT(3, 92);
					PrintSpacesT(4, 92);
					PrintSpacesT(5, 92);
					break;
				case 2:
					cout << "Find Next All";
					gotoRowColT(4, 92);
					cout << "Enter The Word: ";
					cin >> W;
					gotoRowColT(5, 92);
					cout << "Case Sensitivity(0/1): ";
					cin >> CaseSens;
					F = this->Doc[CDoci].FindAllNext(W, cri, cci, count, CaseSens);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
					for (int j = cri; j < this->Doc[CDoci].NOLs; j++)
					{
						for (int fi = 0; fi < count[j]; fi++)
						{
							gotoRowColT(j, F[j][fi]);
							cout << W;
						}
					}
					_getch();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
					for (int j = cri; j < this->Doc[CDoci].NOLs; j++)
					{
						for (int fi = 0; fi < count[j]; fi++)
						{
							gotoRowColT(j, F[j][fi]);
							this->Doc[CDoci].PrintDocument(j, F[j][fi]);
						}
					}
					gotoRowColT(cri, cci);
					PrintSpacesT(2, 92);
					PrintSpacesT(3, 92);
					PrintSpacesT(4, 92);
					PrintSpacesT(5, 92);
					break;
				case 3:
					cout << "Find Prev Only";
					gotoRowColT(4, 92);
					cout << "Enter The Word: ";
					cin >> W;
					gotoRowColT(5, 92);
					cout << "Case Sensitivity(0/1): ";
					cin >> CaseSens;
					f = this->Doc[CDoci].FindPrev(W, cri, cci, i, CaseSens);
					if (f)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
						gotoRowColT(cri, i);
						cout << W;
						_getch();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
						gotoRowColT(cri, i);
						this->Doc[CDoci].PrintDocument(cri, i);
					}
					gotoRowColT(cri, i);
					PrintSpacesT(2, 92);
					PrintSpacesT(3, 92);
					PrintSpacesT(4, 92);
					PrintSpacesT(5, 92);
					break;
				case 4:
					cout << "Find Prev All";
					gotoRowColT(4, 92);
					cout << "Enter The Word: ";
					cin >> W;
					gotoRowColT(5, 92);
					cout << "Case Sensitivity(0/1): ";
					cin >> CaseSens;
					F = this->Doc[CDoci].FindAllPrev(W, cri, cci, count, CaseSens);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
					for (int j = cri; j >= 0; j--)
					{
						for (int fi = 0; fi < count[j]; fi++)
						{
							gotoRowColT(j, F[j][fi]);
							cout << W;
						}
					}
					_getch();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
					for (int j = cri; j >= 0; j--)
					{
						for (int fi = 0; fi < count[j]; fi++)
						{
							gotoRowColT(j, F[j][fi]);
							this->Doc[CDoci].PrintDocument(j, F[j][fi]);
						}
					}
					gotoRowColT(cri, cci);
					PrintSpacesT(2, 92);
					PrintSpacesT(3, 92);
					PrintSpacesT(4, 92);
					PrintSpacesT(5, 92);
					break;
				}
			}
			else if (ch == 9)
			{
				int opt, i = 0, * count = nullptr;
				string W, R;
				bool CaseSens;
				gotoRowColT(2, 92);
				cout << "Find & Replace:";
				gotoRowColT(3, 92);
				cout << "1. Next Only";
				gotoRowColT(4, 92);
				cout << "2. Next All";
				gotoRowColT(5, 92);
				cout << "3. Previous Only";
				gotoRowColT(6, 92);
				cout << "4. Previous All";
				gotoRowColT(7, 92);
				cin >> opt;
				for (int i = 3; i < 8; i++)
					PrintSpacesT(i, 92);
				switch (opt)
				{
				case 1:
					gotoRowColT(3, 92);
					cout << "Next Only:";
					gotoRowColT(4, 92);
					cout << "Enter The Word: ";
					cin >> W;
					gotoRowColT(5, 92);
					cout << "Enter Replacement: ";
					cin >> R;
					gotoRowColT(6, 92);
					cout << "Case Sensitivity(0/1): ";
					cin >> CaseSens;
					this->Doc[CDoci].FindReplaceNext(W, R, cri, cci, i, CaseSens);
					for (int i = 2; i < 7; i++)
						PrintSpacesT(i, 92);
					gotoRowColT(cri, cci);
					this->Doc[CDoci].PrintDocument(cri, cci);
					gotoRowColT(cri, cci);
					break;
				case 2:
					gotoRowColT(3, 92);
					cout << "Next All:";
					gotoRowColT(4, 92);
					cout << "Enter The Word: ";
					cin >> W;
					gotoRowColT(5, 92);
					cout << "Enter Replacement: ";
					cin >> R;
					gotoRowColT(6, 92);
					cout << "Case Sensitivity(0/1): ";
					cin >> CaseSens;
					this->Doc[CDoci].FindReplaceAllNext(W, R, cri, cci, count, CaseSens);
					for (int i = 2; i < 7; i++)
						PrintSpacesT(i, 92);
					gotoRowColT(cri, cci);
					this->Doc[CDoci].PrintDocument(cri, cci);
					gotoRowColT(cri, cci);
					break;
				case 3:
					gotoRowColT(3, 92);
					cout << "Previous Only:";
					gotoRowColT(4, 92);
					cout << "Enter The Word: ";
					cin >> W;
					gotoRowColT(5, 92);
					cout << "Enter Replacement: ";
					cin >> R;
					gotoRowColT(6, 92);
					cout << "Case Sensitivity(0/1): ";
					cin >> CaseSens;
					this->Doc[CDoci].FindReplacePrev(W, R, cri, cci, i, CaseSens);
					for (int i = 2; i < 7; i++)
						PrintSpacesT(i, 92);
					gotoRowColT(cri, cci);
					this->Doc[CDoci].PrintDocument(cri, cci);
					gotoRowColT(cri, cci);
					break;
				case 4:
					gotoRowColT(3, 92);
					cout << "Previous All:";
					gotoRowColT(4, 92);
					cout << "Enter The Word: ";
					cin >> W;
					gotoRowColT(5, 92);
					cout << "Enter Replacement: ";
					cin >> R;
					gotoRowColT(6, 92);
					cout << "Case Sensitivity(0/1): ";
					cin >> CaseSens;
					this->Doc[CDoci].FindReplaceAllPrev(W, R, cri, cci, count, CaseSens);
					for (int i = 2; i < 7; i++)
						PrintSpacesT(i, 92);
					gotoRowColT(cri, cci);
					this->Doc[CDoci].PrintDocument(cri, cci);
					gotoRowColT(cri, cci);
					break;
				}
			}
			else if (ch == 13)
			{
				this->Doc[CDoci].Enter_AddNewLine(cri, cci);
				this->Doc[CDoci].PrintDocument(cri, cci);
				cri++;
				cci = 0;
				gotoRowColT(cri, cci);
			}
			else if (ch == 8 && cci == 0)
			{
				if (this->Doc[CDoci].Ls[cri].size + this->Doc[CDoci].Ls[cri - 1].size - 1 < COLS)
				{
					cci = this->Doc[CDoci].Ls[cri - 1].size - 1;
					this->Doc[CDoci].BackSpace_LineRemover(cri);
					cri--;
					gotoRowColT(cri, cci);
					this->Doc[CDoci].PrintDocument(cri, cci);
					PrintSpacesT(cri + 1, 0);
					gotoRowColT(cri, cci);
				}
			}
			else if (ch == 5)
			{
				string S;
				bool CaseSens;
				gotoRowColT(48, 0);
				getline(cin, S);
				gotoRowColT(49, 0);
				cout << "Case Sensitivity(0/1): ";
				cin >> CaseSens;
				int length = this->Doc[CDoci].strLEN(S);
				int FI, fi;
				bool c = this->Doc[CDoci].FindSentence(S, FI, fi, CaseSens);
				if (c)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
					gotoRowColT(FI, fi);
					this->Doc[CDoci].PrintDocument(FI, fi, fi + length);
					_getch();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
					gotoRowColT(FI, fi);
					this->Doc[CDoci].PrintDocument(FI, fi, fi + length);
				}
			}
			else if (ch == 14)
			{
				gotoRowColT(47, 0);
				cout << "Enter File To Open: ";
				string n;
				cin >> n;
				this->OpenMultipleDocs(n);
				PrintSpacesT(47, 0);
			}
			else if (ch == 20)
			{
				if (this->CDoci < this->NODs)
				{
					this->CDoci++;
					if (this->CDoci < this->NODs)
					{

						this->Doc[CDoci].PrintDocument(0, 0, 0, 0);
					}
					else
					{
						CDoci = 0;
						system("cls");
						this->Doc[CDoci].PrintDocument(0, 0, 0, 0);
					}
				}
			}
			else if (ch == 25)
			{
				gotoRowColT(2, 92);
				cout << "Merge Docs:";
				gotoRowColT(3, 92);
				cout << "Enter Docs To Merge: ";
				int a, b;
				cin >> a >> b;
				gotoRowColT(4, 92);
				cout << "Enter Filename:";
				gotoRowColT(5, 92);
				string fname;
				cin >> fname;
				MergeDocs(Doc[a], Doc[b], fname);
				this->Doc[this->NODs - 1].PrintDocument(0, 0, 0, 0);
			}
			else if (ch == 23)
			{
				gotoRowColT(2, 92);
				cout << "Doc Features: \n";
				gotoRowColT(3, 92);
				int wc = Doc[CDoci].WordCount();
				cout << "Word Count: " << wc;
				gotoRowColT(4, 92);
				int spc = Doc[CDoci].SpecialCharCount();
				cout << "Special Char Count: " << spc;
				gotoRowColT(5, 92);
				int sc = Doc[CDoci].SentencesCount();
				cout << "Sentence Count: " << sc;
				gotoRowColT(6, 92);
				int pc = Doc[CDoci].ParagraphCount();
				cout << "Paragraph Count: " << pc;
				gotoRowColT(7, 92);
				double wl = Doc[CDoci].AvgWordLen();
				cout << "Avg Word Length: " << wl;
				gotoRowColT(8, 92);
				int swl = Doc[CDoci].SmallestWordLen();
				cout << "Smallest Word Len: " << swl;
				gotoRowColT(9, 92);
				int lwl = Doc[CDoci].LargestWordLength();
				cout << "Largest Word Len: " << lwl;
				_getch();
				for (int i = 2; i < 10; i++)
					PrintSpacesT(i, 92);
			}
			else if (ch == 26)
			{
				this->ShortcutsPrinter();
				_getch();
				for (int i = 2; i < 14; i++)
					PrintSpacesT(i, 92);
			}
			else
			{
				if (cci == COLS - 1)
				{
					int e = cci;
					for (; e >= 0; e--)
					{
						if (this->Doc[CDoci].Ls[cri].Cs[e] == ' ')
							break;
					}
					this->Doc[CDoci].Enter_AddNewLine(cri, e + 1);
					PrintSpacesT(cri, e + 1);
					cri++;
					cci -= e + 1;
					gotoRowColT(cri, cci);
				}
				this->Doc[CDoci].Ls[cri].InsertCharAt_i(cci, ch);
				cci++;
				gotoRowColT(cri, 0);
				this->Doc[CDoci].Ls[cri].PrintLine(0);
			}
		}
	}
}

void TextEditor::ShortcutsPrinter()
{
	gotoRowColT(2, 92);
	cout << "Keyboard Shortcuts:\n";
	gotoRowColT(3, 92);
	cout << "Find Substring: CTRL + S\n";
	gotoRowColT(4, 92);
	cout << "Add Prefix:     CTRL + P\n";
	gotoRowColT(5, 92);
	cout << "Add Postfix:    CTRL + Q\n";
	gotoRowColT(6, 92);
	cout << "Replace:        CTRL + R\n";
	gotoRowColT(7, 92);
	cout << "Find:           CTRL + G\n";
	gotoRowColT(8, 92);
	cout << "Find & Replace: CTRL + I\n";
	gotoRowColT(9, 92);
	cout << "Find Sentence:  CTRL + E\n";
	gotoRowColT(10, 92);
	cout << "Doc Features:   CTRL + W\n";
	gotoRowColT(11, 92);
	cout << "OpenMultipeDocs:CTRL + N\n";
	gotoRowColT(12, 92);
	cout << "Switch Docs:    CTRL + T\n";
	gotoRowColT(13, 92);
	cout << "Save Doc:       Esc\n";
}

void TextEditor::OpenMultipleDocs(string fname)
{
	ifstream Rdr(fname);
	Document* HA = new Document[this->NODs + 1];
	for (int i = 0; i < this->NODs; i++)
	{
		HA[i].NOLs = this->Doc[i].NOLs;
		HA[i].Ls = new Line[HA[i].NOLs];
		for (int j = 0; j < HA[i].NOLs; j++)
		{
			HA[i].Ls[j].size = this->Doc[i].Ls[j].size;
			HA[i].Ls[j].Cs = new char[HA[i].Ls[j].size];
			for (int k = 0; k < HA[i].Ls[j].size; k++)
			{
				HA[i].Ls[j].Cs[k] = this->Doc[i].Ls[j].Cs[k];
			}
		}
	}
	Rdr >> HA[this->NODs].NOLs;
	Rdr.ignore();
	HA[this->NODs].Ls = new Line[HA[this->NODs].NOLs];
	for (int i = 0; i < HA[this->NODs].NOLs; i++)
	{
		HA[this->NODs].Ls[i].Load(Rdr);
	}
	HA[this->NODs].DName = fname;
	this->NODs++;
	delete[] this->Doc;
	this->Doc = HA;
}

void TextEditor::MergeDocs(Document D1, Document D2, string fname)
{
	Document* HA = new Document[this->NODs + 1];
	for (int i = 0; i < this->NODs; i++)
	{
		HA[i].NOLs = this->Doc[i].NOLs;
		HA[i].Ls = new Line[HA[i].NOLs];
		for (int j = 0; j < HA[i].NOLs; j++)
		{
			HA[i].Ls[j].size = this->Doc[i].Ls[j].size;
			HA[i].Ls[j].Cs = new char[HA[i].Ls[j].size];
			for (int k = 0; k < HA[i].Ls[j].size; k++)
			{
				HA[i].Ls[j].Cs[k] = this->Doc[i].Ls[j].Cs[k];
			}
		}
	}
	HA[this->NODs].NOLs = D1.NOLs + D2.NOLs;
	HA[this->NODs].Ls = new Line[HA[this->NODs].NOLs];
	int n = 0;
	for (int i = 0; i < D1.NOLs; i++, n++)
	{
		HA[this->NODs].Ls[n].size = D1.Ls[i].size;
		HA[this->NODs].Ls[n].Cs = new char[HA[this->NODs].Ls[i].size];
		for (int j = 0; j < HA[this->NODs].Ls[n].size; j++)
		{
			HA[this->NODs].Ls[n].Cs[j] = D1.Ls[n].Cs[j];
		}
	}
	for (int i = 0; i < D2.NOLs; i++, n++)
	{
		HA[this->NODs].Ls[n].size = D2.Ls[i].size;
		HA[this->NODs].Ls[n].Cs = new char[HA[this->NODs].Ls[i].size];
		for (int j = 0; j < HA[this->NODs].Ls[n].size; j++)
		{
			HA[this->NODs].Ls[n].Cs[j] = D2.Ls[i].Cs[j];
		}
	}
	HA[this->NODs].DName = fname;
	this->NODs++;
	delete[] this->Doc;
	this->Doc = HA;
}
