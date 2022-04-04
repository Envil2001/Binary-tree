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

//Додавання елемента
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
//Обхід всього дерева
void wrtree(ttree* p, int level) {
	if (p == NULL) {
		cout << "Дерево пусто" << endl;
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
//Вивод в обратному порядку
void wrtreeOutput(ttree* p, int level) {
	if (p == NULL) {
		cout << "Дерево пусто" << endl;
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
//Вивод в порядку зростання
void wrtreeobh(ttree* p, int level) {
	if (p == NULL) {
		cout << "Дерево пусто" << endl;
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


//Пошук елемента із заданим ключем
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

//Видалення елемента із заданим ключем
ttree* dellist(ttree* proot, int inf) {
	ttree* ps = proot, * pr = proot, * w, * v;
	// Поиск удалемого узла
	while ((ps != NULL) && (ps->inf != inf)) {
		pr = ps;
		if (inf < ps->inf) ps = ps->left;
		else ps = ps->rigth;
	}
	if (ps == NULL) return proot;
	// Если узел не имеет дочерей
	if ((ps->left == NULL) && (ps->rigth == NULL)) {
		if (ps == pr) { // Если это был последний элемент
			delete(ps);
			return NULL;
		}
		if (pr->left == ps) // Если удаляемый узел слева
			pr->left = NULL;
		else                // Если удаляемый узел спава
			pr->rigth = NULL;
		delete(ps);
		return proot;
	}
	// Если узел имеет дочь только справа
	if (ps->left == NULL) {
		if (ps == pr) { // Если удаляется корень
			ps = ps->rigth;
			delete(pr);
			return ps;
		}
		if (pr->left == ps) // Если удаляемый узел слева
			pr->left = ps->rigth;
		else                // Если удаляемый узел спава
			pr->rigth = ps->rigth;
		delete(ps);
		return proot;
	}
	// Если узел имеет дочь только слева
	if (ps->rigth == NULL) {
		if (ps == pr) { // Если удаляется корень
			ps = ps->left;
			delete(pr);
			return ps;
		}
		if (pr->left == ps) // Если удаляемый узел слева
			pr->left = ps->left;
		else                // Если удаляемый узел спава
			pr->rigth = ps->left;
		delete(ps);
		return proot;
	}
	w = ps->left;
	if (w->rigth == NULL) // Если максимасальный
						  // следует за ps
		w->rigth = ps->rigth;
	if (ps == pr) // Если удаляется корень
	{
		delete(ps);
		return w;
	}
	if (pr->left == ps) // Если удаляемый узел слева
		pr->left = w;
	else                // Если удаляемый узел справа
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
		cout << "(0)Заполнить дерево рандомом от -50 до 50 +" << endl
			<< "(1)Вывод +" << endl
			<< "(2)Вывод обратным обходом" << endl
			<< "(3)Вывод в порядке возрастания" << endl
			<< "(4)Добавить новое значения +" << endl
			<< "(5)Удалить значение" << endl
			<< "(6)Поиск значения +" << endl
			<< "(7)Выход +" << endl;
		cin >> k;
		switch (k) {
			case 0:
				cout << "Введите размер: "; cin >> size;
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
				cout << "Введите новый элемент: ";
				cin >> elem;
				addtree(proot, elem);
				cout << "Значение добавлено" << endl;
				break;
			case 5:
				int k;
				cout << "Введите значение - ";
				cin >> k;
				proot = dellist(proot, k);
				break;
			case 6:
				bool b;
				int key, rez;
				cout << "Введите ключ - ";
				cin >> key;
				poisktree(proot, key, b = false, rez);
				if (b == false)
					cout << "К сожалению,ничего не найдено!" << endl;
				else
					cout << "Найдено! - " << rez << endl;
				break;
			case 7:return 0;
		}
	} while (1);
}