// Max Likarenko - Homework 007
/*
Створіть клас «Дріб» (або використовуйте вже раніше створений вами).
Використовуючи перевантаження операторів реалізуйте для нього арифметичні операції для роботи
з дробом (операції +, -, *, /, =, ==, !=, >, <, >=, <=, !, ++ та -- (пркфіксну та постфіксну)).
*/

#include <iostream>
#include <Windows.h>

using namespace std;

class Drib {
	int chis, znam;
public:
	Drib(int up = 1, int down = 1) : chis{ up }, znam{ down } {}
	Drib operator+(const Drib& right) { return Drib(((this->chis * right.znam) + (right.chis * this->znam)), (this->znam * right.znam)); }
	Drib operator-(const Drib& right) { return Drib(((this->chis * right.znam) - (right.chis * this->znam)), (this->znam * right.znam)); }
	Drib operator-() { return Drib(-chis, znam); }
	Drib operator*(const Drib& right) { return Drib((this->chis * right.chis), (this->znam * right.znam)); }
	Drib operator/(const Drib& right) { 
		if (right.znam == 0)
			return Drib(NULL, NULL);
		return Drib((this->chis * right.znam), (this->znam * right.chis)); 
	}
	Drib& operator=(const Drib& right) {
		chis = right.chis;
		znam = right.znam;
		return *this;
	}
	bool operator==(const Drib& right) {
		if (znam && right.znam) {
			if ((double(this->chis) / double(this->znam)) == (double(right.chis) / double(right.znam)))
				return 1;
			else
				return 0;
		}
	}
	bool operator!=(const Drib& right) {
		if (znam && right.znam) {
			if ((double(this->chis) / double(this->znam)) != (double(right.chis) / double(right.znam)))
				return 1;
			else
				return 0;
		}
	}
	bool operator>(const Drib& right) {
		if (znam && right.znam) {
			if ((double(this->chis) / double(this->znam)) > (double(right.chis) / double(right.znam)))
				return 1;
			else
				return 0;
		}
	}
	bool operator<(const Drib& right) {
		if (znam && right.znam) {
			if ((double(this->chis) / double(this->znam)) < (double(right.chis) / double(right.znam)))
				return 1;
			else
				return 0;
		}
	}
	bool operator>=(const Drib& right) {
		if (znam && right.znam) {
			if ((double(this->chis) / double(this->znam)) >= (double(right.chis) / double(right.znam)))
				return 1;
			else
				return 0;
		}
	}
	bool operator<=(const Drib& right) {
		if (znam && right.znam) {
			if ((double(this->chis) / double(this->znam)) <= (double(right.chis) / double(right.znam)))
				return 1;
			else
				return 0;
		}
	}
	bool operator!() {
		if (znam)
			return 0;
		else
			return 1;
	}
	Drib operator++() { return Drib(chis += znam, znam); }
	Drib operator++(int) {
		Drib help = *this;
		chis += znam;
		return help;
	}
	Drib operator--() { return Drib(chis -= znam, znam); }
	Drib operator--(int) {
	Drib help = *this;
	chis -= znam;
	return help;
}
	void print() {
	if (znam == 0)
		cout << "Дріб виконати не вдалося" << endl;
	else
		cout << chis << "/" << znam << endl;
}
	void print(string message) {	
		cout << chis << "/" << znam << " " << message << endl;
	}
	void print(string message, Drib drib) {
		cout << chis << "/" << znam << " " << message << " " << drib.chis << "/" << drib.znam << endl;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Drib d1(15, 13);
	Drib d2(58, 33);
	Drib d3, d4;
	d4 = d3 = d1 + d2;
	d3.print();
	d4.print();
	d3 = d1 - d2;
	d3.print();
	d3 = d1 * d2;
	d3.print();
	d3 = d1 / d2;
	d3.print();
	d4 = Drib(0, 0);
	d3 = d1 / d4;
	d3.print();
	if (d1 > d2)
		d1.print("більше", d2);
	else
		d2.print("більше", d1);
	if (d1 == d2)
		d1.print("рівне", d2);
	else
		d2.print("не рівне", d1);
	d4 = ++d1;
	d4.print();
	d4 = d1--;
	d4.print();
	d4 = -d4;
	d4.print();
	if (d4 != d2)
		d4.print("не дорівнює", d2);
	else
		d4.print("дорівнює", d1);
	if (d2 < d1)
		d2.print("меньше", d1);
	else
		d1.print("меньше", d2);
	if (d1 >= d2)
		d1.print("більше або дорівнює", d2);
	else
		d2.print("більше або дорівнює", d1);
	if (d1 <= d2)
		d1.print("меньше або дорівнює", d2);
	else
		d2.print("меньше або дорівнює", d1);
	if (!d3)
		d3.print("знаменник нуль");
	else
		d2.print("знаменник не нуль");
	d3 = d2++;
	d3.print();
	d3 = --d2;
	d3.print();
}