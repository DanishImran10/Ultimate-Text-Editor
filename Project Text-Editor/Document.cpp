#include"Document.h"
#include"Line.h"
#include"Header.h"
#include<fstream>
using namespace std;

void gotoRowColD(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void PrintSpacesD(int rci, int sci)
{
	for (int i = sci; i < CCOLS; i++)
	{
		gotoRowColD(rci, i);
		cout << ' ';
	}
}

int Document::strLEN(string str)
{
	int count = 0, i = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	return count;
}


Document::Document()
{
	this->NOLs = 1;
	this->Ls = new Line[1];
}


Document::Document(string fname)
{
	this->NOLs = 1;
	this->Ls = new Line[1];
	this->DName = fname;
}

void Document::DeepCopy(const Document& D)
{
	this->NOLs = D.NOLs;
	this->DName = D.DName;
	this->Ls = new Line[this->NOLs];
	for (int i = 0; i < this->NOLs; i++)
	{
		this->Ls[i].size = D.Ls[i].size;
		this->Ls[i].Cs = new char[this->Ls[i].size];
		for (int j = 0; j < this->Ls[i].size; j++)
		{
			this->Ls[i].Cs[j] = D.Ls[i].Cs[j];
		}
	}
}

void Document::Load(string Fname)
{
	ifstream Rdr(Fname);
	if (!Rdr)
		cout << "not reading";
	Rdr >> this->NOLs;
	Rdr.ignore();
	this->Ls = new Line[this->NOLs];
	for (int i = 0; i < this->NOLs; i++)
	{
		this->Ls[i].Load(Rdr);
	}
}

void Document::LoadEncodedFile(string Fname, const string PASS)
{
	ifstream Rdr(Fname);
	gotoRowColD(0, 0);
	cout << "Enter Password: ";
	string pass;
	cin >> pass;
	if (pass == PASS)
	{
		system("cls");
		for (int i = 0; i < this->NOLs; i++)
			for (int j = 0; j < this->Ls[i].size; j++)
			{
				this->Ls[i].Cs[j] -= 30;
				Rdr >> this->Ls[i].Cs[j];
			}
	}
	else
		cout << "\nWrong Password!\n";
}

void Document::SimpleUpdater(ofstream& Wtr)
{
	Wtr << this->NOLs << endl;
	for (int i = 0; i < this->NOLs; i++)
		Ls[i].Writer(Wtr);
}

string Document::UpdaterEncodedFiles(ofstream& Wtr, bool& newcheck)
{
	static bool check = true;
	for (int i = 0; i < this->NOLs; i++)
	{
		for (int j = 0; j < this->Ls[i].size; j++)
		{
			this->Ls[i].Cs[j] += 30;
		}
		Ls[i].Writer(Wtr);
	}
	static string Pass;
	if (check && newcheck)
	{
		gotoRowColD(28, 0);
		cout << "Enter Password: ";
		cin >> Pass;
		check = false;
		newcheck = false;
	}
	return Pass;
}

void Document::Enter_AddNewLine(int ri, int ci)
{
	Line* HA = new Line[this->NOLs + 1];
	int i = 0;
	for (; i < ri; i++)
	{
		HA[i].size = this->Ls[i].size;
		HA[i].Cs = new char[HA[i].size];
		for (int j = 0; j < HA[i].size; j++)
			HA[i].Cs[j] = this->Ls[i].Cs[j];
	}

	HA[i].size = ci + 1;
	HA[i].Cs = new char[HA[i].size];
	int j = 0;
	for (; j < HA[i].size - 1; j++)
		HA[i].Cs[j] = this->Ls[i].Cs[j];
	HA[i].Cs[j] = '\0';

	HA[i + 1].size = this->Ls[i].size - ci;
	HA[i + 1].Cs = new char[HA[i + 1].size];
	for (int k = 0; k < HA[i + 1].size; j++, k++)
		HA[i + 1].Cs[k] = this->Ls[i].Cs[j];

	for (i++; i < this->NOLs; i++)
	{
		HA[i + 1].size = this->Ls[i].size;
		HA[i + 1].Cs = new char[HA[i + 1].size];
		for (int k = 0; k < HA[i + 1].size; k++)
			HA[i + 1].Cs[k] = this->Ls[i].Cs[k];
	}
	delete[] this->Ls;
	this->NOLs++;
	this->Ls = HA;
}

void Document::BackSpace_LineRemover(int Ln)
{
	Line* HA = new Line[this->NOLs - 1];
	int i = 0;
	for (; i < Ln - 1; i++)
	{
		HA[i].size = this->Ls[i].size;
		HA[i].Cs = new char[HA[i].size];
		for (int j = 0; j < HA[i].size; j++)
			HA[i].Cs[j] = this->Ls[i].Cs[j];
	}

	HA[i].size = this->Ls[i].size + this->Ls[Ln].size - 1;
	HA[i].Cs = new char[HA[i].size];
	int j = 0;
	for (; j < this->Ls[i].size - 1; j++)
		HA[i].Cs[j] = this->Ls[i].Cs[j];
	for (int k = 0; k < this->Ls[Ln].size; j++, k++)
		HA[i].Cs[j] = this->Ls[Ln].Cs[k];

	for (i++; i < this->NOLs - 1; i++)
	{
		HA[i].size = this->Ls[i + 1].size;
		HA[i].Cs = new char[HA[i].size];
		for (int k = 0; k < HA[i].size; k++)
			HA[i].Cs[k] = this->Ls[i + 1].Cs[k];
	}

	delete[] this->Ls;
	this->NOLs--;
	this->Ls = HA;
}

double Document::AvgWordLen()
{
	int WordCount = 0, AlphaCount = 0;
	for (int i = 0; i < this->NOLs; i++)
		for (int j = 0; j < this->Ls[i].size; j++)
		{
			if ((this->Ls[i].Cs[j] == ' ' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == '.' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == ',' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == '?' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == '/' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == ':' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == ';' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == '!' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == '\0' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1])))
			{
				WordCount++;
			}
			if (this->Ls[i].isChar(this->Ls[i].Cs[j]))
				AlphaCount++;
		}
	double Avg = (double)AlphaCount / WordCount;
	return Avg;
}

