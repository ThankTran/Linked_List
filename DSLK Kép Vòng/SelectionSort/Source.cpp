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
void SelectionSort(LIST&);
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
			SelectionSort(lst);
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
	p->pNext = p;
	p->pPrev = p;
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
		p->pNext = l.pHead;
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
	do
	{
		fo << p->info << setw(4);
		p = p->pNext;
	} while (p != l.pHead);
	return 1;
}

void Xuat(LIST l)
{
	if (l.pHead == NULL)
		return;
	NODE* p = l.pHead;
	do
	{
		cout << p->info << setw(8);
		p = p->pNext;
	} while (p != l.pHead);
}

int DemNode(LIST l)
{
	if (l.pHead == NULL)
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

void SelectionSort(LIST& l)
{
	if (l.pHead == NULL || l.pHead->pNext == l.pHead)
		return;

	for (NODE* p = l.pHead; p->pNext != l.pHead; p = p->pNext)
	{
		NODE* lc = p;
		for (NODE* q = p->pNext; q != l.pHead; q = q->pNext)
		{
			if (q->info < lc->info)
				lc = q;
		}
		if (lc != p)
			swap(p->info, lc->info);
	}
}