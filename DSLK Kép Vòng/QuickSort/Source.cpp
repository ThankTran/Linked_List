#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>
using namespace std;

struct node
{
	int info;
	struct node* pNext;
	struct node* pPrev;
};
typedef struct node NODE;

struct list
{
	NODE* pHead;
	NODE* pTail;
};
typedef struct list LIST;

void Init(LIST&);
int IsEmpty(LIST);
NODE* GetNode(int);
void AddTail(LIST&, NODE*);
int Nhap(LIST&, string);
void Xuat(LIST);
void QuickSort(LIST&, NODE*, NODE*);
NODE* Partition(LIST&, NODE*, NODE*);
int DemNode(LIST);
int Xuat(LIST, string);

int main()
{
	LIST lst;
	for (int i = 1;i <= 13;i++)
	{
		string filename = "intdata";
		if (i < 10)
			filename += '0';
		filename += to_string(i);
		string filenameinp = filename;
		filenameinp += ".inp";
		if (Nhap(lst, filenameinp) == 1)
		{
			QuickSort(lst, lst.pHead, lst.pTail);
			string filenameout = filename;
			filenameout += ".out";
			Xuat(lst, filenameout);
		}
		else
			cout << "\n Khong mo duoc file ";
	}

	cout << "\n\n\nKet thuc !!!!!";
	return 0;
}

void Init(LIST& l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}

int IsEmpty(LIST l)
{
	if (l.pHead == NULL)
		return 1;
	return 0;
}

NODE* GetNode(int x)
{
	NODE* p = new NODE;
	if (p == NULL)
		return NULL;
	p->info = x;
	p->pNext = NULL;
	p->pPrev = NULL;
	return p;
}

void AddTail(LIST& l, NODE* p)
{
	if (p == NULL) return;

	if (IsEmpty(l))
	{
		l.pHead = p;
		l.pTail = p;
		p->pNext = p;
		p->pPrev = p;
	}
	else
	{
		p->pPrev = l.pTail;
		p->pNext = l.pHead;
		l.pTail->pNext = p;
		l.pHead->pPrev = p;
		l.pTail = p;
	}
}

int Nhap(LIST& l, string filename)
{
	ifstream fi(filename);
	if (fi.fail() == true)
		return 0;

	int n;
	int x;
	fi >> n;

	Init(l);

	for (int i = 1; i <= n; i++)
	{
		fi >> x;
		NODE* p = GetNode(x);
		if (p != NULL)
			AddTail(l, p);
	}

	fi.close();
	return 1;
}

int Xuat(LIST l, string filename)
{
	ofstream fo(filename);
	if (fo.fail() == true)
		return 0;

	fo << setw(5) << DemNode(l) << "\n";

	if (!IsEmpty(l))
	{
		NODE* p = l.pHead;
		do
		{
			fo << p->info << setw(4);
			p = p->pNext;
		} while (p != l.pHead);
	}

	fo.close();
	return 1;
}

void Xuat(LIST l)
{
	if (IsEmpty(l))
		return;

	NODE* p = l.pHead;
	do
	{
		cout << p->info << setw(8) << endl;
		p = p->pNext;
	} while (p != l.pHead);
}

int DemNode(LIST l)
{
	if (IsEmpty(l))
		return 0;

	int dem = 0;
	NODE* p = l.pHead;
	do
	{
		dem++;
		p = p->pNext;
	} while (p != l.pHead);

	return dem;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

NODE* Partition(LIST& l, NODE* Left, NODE* Right)
{
	int Pivot = Right->info;
	NODE* i = Left->pPrev;

	for (NODE* j = Left; j != Right; j = j->pNext)
	{
		if (j->info <= Pivot)
		{
			i = (i == Right) ? Left : i->pNext;

			if (i != j)
				swap(i->info, j->info);
		}
	}

	i = (i == Right) ? Left : i->pNext;
	swap(i->info, Right->info);

	return i;
}

void QuickSort(LIST& l, NODE* Left, NODE* Right)
{
	if (Left == NULL || Right == NULL || Left == Right)
		return;

	if (Right->pPrev == Left)
	{
		if (Left->info > Right->info)
			swap(Left->info, Right->info);
		return;
	}

	NODE* pivot = Partition(l, Left, Right);

	if (pivot != Left)
		QuickSort(l, Left, pivot->pPrev);

	if (pivot != Right)
		QuickSort(l, pivot->pNext, Right);
}