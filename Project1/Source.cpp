#include <iostream>
#include <iomanip>
using namespace std;

int tabs = 0;
struct ttree
{
	int inf;
	ttree* left;
	ttree* rigth;
} *proot;

//��������� ��������
ttree* addtree(ttree* proot, int inf)  {
	ttree* nl, * pr = nullptr, * ps;
	bool b;
	nl = new ttree;
	nl->inf = inf;
	nl->left = NULL;
	nl->rigth = NULL;
	if (proot == NULL) return nl;
	ps = proot;
	while (ps != NULL) {
		pr = ps;
		b = (inf < ps->inf);
		if (b) ps = ps->left;
		else ps = ps->rigth;
	}
	if (b) pr->left = nl;
	else pr->rigth = nl;
	return proot;
}
//����� ������ ������
void wrtree(ttree* p, int level) {
	if (p == NULL) {
		cout << "������ �����" << endl;
	}
	else {
		tabs += 5;
		if (p->left != NULL) wrtree(p->left, level + 1);
		for (int i = 0; i < tabs; i++) cout << " ";
		cout << " " << p->inf << endl;
		if (p->rigth != NULL) wrtree(p->rigth, level + 1);
		tabs -= 5;
	}
}
//����� � ��������� �������
void wrtreeOutput(ttree* p, int level) {
	if (p == NULL) {
		cout << "������ �����" << endl;
	}
	else {
		tabs += 5;
		if (p->rigth != NULL) wrtreeOutput(p->rigth, level + 1);
		for (int i = 0; i < tabs; i++) cout << " ";
		cout << " " << p->inf << endl;
		if (p->left != NULL)  wrtreeOutput(p->left, level + 1);
		tabs -= 5;
	}
}
//����� � ������� ���������
void wrtreeobh(ttree* p, int level) {
	if (p == NULL) {
		cout << "������ �����" << endl;
	}
	else {
		tabs += 5;
		if (p->left != NULL) wrtreeobh(p->left, level + 1);
		for (int i = 0; i < tabs; i++) cout << " ";
		cout << " " << p->inf << endl;
		if (p->rigth != NULL) wrtreeobh(p->rigth, level + 1);
		tabs -= 5;
	}
}


//����� �������� �� ������� ������
void poisktree(ttree* p, int key, bool& b, int& inf) {
	if ((p != NULL) && (b != true))
	{
		if (p->inf != key)
		{
			poisktree(p->left, key, b, inf);
			poisktree(p->rigth, key, b, inf);
		}
		else {
			b = true;
			inf = p->inf;
		}
	}
	return;
}

//��������� �������� �� ������� ������
ttree* dellist(ttree* proot, int inf) {
	ttree* ps = proot, * pr = proot, * w, * v;
	// ����� ��������� ����
	while ((ps != NULL) && (ps->inf != inf)) {
		pr = ps;
		if (inf < ps->inf) ps = ps->left;
		else ps = ps->rigth;
	}
	if (ps == NULL) return proot;
	// ���� ���� �� ����� �������
	if ((ps->left == NULL) && (ps->rigth == NULL)) {
		if (ps == pr) { // ���� ��� ��� ��������� �������
			delete(ps);
			return NULL;
		}
		if (pr->left == ps) // ���� ��������� ���� �����
			pr->left = NULL;
		else                // ���� ��������� ���� �����
			pr->rigth = NULL;
		delete(ps);
		return proot;
	}
	// ���� ���� ����� ���� ������ ������
	if (ps->left == NULL) {
		if (ps == pr) { // ���� ��������� ������
			ps = ps->rigth;
			delete(pr);
			return ps;
		}
		if (pr->left == ps) // ���� ��������� ���� �����
			pr->left = ps->rigth;
		else                // ���� ��������� ���� �����
			pr->rigth = ps->rigth;
		delete(ps);
		return proot;
	}
	// ���� ���� ����� ���� ������ �����
	if (ps->rigth == NULL) {
		if (ps == pr) { // ���� ��������� ������
			ps = ps->left;
			delete(pr);
			return ps;
		}
		if (pr->left == ps) // ���� ��������� ���� �����
			pr->left = ps->left;
		else                // ���� ��������� ���� �����
			pr->rigth = ps->left;
		delete(ps);
		return proot;
	}
	w = ps->left;
	if (w->rigth == NULL) // ���� ��������������
						  // ������� �� ps
		w->rigth = ps->rigth;
	if (ps == pr) // ���� ��������� ������
	{
		delete(ps);
		return w;
	}
	if (pr->left == ps) // ���� ��������� ���� �����
		pr->left = w;
	else                // ���� ��������� ���� ������
		pr->rigth = w;
	delete(ps);
	return proot;
}

int main()
{
	srand(time(NULL));
	int n = 0, size = 0;
	setlocale(LC_ALL, "Russian");
	do {
		int k;
		cout << "(0)��������� ������ �������� �� -50 �� 50 +" << endl
			<< "(1)����� +" << endl
			<< "(2)����� �������� �������" << endl
			<< "(3)����� � ������� �����������" << endl
			<< "(4)�������� ����� �������� +" << endl
			<< "(5)������� ��������" << endl
			<< "(6)����� �������� +" << endl
			<< "(7)����� +" << endl;
		cin >> k;
		switch (k) {
			case 0:
				cout << "������� ������: "; cin >> size;
				for (int i = 0; i < size; ++i) {
					proot = addtree(proot, rand() % 101 - 50);
				}
				cout << endl;
			case 1:
				wrtree(proot, 0);
				break;
			case 2:
				wrtreeOutput(proot, 0);
				break;
			case 3:
				wrtreeobh(proot, 0);
				break;
			case 4:
				int elem;
				cout << "������� ����� �������: ";
				cin >> elem;
				addtree(proot, elem);
				cout << "�������� ���������" << endl;
				break;
			case 5:
				int k;
				cout << "������� �������� - ";
				cin >> k;
				proot = dellist(proot, k);
				break;
			case 6:
				bool b;
				int key, rez;
				cout << "������� ���� - ";
				cin >> key;
				poisktree(proot, key, b = false, rez);
				if (b == false)
					cout << "� ���������,������ �� �������!" << endl;
				else
					cout << "�������! - " << rez << endl;
				break;
			case 7:return 0;
		}
	} while (1);
}