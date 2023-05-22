#include"Line.h"
#include<fstream>
#include"Header.h"
using namespace std;

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void PrintSpaces(int rci, int sci)
{
	for (int i = sci; i < CCOLS; i++)
	{
		gotoRowCol(rci, i);
		cout << ' ';
	}
}

bool Line::IsAWord(string str, const int ci)
{
	int length = STRLEN(str);
	if (ci == 0 || this->Cs[ci - 1] == ' ')
		return !((this->Cs[ci + length] > 65 && this->Cs[ci + length] < 90) ||
			(this->Cs[ci + length] > 97 && this->Cs[ci + length] < 122));
	else return false;
}

bool Line::isChar(char c)
{
	return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

bool Line::islower(char c)
{
	return c >= 97 && c <= 122;
}

bool Line::isupper(char c)
{
	return c >= 65 && c <= 90;
}

char Line::tolower(char c)
{
	if (isupper(c))
		c += 32;
	return c;
}

char Line::toupper(char c)
{
	if (islower(c))
		c -= 32;
	return c;
}

Line::Line()
{
	size = 1;
	Cs = new char[1]{'\0'};
}

Line::Line(const Line& A)
{
	this->size = A.size;
	this->Cs = new char[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Cs[i] = A.Cs[i];
	}
}

void Line::Load(ifstream& Rdr)
{
	string ch;
	int i = 0;
	getline(Rdr, ch);
	while (ch[i] != '\0')
	{
		InsertCharAt_i(i, ch[i]);
		i++;
	}
}

void Line::InsertCharAt_i(int i, char ch)
{
	char* temp;
	temp = new char[this->size + 1];
	for (int j = 0; j < i; j++)
		temp[j] = this->Cs[j];
	temp[i] = ch;
	for (int j = i + 1; j <= this->size; j++)
		temp[j] = this->Cs[j - 1];
	delete[] this->Cs;
	this->size++;
	this->Cs = temp;
}

void Line::CharRemoverAt_i(int i)
{
	char* temp;
	temp = new char[this->size - 1];
	for (int j = 0; j < i; j++)
		temp[j] = this->Cs[j];
	for (int j = i, k = i + 1; k < this->size; j++, k++)
		temp[j] = this->Cs[k];
	delete[] this->Cs;
	this->size--;
	this->Cs = temp;
}

int Line::STRLEN(string str)
{
	int count = 0, i = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	return count;
}

int* Line::SubStrings(string Tofind, int& count, bool CaseSens)
{
	int* A = nullptr;
	count = 0;
	int length = STRLEN(Tofind);
	int a = 0;
	bool check = true;
	for (int i = 0; i < this->size; i++)
	{
		if (this->Cs[i] == Tofind[0] && CaseSens)
		{
			for (int j = 1, k = i + 1; j < length; j++, k++)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check = false;
					break;
				}
			}
			if (check == true)
			{
				int* HA = new int[count + 1];
				for (int l = 0; l < count; l++)
				{
					HA[l] = A[l];
				}
				HA[count] = i;
				delete[] A;
				count++;
				A = HA;
			}
		}
		if (tolower(this->Cs[i]) == tolower(Tofind[0]) && !CaseSens)
		{
			for (int j = 1, k = i + 1; j < length; j++, k++)
			{
				if (tolower(this->Cs[k]) != tolower(Tofind[j]))
				{
					check = false;
					break;
				}
			}
			if (check == true)
			{
				int* HA = new int[count + 1];
				for (int l = 0; l < count; l++)
				{
					HA[l] = A[l];
				}
				HA[count] = i;
				delete[] A;
				count++;
				A = HA;
			}
		}
	}
	return A;
}

