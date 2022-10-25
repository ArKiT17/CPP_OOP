/* Max Likarenko Homework 1 
Завдання написати програму розрахунку вартості газу за рік:
1. Створити клас Газ (Gas) - поля:
	a. ім'я абонента,
	b. кількість спожитого газу в місяці
	c. інші поля при потребі.
2. Формула для розрахунку вартості газу:
	a. 6 грн з 3-10 місяці
	b. 8 грн в 1-2 та 11-12 місяці
3. Внести інформацію в клас по кожному місяцю за цілий рік з клавіатури.
	a. для цього в класі створити відповідні сетери і гетери
4. Порахувати суму оплати помісячно та за рік по абоненту Іван Іванович та вивести в консоь
	a. Суму по кожному місяцю в році
	b. Загальну суму до оплати за рік
*/
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

class Gas {
	string name;
	int count[12];
public:
	void setName(string x) { name = x; };
	//string getName() { return name; };
	void setCount(int x, int index) { count[index] = x; };
	//int getCount(int index) { return count[index]; };
	int getPrice(int month);
	void print();
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Gas g1;
	cout << "Введіть Ваше ім'я: ";
	string h;
	getline(cin, h);
	g1.setName(h);
	int h2;
	for (int i = 0; i < 12; i++) {
		cout << "Введіть кількість спожитого газу за " << i + 1 << " місяць: ";
		cin >> h2;
		g1.setCount(h2, i);
	}
	g1.print();
}

int Gas::getPrice(int month) {
	if (month >= 2 && month <= 9)
		return count[month] * 6;
	else
		return count[month] * 8;
}

void Gas::print() {
	cout << "\nІм'я: " << name << endl;
	int sum = 0;
	for (int i = 0; i < 12; i++) {
		cout << "Ціна за " << i + 1 << " місяць становить: " << getPrice(i) << endl;
		sum += getPrice(i);
	}
	cout << "\nЦіна за рік: " << sum;
}