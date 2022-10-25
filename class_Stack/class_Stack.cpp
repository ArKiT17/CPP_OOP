// Max Likarenko Homework 012
/*
Є рядок символів, ознакою кінця, якого є «;» .
У рядку можуть бути фігурні, круглі, квадратні дужки. Дужки
можуть бути відкриваючими і закриваючими.
Необхідно перевірити коректність розташування дужок.
При цьому необхідно, щоб виконувалися наступні правила:
1. Кожна відкриваюча дужка повинна мати справа таку
ж закриваючу. Зворотне правило також має працювати.
2. Відкриваюча і закриваюча пари дужок різних типів
повинні бути правильно розташовані відносно один до
одного.
■ Приклад правильного рядка:
({x-y-z} * [x + 2y] - (z + 4x)).
■ Приклад неправильного рядка:
([x-y-z} * [x + 2y) - {z + 4x)].
Якщо всі правила дотримані виведіть інформаційне
повідомлення про коректність рядка, інакше — покажіть
рядок до місця виникнення першої помилки.
*/

#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

template <class T>
class Stack {
	T* arr;
	int size;
	int index;
public:
	Stack(int size = 10) : arr{ new T[size] }, size{ size }, index{ -1 } {};
	~Stack() { delete[] arr; }
	bool isFull() { return index + 1 == size; }
	bool isEmpty() { return index == -1; }
	void push(T obj) {
		if (!isFull()) {
			index++;
			arr[index] = obj;
		}
	}
	void pop() {
		if (!isEmpty())
			index--;
	}
	T* top() {
		if (!isEmpty())
			return &arr[index];
		return nullptr;
	}
	void clear() { index = -1; }
	void swap() {
		T help = arr[index - 1];
		arr[index - 1] = arr[index];
		arr[index] = help;
	}
	int getSize() { return size; }
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Stack <char> dugka;
	cout << "Введіть рядок (останній символ \";\"): ";
	string line;
	getline(cin, line);
	int i = 0;
	char* error_line = new char[line.length()];
	while (line[i] != ';') {
		if (line[i] == '(' || line[i] == '{' || line[i] == '[')
			if (!dugka.isFull())
				dugka.push(line[i]);
			else {
				cout << "Помилка. Стек повний.";
				return 1;
			}
		else
			if (line[i] == ')')
				if (*dugka.top() == '(')
					dugka.pop();
				else {
					error_line[i] = '\0';
					cout << "Рядок записаний неправильно: " << error_line;
					return 1;
				}
			else
				if (line[i] == '}')
					if (*dugka.top() == '{')
						dugka.pop();
					else {
						error_line[i] = '\0';
						cout << "Рядок записаний неправильно: " << error_line;
						return 1;
					}
				else
					if (line[i] == ']')
						if (*dugka.top() == '[')
							dugka.pop();
						else {
							error_line[i] = '\0';
							cout << "Рядок записаний неправильно: " << error_line;
							return 1;
						}
		error_line[i] = line[i];
		i++;
	}
	if (dugka.isEmpty())
		cout << "Рядок записаний правильно.";
	else {
		error_line[i] = '\0';
		cout << "Рядок записаний неправильно: " << error_line;
	}
}