void Line::AddPrefix(string Tofind, string Prefix, bool CaseSens)
{
	int length1 = STRLEN(Tofind);
	int length2 = STRLEN(Prefix);
	bool check1, check2 = false, check3;
	for (int i = 0; i < this->size; i++)
	{
		if (check2 == true)
		{
			i += length1 + length2 - 1;
			check2 = false;
		}
		check1 = true;
		if (this->Cs[i] == Tofind[0] && CaseSens)
		{
			for (int j = 1, k = i + 1; j < length1; j++, k++)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check3 = IsAWord(Tofind, i);
				if (check3)
				{
					char* Cs = new char[this->size + length2];
					for (int m = 0; m < i; m++)
						Cs[m] = this->Cs[m];
					for (int m = i, n = 0; n < length2; m++, n++)
						Cs[m] = Prefix[n];
					for (int m = i + length2, n = i; m < this->size + length2; m++, n++)
						Cs[m] = this->Cs[n];
					delete[] this->Cs;
					this->size += length2;
					this->Cs = Cs;
					check2 = true;
				}
			}
		}
		if (tolower(this->Cs[i]) == tolower(Tofind[0]) && !CaseSens)
		{
			for (int j = 1, k = i + 1; j < length1; j++, k++)
			{
				if (tolower(this->Cs[k]) != tolower(Tofind[j]))
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check3 = IsAWord(Tofind, i);
				if (check3)
				{
					char* Cs = new char[this->size + length2];
					for (int m = 0; m < i; m++)
						Cs[m] = this->Cs[m];
					for (int m = i, n = 0; n < length2; m++, n++)
						Cs[m] = Prefix[n];
					for (int m = i + length2, n = i; m < this->size + length2; m++, n++)
						Cs[m] = this->Cs[n];
					delete[] this->Cs;
					this->size += length2;
					this->Cs = Cs;
					check2 = true;
				}
			}
		}
	}
}

void Line::AddPostfix(string Tofind, string Postfix, bool CaseSens)
{
	int length1 = STRLEN(Tofind);
	int length2 = STRLEN(Postfix);
	bool check1, check2 = false, check3;
	for (int i = 0; i < this->size; i++)
	{
		if (check2 == true)
		{
			i += length1 + length2 - 1;
			check2 = false;
		}
		check1 = true;
		if (this->Cs[i] == Tofind[0] && CaseSens)
		{
			for (int j = 1, k = i + 1; j < length1; j++, k++)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check3 = IsAWord(Tofind, i);
				if (check3)
				{
					char* Cs = new char[this->size + length2];
					for (int m = 0; m < i + length1; m++)
						Cs[m] = this->Cs[m];
					for (int m = i + length1, n = 0; n < length2; m++, n++)
						Cs[m] = Postfix[n];
					for (int m = i + length1 + length2, n = i + length1; m < this->size + length2; m++, n++)
						Cs[m] = this->Cs[n];
					delete[] this->Cs;
					this->size += length2;
					this->Cs = Cs;
					check2 = true;
				}
			}
		}
		if (tolower(this->Cs[i]) == tolower(Tofind[0]) && !CaseSens)
		{
			for (int j = 1, k = i + 1; j < length1; j++, k++)
			{
				if (tolower(this->Cs[k]) != tolower(Tofind[j]))
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check3 = IsAWord(Tofind, i);
				if (check3)
				{
					char* Cs = new char[this->size + length2];
					for (int m = 0; m < i + length1; m++)
						Cs[m] = this->Cs[m];
					for (int m = i + length1, n = 0; n < length2; m++, n++)
						Cs[m] = Postfix[n];
					for (int m = i + length1 + length2, n = i + length1; m < this->size + length2; m++, n++)
						Cs[m] = this->Cs[n];
					delete[] this->Cs;
					this->size += length2;
					this->Cs = Cs;
					check2 = true;
				}
			}
		}
	}
}

