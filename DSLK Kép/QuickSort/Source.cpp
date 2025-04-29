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
	if (l.pHead == NULL)
		l.pHead = l.pTail = p;
	else
	{
		l.pTail->pNext = p;
		p->pPrev = l.pTail;
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
	for (int i = 1;i <= n;i++)
	{
		fi >> x;
		NODE* p = GetNode(x);
		if (p != NULL)
			AddTail(l, p);
	}
	return 1;
}

int Xuat(LIST l, string filename)
{
	ofstream fo(filename);
	if (fo.fail() == true)
		return 0;
	fo << setw(5) << DemNode(l) << endl;
	NODE* p = l.pHead;
	while (p != NULL)
	{
		fo << p->info << setw(4);
		p = p->pNext;
	}
	return 1;
}

void Xuat(LIST l)
{
	NODE* p = l.pHead;
	while (p != NULL)
	{
		cout << p->info << setw(4);
		p = p->pNext;
	}
}

int DemNode(LIST l)
{
	int dem = 0;
	NODE* p = l.pHead;
	while (p != NULL)
	{
		dem++;
		p = p->pNext;
	}
	return dem;
}

NODE* Partition(LIST& l, NODE* Left, NODE* Right)
{
	int Pivot = Right->info;
	NODE* i = Left->pPrev;

	for (NODE* j = Left; j != Right; j = j->pNext)
	{
		if (j->info <= Pivot)
		{
			i = (i == NULL) ? l.pHead : i->pNext;

			if (i != j)
				swap(i->info, j->info);
		}
	}

	i = (i == NULL) ? l.pHead : i->pNext;
	swap(i->info, Right->info);

	return i;
}

void QuickSort(LIST& l, NODE* Left, NODE* Right)
{
	if (Left == NULL || Right == NULL || Left == Right || IsEmpty(l))
		return;

	if (Right->pPrev == Left)
	{
		if (Left->info > Right->info)
			swap(Left->info, Right->info);
		return;
	}

	NODE* pivot = Partition(l, Left, Right);

	if (pivot != Left && Left != NULL)
		QuickSort(l, Left, pivot->pPrev);

	if (pivot != Right && Right != NULL)
		QuickSort(l, pivot->pNext, Right);
}