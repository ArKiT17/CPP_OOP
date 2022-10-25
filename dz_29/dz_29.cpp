// Max Likarenko Homework 029
/*
Створіть додаток для роботи автосалону. Необхідно
зберігати інформацію про автомобілі у продажі (назва, рік
випуску, об’єм двигуна, ціну).
Реалізуйте інтерфейс для додавання даних, видалення
даних, відображення даних, сортування даних за різними
параметрами, пошук даних за різними параметрами.
Під час реалізації використовуйте контейнери,
функтори, лямбда-функції і алгоритми.
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Auto {
	string name;
	int year;
	float volume;
	int price;
	Auto(string n, int y, float v, int p) :
		name{ n }, year{ y }, volume{ v }, price{ p } {}
	friend ostream& operator<<(ostream& out, const Auto& car) {
		out << "Назва: " << car.name << endl;
		out << "Рік випуску: " << car.year << endl;
		out << "Об'єм двигуна: " << car.volume << endl;
		out << "Ціна: " << car.price << endl;
		return out;
	}
};

bool ifName(Auto& car1, Auto& car2) { return car1.name < car2.name; }
bool ifYear(Auto& car1, Auto& car2) { return car1.year < car2.year; }

class Autosalon {
	vector<Auto> cars;
public: 
	void add(string name, int year, float volume, int price) {
		cars.push_back(Auto(name, year, volume, price));
	}
	void add() {
		cout << "Введіть назву авто: ";
		string tmps;
		getline(cin, tmps);
		cout << "Введіть рік випуску: ";
		int tmpi;
		cin >> tmpi;
		cout << "Введіть об'єм двигуна: ";
		float tmpf;
		cin >> tmpf;
		cout << "Введіть ціну авто: ";
		int tmpc;
		cin >> tmpc;
		cars.push_back(Auto(tmps, tmpi, tmpf, tmpc));
	}
	void remove(string name) {
		for (auto i = cars.begin(); i < cars.end(); i++)
			if (i->name == name) {
				cars.erase(i);
				break;
			}
	}
	void showAll() {
		for (auto car : cars)
			cout << car;
		cout << endl;
	}
	void sortName() {
		sort(cars.begin(), cars.end(), ifName);
	}
	void sortYear() {
		sort(cars.begin(), cars.end(), ifYear);
	}
	void sortPriceUp() {
		sort(cars.begin(), cars.end(), [](const Auto& car1, const Auto& car2) {
			if (car1.price < car2.price)
				return true;
			else
				return false;
		});
	}
	void sortPriceDown() {
		sort(cars.begin(), cars.end(), [](const Auto& car1, const Auto& car2) {
			if (car1.price > car2.price)
				return true;
			else
				return false;
		});
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Autosalon a;
	a.add("mashina", 2020, 2.5, 10000);
	a.add("car", 1990, 1.0, 1000);
	a.add("Lexus", 2017, 3.0, 17000);
	a.add("Audi", 2022, 3.2, 16000);
	a.add("Ford", 2015, 2.2, 10200);
	a.showAll();

	cout << "Видаляємо car i mashina...\n";
	system("pause");
	system("cls");
	a.remove("car");
	a.remove("mashina");
	cout << "car i mashina видалено\n\n";
	a.showAll();

	cout << "Сортуємо за назвою (використовуючи предикат)\n";
	system("pause");
	system("cls");
	a.sortName();
	cout << "Відсортовано за назвою (використовуючи предикат)\n\n";
	a.showAll();

	cout << "Сортуємо за роком випуску (використовуючи предикат)\n";
	system("pause");
	system("cls");
	a.sortYear();
	cout << "Відсортовано за роком випуску (використовуючи предикат)\n\n";
	a.showAll();

	cout << "Сортуємо за зростанням ціни (використовуючи лямбду)\n";
	system("pause");
	system("cls");
	a.sortPriceUp();
	cout << "Відсортовано за зростанням ціни (використовуючи лямбду)\n\n";
	a.showAll();

	cout << "Сортуємо за спаданням ціни (використовуючи лямбду)\n";
	system("pause");
	system("cls");
	a.sortPriceDown();
	cout << "Відсортовано за спаданням ціни (використовуючи лямбду)\n\n";
	a.showAll();
}