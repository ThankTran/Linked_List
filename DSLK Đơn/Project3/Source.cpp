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
void InterchangeSort(LIST&);
int DemNode(LIST);
int Xuat(LIST, string);

int main()
{
	LIST lst;
	if (Nhap(lst, "intdata01.inp") == 1)
	{
		InterchangeSort(lst);
		Xuat(lst, "intdata01.out");
	}
	else
		cout << "Loi mo file";

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
	return p;
}

void AddTail(LIST& l, NODE* p)
{
	if (l.pHead == NULL)
		l.pHead = l.pTail = p;
	else
	{
		l.pTail->pNext = p;
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

void InterchangeSort(LIST& l)
{
	for (NODE* p = l.pHead;p->pNext != NULL;p = p->pNext)
		for (NODE* q = p->pNext;q != NULL;q = q->pNext)
			if (p->info > q->info)
				swap(p->info, q->info);
}