bool Line::ReplaceFirst(string Tofind, string Toreplace, bool CaseSens)
{
	int length1 = STRLEN(Tofind);
	int length2 = STRLEN(Toreplace);
	bool check1, check2 = true, check3;
	for (int i = 0; i < this->size && check2; i++)
	{
		check1 = true;
		if (this->Cs[i] == Tofind[0] && CaseSens)
		{
			for (int j = 1, k = i + 1; j < length1; j++, k++)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check3 = IsAWord(Tofind, i);
				if (check3)
				{
					char* Cs = new char[this->size - length1 + length2];
					int m = 0;
					for (; m < i; m++)
						Cs[m] = this->Cs[m];
					for (int n = 0; n < length2; m++, n++)
						Cs[m] = Toreplace[n];
					for (int n = i + length1; n < this->size; m++, n++)
						Cs[m] = this->Cs[n];
					delete[] this->Cs;
					this->size = this->size - length1 + length2;
					this->Cs = Cs;
					check2 = false;
				}
			}
		}
		if (tolower(this->Cs[i]) == tolower(Tofind[0]) && !CaseSens)
		{
			for (int j = 1, k = i + 1; j < length1; j++, k++)
			{
				if (tolower(this->Cs[k]) != tolower(Tofind[j]))
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check3 = IsAWord(Tofind, i);
				if (check3)
				{
					char* Cs = new char[this->size - length1 + length2];
					int m = 0;
					for (; m < i; m++)
						Cs[m] = this->Cs[m];
					for (int n = 0; n < length2; m++, n++)
						Cs[m] = Toreplace[n];
					for (int n = i + length1; n < this->size; m++, n++)
						Cs[m] = this->Cs[n];
					delete[] this->Cs;
					this->size = this->size - length1 + length2;
					this->Cs = Cs;
					check2 = false;
				}
			}
		}
	}
	return !check2;
}

void Line::ReplaceAll(string Tofind, string Toreplace, bool CaseSens)
{
	int length1 = STRLEN(Tofind);
	int length2 = STRLEN(Toreplace);
	bool check1, check2 = false, check3;
	for (int i = 0; i < this->size; i++)
	{
		if (check2 == true)
		{
			i += length2 - 1;
			check2 = false;
		}
		check1 = true;
		if (this->Cs[i] == Tofind[0] && CaseSens)
		{
			for (int j = 1, k = i + 1; j < length1; j++, k++)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check3 = IsAWord(Tofind, i);
				if (check3)
				{
					char* Cs = new char[this->size - length1 + length2];
					int m = 0;
					for (; m < i; m++)
						Cs[m] = this->Cs[m];
					for (int n = 0; n < length2; m++, n++)
						Cs[m] = Toreplace[n];
					for (int n = i + length1; n < this->size; m++, n++)
						Cs[m] = this->Cs[n];
					delete[] this->Cs;
					this->size = this->size - length1 + length2;
					this->Cs = Cs;
					check2 = true;
				}
			}
		}
		if (tolower(this->Cs[i]) == tolower(Tofind[0]) && !CaseSens)
		{
			for (int j = 1, k = i + 1; j < length1; j++, k++)
			{
				if (tolower(this->Cs[k]) != tolower(Tofind[j]))
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check3 = IsAWord(Tofind, i);
				if (check3)
				{
					char* Cs = new char[this->size - length1 + length2];
					int m = 0;
					for (; m < i; m++)
						Cs[m] = this->Cs[m];
					for (int n = 0; n < length2; m++, n++)
						Cs[m] = Toreplace[n];
					for (int n = i + length1; n < this->size; m++, n++)
						Cs[m] = this->Cs[n];
					delete[] this->Cs;
					this->size = this->size - length1 + length2;
					this->Cs = Cs;
					check2 = true;
				}
			}
		}
	}
}

bool Line::FindNextOnly(string Tofind, const int ci, int& fi, bool CaseSens)
{
	int length = STRLEN(Tofind);
	bool check1, check2;
	for (int i = ci; i < this->size; i++)
	{
		check1 = true;
		if (this->Cs[i] == Tofind[0] && CaseSens)
		{
			for (int j = 1, k = i + 1; j < length; j++, k++)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check2 = IsAWord(Tofind, i);
				if (check2)
				{
					fi = i;
					return true;
				}
			}
		}
		if (tolower(this->Cs[i]) == tolower(Tofind[0]) && !CaseSens)
		{
			for (int j = 1, k = i + 1; j < length; j++, k++)
			{
				if (tolower(this->Cs[k]) != tolower(Tofind[j]))
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check2 = IsAWord(Tofind, i);
				if (check2)
				{
					fi = i;
					return true;
				}
			}
		}
	}
	return false;
}