int Document::SmallestWordLen()
{
	int templen = 0;
	bool check1, check2 = true;
	for (int i = 0; i < this->NOLs; i++)
		for (int j = 0; j < this->Ls[i].size; )
		{
			check1 = true;
			if (this->Ls[i].isChar(this->Ls[i].Cs[j]) && check1)
			{
				for (int k = j + 1; k < this->Ls[i].size; k++)
				{
					if ((this->Ls[i].Cs[k] == ' ' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == '.' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == ',' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == '?' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == '/' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == ':' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == ';' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == '!' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == '\0' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1])))
					{
						int l = k - j;
						if (check2)
						{
							check2 = false;
							templen = l;
						}
						if (l < templen)
							templen = l;
						j += l - 1;
						check1 = false;
						break;
					}
				}
			}
			j++;
		}
	return templen;
}

int Document::LargestWordLength()
{
	int templen = 0;
	bool check;
	for (int i = 0; i < this->NOLs; i++)
		for (int j = 0; j < this->Ls[i].size; )
		{
			check = true;
			if (this->Ls[i].isChar(this->Ls[i].Cs[j]) && check)
			{
				for (int k = j + 1; k < this->Ls[i].size; k++)
				{
					if ((this->Ls[i].Cs[k] == ' ' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == '.' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == ',' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == '?' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == '/' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == ':' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == ';' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == '!' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1]))
						|| (this->Ls[i].Cs[k] == '\0' && this->Ls[i].isChar(this->Ls[i].Cs[k - 1])))
					{
						int l = k - j;
						if (l > templen)
							templen = l;
						j += l - 1;
						check = false;
						break;
					}
				}
			}
			j++;
		}
	return templen;
}

int Document::WordCount()
{
	int count = 0;
	for (int i = 0; i < this->NOLs; i++)
		for (int j = 0; j < this->Ls[i].size; j++)
		{
			if ((this->Ls[i].Cs[j] == ' ' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == '.' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == ',' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == '?' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == '/' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == ':' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == ';' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == '!' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1]))
				|| (this->Ls[i].Cs[j] == '\0' && this->Ls[i].isChar(this->Ls[i].Cs[j - 1])))
				count++;
		}
	return count;
}

