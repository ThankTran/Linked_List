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
int Nhap(LIST&);
void Xuat(LIST);
void InterchangeSort(LIST&);

int main()
{
	LIST lst;
	Nhap(lst);
	cout << "\nDanh sach ban dau: ";
	Xuat(lst);
	InterchangeSort(lst);
	cout << "\nDanh sach sau khi sap tang: ";
	Xuat(lst);

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

int Nhap(LIST& l)
{
	int n;
	cout << "Nhap so phan tu: ";
	cin >> n;
	Init(l);
	int x;
	for (int i = 1;i <= n;i++)
	{
		cin >> x;
		NODE* p = GetNode(x);
		if (p != NULL)
			AddTail(l, p);
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

void InterchangeSort(LIST& l)
{
	for (NODE* p = l.pHead;p->pNext != NULL;p = p->pNext)
		for (NODE* q = p->pNext;q != NULL;q = q->pNext)
			if (p->info > q->info)
				swap(p->info, q->info);
}