bool Line::FindPrevOnly(string Tofind, const int ci, int& fi, bool CaseSens)
{
	int length = STRLEN(Tofind);
	bool check1, check2;
	for (int i = ci; i >= 0; i--)
	{
		check1 = true;
		if (this->Cs[i] == Tofind[length - 1] && CaseSens)
		{
			for (int j = length - 2, k = i - 1; j >= 0; j--, k--)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				int chi = i - length + 1;
				check2 = IsAWord(Tofind, chi);
				if(check2)
				{
					fi = chi;
					return true;
				}
			}
		}
		if (tolower(this->Cs[i]) == tolower(Tofind[length - 1]) && !CaseSens)
		{
			for (int j = length - 2, k = i - 1; j >= 0; j--, k--)
			{
				if (tolower(this->Cs[k]) != tolower(Tofind[j]))
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				int chi = i - length + 1;
				check2 = IsAWord(Tofind, chi);
				if (check2)
				{
					fi = chi;
					return true;
				}
			}
		}
	}
	return false;
}

int* Line::FindNextAll(string Tofind, const int ci, int& count, bool CaseSens)
{
	int* Fi = nullptr;
	int length = STRLEN(Tofind);
	bool check1, check2;
	for (int i = ci; i < this->size; i++)
	{
		check1 = true;
		if (this->Cs[i] == Tofind[0] && CaseSens)
		{
			for (int j = 1, k = i + 1; j < length; j++, k++)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check2 = IsAWord(Tofind, i);
				if (check2)
				{
					int* HA = new int[count + 1];
					for (int fi = 0; fi < count; fi++)
						HA[fi] = Fi[fi];
					HA[count] = i;
					count++;
					delete[] Fi;
					Fi = HA;
				}
			}
		}
		if (tolower(this->Cs[i]) == tolower(Tofind[0]) && !CaseSens)
		{
			for (int j = 1, k = i + 1; j < length; j++, k++)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				check2 = IsAWord(Tofind, i);
				if (check2)
				{
					int* HA = new int[count + 1];
					for (int fi = 0; fi < count; fi++)
						HA[fi] = Fi[fi];
					HA[count] = i;
					count++;
					delete[] Fi;
					Fi = HA;
				}
			}
		}
	}
	return Fi;
}

int* Line::FindPrevAll(string Tofind, const int ci, int& count, bool CaseSens)
{
	int* Fi = nullptr;
	int length = STRLEN(Tofind);
	bool check1, check2;
	for (int i = ci; i >= 0; i--)
	{
		check1 = true;
		if (this->Cs[i] == Tofind[length - 1] && CaseSens)
		{
			for (int j = length - 2, k = i - 1; j >= 0; j--, k--)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				int chi = i - length + 1;
				check2 = IsAWord(Tofind, chi);
				if (check2)
				{
					int* HA = new int[count + 1];
					for (int fi = 0; fi < count; fi++)
						HA[fi] = Fi[fi];
					HA[count] = chi;
					count++;
					delete[] Fi;
					Fi = HA;
				}
			}
		}
		if (this->Cs[i] == Tofind[length - 1] && !CaseSens)
		{
			for (int j = length - 2, k = i - 1; j >= 0; j--, k--)
			{
				if (this->Cs[k] != Tofind[j])
				{
					check1 = false;
					break;
				}
			}
			if (check1)
			{
				int chi = i - length + 1;
				check2 = IsAWord(Tofind, chi);
				if (check2)
				{
					int* HA = new int[count + 1];
					for (int fi = 0; fi < count; fi++)
						HA[fi] = Fi[fi];
					HA[count] = chi;
					count++;
					delete[] Fi;
					Fi = HA;
				}
			}
		}
	}
	return Fi;
}