int Document::SpecialCharCount()
{
	int count = 0;
	for (int i = 0; i < this->NOLs; i++)
		for (int j = 0; j < this->Ls[i].size; j++)
		{
			if (this->Ls[i].Cs[j] == '.' || this->Ls[i].Cs[j] == ',' || this->Ls[i].Cs[j] == '?' || this->Ls[i].Cs[j] == '!'
				|| this->Ls[i].Cs[j] == ';' || this->Ls[i].Cs[j] == ':' || this->Ls[i].Cs[j] == '/' || this->Ls[i].Cs[j] == '@'
				|| this->Ls[i].Cs[j] == '#' || this->Ls[i].Cs[j] == '%' || this->Ls[i].Cs[j] == '`' || this->Ls[i].Cs[j] == '-'
				|| this->Ls[i].Cs[j] == '_' || this->Ls[i].Cs[j] == '^' || this->Ls[i].Cs[j] == '&' || this->Ls[i].Cs[j] == '*'
				|| this->Ls[i].Cs[j] == '=' || this->Ls[i].Cs[j] == '~' || this->Ls[i].Cs[j] == '<' || this->Ls[i].Cs[j] == '>')
				count++;
		}
	return count;
}

int Document::SentencesCount()
{
	int count = 0;
	for (int i = 0; i < this->NOLs; i++)
		for (int j = 0; j < this->Ls[i].size; j++)
		{
			if (this->Ls[i].Cs[j] == '.' || this->Ls[i].Cs[j] == '?' || this->Ls[i].Cs[j] == '!')
				count++;
		}
	return count;
}

int Document::ParagraphCount()
{
	int count = 1;
	for (int i = 0; i + 1 < this->NOLs; i++)
	{
		if (this->Ls[i].Cs[0] == '\0' && this->Ls[i + 1].Cs[0] == '\0')
			count++;
	}
	return count;
}

int** Document::FindAllSubStrings(string Tofind, int*& count, bool CaseSens)
{
	int** Si = new int* [this->NOLs];
	count = new int[this->NOLs]{};
	for (int i = 0; i < this->NOLs; i++)
		Si[i] = this->Ls[i].SubStrings(Tofind, count[i], CaseSens);
	return Si;
}

void Document::Prefix(string Tofind, string Prefix, bool CaseSens)
{
	for (int i = 0; i < this->NOLs; i++)
		this->Ls[i].AddPrefix(Tofind, Prefix, CaseSens);
}

void Document::PostFix(string Tofind, string Postfix, bool CaseSens)
{
	for (int i = 0; i < this->NOLs; i++)
		this->Ls[i].AddPostfix(Tofind, Postfix, CaseSens);
}

void Document::FindAndReplaceFirst(string Tofind, string Toreplace, bool CaseSens)
{
	for (int i = 0; i < this->NOLs; i++)
	{
		bool f = this->Ls[i].ReplaceFirst(Tofind, Toreplace, CaseSens);
		if (f)
			return;
	}
}

void Document::FindAndReplaceAll(string Tofind, string Toreplace, bool CaseSens)
{
	for (int i = 0; i < this->NOLs; i++)
		this->Ls[i].ReplaceAll(Tofind, Toreplace, CaseSens);
}

bool Document::FindNext(string Tofind, const int ri, const int ci, int& fi, bool CaseSens)
{
	for (int i = ri; i < this->NOLs; i++)
		if (this->Ls[i].FindNextOnly(Tofind, ci, fi, CaseSens))
			return true;
	return false;
}

bool Document::FindPrev(string Tofind, const int ri, const int ci, int& fi, bool CaseSens)
{
	for (int i = ri; i >= 0; i--)
		if (this->Ls[i].FindPrevOnly(Tofind, ci, fi, CaseSens))
			return true;
	return false;
}

int** Document::FindAllNext(string Tofind, const int ri, const int ci, int*& count, bool CaseSens)
{
	int** FI = new int* [this->NOLs - ri];
	count = new int[this->NOLs - ri]{};
	FI[0] = this->Ls[ri].FindNextAll(Tofind, ci, count[0], CaseSens);
	for (int i = ri + 1, j = 1; i < this->NOLs; i++, j++)
		FI[j] = this->Ls[i].FindNextAll(Tofind, 0, count[j], CaseSens);
	return FI;
}

int** Document::FindAllPrev(string Tofind, const int ri, const int ci, int*& count, bool CaseSens)
{
	int** FI = new int* [ri + 1];
	count = new int[ri + 1]{};
	FI[ri] = this->Ls[ri].FindPrevAll(Tofind, ci, count[ri], CaseSens);
	for (int i = ri - 1; i >= 0; i--)
		FI[i] = this->Ls[i].FindPrevAll(Tofind, this->Ls[i].size - 1, count[i], CaseSens);
	return FI;
}