bool Line::FindAndReplaceNextOnly(string Tofind, string Toreplace, const int ci, int& fi, bool CaseSens)
{
	int length1 = STRLEN(Tofind);
	int length2 = STRLEN(Toreplace);
	bool f = this->FindNextOnly(Tofind, ci, fi, CaseSens);
	if (f)
	{
		char* Cs = new char[this->size - length1 + length2];
		int m = 0, i = fi;
		for (; m < i; m++)
			Cs[m] = this->Cs[m];
		for (int n = 0; n < length2; m++, n++)
			Cs[m] = Toreplace[n];
		for (int n = i + length1; n < this->size; m++, n++)
			Cs[m] = this->Cs[n];
		delete[] this->Cs;
		this->size = this->size - length1 + length2;
		this->Cs = Cs;
	}
	return f;
}

bool Line::FindAndReplacePrevOnly(string Tofind, string Toreplace, const int ci, int& fi, bool CaseSens)
{
	int length1 = STRLEN(Tofind);
	int length2 = STRLEN(Toreplace);
	bool f = this->FindPrevOnly(Tofind, ci, fi, CaseSens);
	if (f)
	{
		char* Cs = new char[this->size - length1 + length2];
		int m = 0, i = fi;
		for (; m < i; m++)
			Cs[m] = this->Cs[m];
		for (int n = 0; n < length2; m++, n++)
			Cs[m] = Toreplace[n];
		for (int n = i + length1; n < this->size; m++, n++)
			Cs[m] = this->Cs[n];
		delete[] this->Cs;
		this->size = this->size - length1 + length2;
		this->Cs = Cs;
	}
	return f;
}

void Line::FindAndReplaceNextAll(string Tofind, string Toreplace, const int ci, int& count, bool CaseSens)
{
	int length1 = STRLEN(Tofind);
	int length2 = STRLEN(Toreplace);
	count = 0;
	int* Fi = FindNextAll(Tofind, ci, count, CaseSens);
	bool check = false;
	for (int i = 0; i < count; i++)
	{
		if(check)
			for (int j = 0; j < count; j++)
				Fi[j] = Fi[j] - length1 + length2;
		char* Cs = new char[this->size - length1 + length2];
		int m = 0;
		for (; m < Fi[i]; m++)
			Cs[m] = this->Cs[m];
		for (int n = 0; n < length2; m++, n++)
			Cs[m] = Toreplace[n];
		for (int n = Fi[i] + length1; n < this->size; m++, n++)
			Cs[m] = this->Cs[n];
		delete[] this->Cs;
		this->size = this->size - length1 + length2;
		this->Cs = Cs;
		check = true;
	}
}

void Line::FindAndReplacePrevAll(string Tofind, string Toreplace, const int ci, int& count, bool CaseSens)
{
	int length1 = STRLEN(Tofind);
	int length2 = STRLEN(Toreplace);
	count = 0;
	int* Fi = FindPrevAll(Tofind, ci, count, CaseSens);
	for (int i = 0; i < count; i++)
	{
		char* Cs = new char[this->size - length1 + length2];
		int m = 0;
		for (; m < Fi[i]; m++)
			Cs[m] = this->Cs[m];
		for (int n = 0; n < length2; m++, n++)
			Cs[m] = Toreplace[n];
		for (int n = Fi[i] + length1; n < this->size; m++, n++)
			Cs[m] = this->Cs[n];
		delete[] this->Cs;
		this->size = this->size - length1 + length2;
		this->Cs = Cs;
	}
}

void Line::PrintLine(int i)
{
	for(int j = i; j < this->size; j++)
		cout << this->Cs[j];
	for (int j = this->size; j < COLS; j++)
		cout << ' ';
	cout << endl;
}

void Line::PrintLine(int i, int lim)
{
	for (int j = i; j < lim; j++)
		cout << this->Cs[j];
}

void Line::Writer(ofstream& Wtr)
{
	for (int j = 0; j < this->size; j++)
		Wtr << this->Cs[j];
	Wtr << endl;
}

Line::~Line()
{
	delete[] Cs;
}