void Document::FindReplaceNext(string Tofind, string Toreplace, int cr, int cc, int& fi, bool CaseSens)
{
	bool c = this->Ls[cr].FindAndReplaceNextOnly(Tofind, Toreplace, cc, fi, CaseSens);
	if (c)
		return;
	for (int i = cr + 1; i < this->NOLs; i++)
	{
		c = this->Ls[i].FindAndReplaceNextOnly(Tofind, Toreplace, 0, fi, CaseSens);
		if (c)
			return;
	}
}

void Document::FindReplacePrev(string Tofind, string Toreplace, int cr, int cc, int& fi, bool CaseSens)
{
	bool c = this->Ls[cr].FindAndReplacePrevOnly(Tofind, Toreplace, cc, fi, CaseSens);
	if (c)
		return;
	for (int i = cr - 1; i >= 0; i--)
	{
		bool c = this->Ls[i].FindAndReplacePrevOnly(Tofind, Toreplace, 0, fi, CaseSens);
		if (c)
			return;
	}
}

void Document::FindReplaceAllNext(string Tofind, string Toreplace, int cr, int cc, int*& count, bool CaseSens)
{
	count = new int[this->NOLs - cr]{};
	this->Ls[cr].FindAndReplaceNextAll(Tofind, Toreplace, cc, count[0], CaseSens);
	for (int i = cr + 1, j = 1; i < this->NOLs; i++, j++)
		this->Ls[i].FindAndReplaceNextAll(Tofind, Toreplace, 0, count[j], CaseSens);
}

void Document::FindReplaceAllPrev(string Tofind, string Toreplace, int cr, int cc, int*& count, bool CaseSens)
{
	count = new int[cr + 1]{};
	this->Ls[cr].FindAndReplacePrevAll(Tofind, Toreplace, cc, count[cr], CaseSens);
	for (int i = cr - 1; i >= 0; i--)
		this->Ls[i].FindAndReplacePrevAll(Tofind, Toreplace, this->Ls[i].size - 1, count[i], CaseSens);
}

bool Document::FindSentence(string Tofind, int& FI, int& fi, bool CaseSens)
{
	int length = this->strLEN(Tofind);
	bool check1;
	for (int i = 0; i < this->NOLs; i++)
	{
		for (int j = 0; j < this->Ls[i].size; j++)
		{
			check1 = true;
			if (this->Ls[i].Cs[j] == Tofind[0] && (j == 0 || this->Ls[i].Cs[j - 1] == ' '))
			{
				int k = j + 1, l = 1;
				for (; k < length && k < this->Ls[i].size; k++, l++)
				{
					if (this->Ls[i].Cs[k] != Tofind[l])
					{
						check1 = false;
						break;
					}
				}
				if (k == this->Ls[i].size)
				{
					for (int q = 0; l < length; q++, l++)
					{
						if (this->Ls[i + 1].Cs[q] != Tofind[l])
						{
							check1 = false;
							break;
						}
					}
				}
				if (check1)
				{
					if (Tofind[length - 1] == '.' || Tofind[length - 1] == '?' || Tofind[length - 1] == '!')
					{
						FI = i;
						fi = j;
						return check1;
					}
				}
			}
		}
	}
	return false;
}

void Document::PrintDocument(int ri, int ci)
{
	this->Ls[ri].PrintLine(ci);
	for (int i = ri + 1; i < this->NOLs; i++)
	{
		this->Ls[i].PrintLine(0);
	}
}

void Document::PrintDocument(int ri, int ci, int lim)
{
	this->Ls[ri].PrintLine(ci, lim);
	for (int i = ri + 1; i < this->NOLs; i++)
	{
		this->Ls[i].PrintLine(0);
	}
}

void Document::PrintDocument(int ri, int ci, int p, int q)
{
	this->Ls[ri].PrintLine(ci);
	for (int i = ri + 1; i < this->NOLs; i++)
	{
		this->Ls[i].PrintLine(0);
	}
	for (int i = this->NOLs; i < ROWS; i++)
		PrintSpacesD(i, 0);
}

Document::~Document()
{
	delete[] this->Ls;
}
