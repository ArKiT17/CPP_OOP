// Max Likarenko Homework 014-016
/*
	Створити клас Шина (наприклад автомобільна шина),
параметри: внутрішній діаметр шини та тип шина (зимова,
літня, інше - enum або char), вага (кілограми)
	Створити клас Диск (автомобільний диск), параметри:
характеристика діаметр в диска, вага (кілограми)
	Створити клас Колесо в якому додати два члени
класу Шина та Диск або множинне наслідування
від Шина та Диск(на кристалики множинне
наслідування). Також додати інші члени та методи
при потребі. Зробити перевірку чи розмір шини та
диску співпадають. Якщо не співпадають то в класі
Автомобіль в функції перевірки засвічувати
лампочку про помилку і виводити повідомлення що
авто не поїде…
	Створити клас Двигун - параметр об'єм двигуна, тип
(бензин, дизель та електрика), вага (кілограми),
потужність, розхід пального (бензин, дизель чи електрика
не важливо на даному етапі) просто для кодного типу буде
відрізнятись цифра, формула та сама.
	Клас Пальне базовий, для використання в
	Клас Батарея ( базовий Пальне ) - Об'єм батареї (Ah
амрео годин), Вага
	Клас Бак ( базовий Пальне ) - Об'єм баку (літри), Вага
	Створити клас Автомобіль - параметр Назва, тип
(Легковий, Вантажний, Автобус), кількість місць, вага
(розраховується), порахувати максимальну швидкість та
пробіг без дозаправки.
Вивести всі параметри автомобіля і його максимальну
швидкість, прохід на одному повному баку чи заряді.
*/

#include <iostream>
#include <Windows.h>
#include <stdlib.h>
using namespace std;

enum shinaType { winter, summer, other };
enum fuelType { gasoline, diesel, eco };
enum autoType { car, truck, bus };

class Shina {
protected:
	float s_diametr;
	shinaType s_type;
	float s_weight;
public:
	Shina(float d = 20, float w = 20, shinaType t = summer) : s_diametr{ d }, s_weight{ w }, s_type { t } {}
	void setShinaDiametr(float d) { d >= 1 ? s_diametr = d : s_diametr = 1; }
	void setShinaType(shinaType a) { s_type = a; }
	void setShinaWeight(float w) { w >= 1 ? s_weight = w : s_weight = 1; }
	float getShinaDiametr() { return s_diametr; }
	shinaType getShinaType() { return s_type; }
	float getShinaWeight() { return s_weight; }
};

class Disс {
protected:
	float d_diametr;
	float d_weight;
public:
	Disс(float d = 20, float w = 20) : d_diametr{ d }, d_weight{ w } {}
	void setDiscDiametr(float d) { d >= 1 ? d_diametr = d : d_diametr = 1; }
	void setDiscWeight(float w) { w >= 1 ? d_weight = w : d_weight = 1; }
	float getDiscDiametr() { return d_diametr; }
	float getDiscWeight() { return d_weight; }
};

class Wheel : public Shina, public Disс {
protected:
	string w_color;
	float w_weight;
public:
	Wheel(float ShDiam = 20, float DsDiam = 20, string c = "none") : w_weight{ s_weight + d_weight }, w_color{ c } {
		s_diametr = ShDiam;
		d_diametr = DsDiam;
	}
	void setWheelColor(string c) { w_color = c; }
	string getWheelColor() { return w_color; }
	float getWheelWeight() { return w_weight; }
	bool isTheSameDiametr() { return s_diametr == d_diametr; }
};

class Engine {
protected:
	float e_volume;
	fuelType e_type;
	float e_weight;
	float e_power;
	float e_ff;
public:
	Engine(float f = 10, float v = 1, fuelType t = gasoline, float w = 1, float p = 100) :
		e_ff{ f }, e_volume{ v }, e_type{ t }, e_weight{ w }, e_power{ p } {}
	void setEngineVolume(float v) { e_volume = v; }
	void setEngineType(fuelType t) { e_type = t; }
	void setEngineWeight(float w) { e_weight = w; }
	void setEnginePower(float p) { e_power = p; }
	void setEngineFF(float ff) { e_ff = ff; }
	float getEngineVolume() { return e_volume; }
	fuelType getEngineType() { return e_type; }
	float getEngineWeight() { return e_weight; }
	float getEnginePower() { return e_power; }
	float getEngineFF() { return e_ff; }
};

class Fuel {
protected:
	fuelType f_type;
public:
	Fuel(fuelType t = gasoline) : f_type{ t } {}
	void setFuelType(fuelType t) { f_type = t; }
	fuelType getFuelType() { return f_type; }
};

class Battery : public Fuel {
protected:
	int b_volume;
	float b_weight;
public:
	Battery(int v = 60000, float w = 5) : b_volume{ v }, b_weight{ w } {}
	void setBatteryVolume(int v) { b_volume = v; }
	void setBatteryWeight(float w) { b_weight = w; }
	int getBatteryVolume() { return b_volume; }
	float getBatteryWeight() { return b_weight; }
};

class Tank : protected Fuel {
	int t_volume;
	float t_weight;
public:
	Tank(int v = 100, float w = 50) : t_volume{ v }, t_weight{ w } {}
	void setTankVolume(int v) { t_volume = v; }
	void setTankWeight(float w) { t_weight = w; }
	int getTankVolume() { return t_volume; }
	float getTankWeight() { return t_weight; }
};

class Auto {
	string a_name;
	autoType a_type;
	int a_numberOfSeats;
	float a_weight;
	float a_maxSpeed;
	float a_mileage;
	Shina s_tmp;
	Disс d_tmp;
	Wheel w_tmp;
	Engine e_tmp;
	Fuel* f_tmp;
public:
	Auto() : Auto("none", car, 0, 18, 18, 100) {}
	Auto(string n, autoType t, int nOS, float ShDiam, float DsDiam, float EFf) : a_name{ n }, a_type{ t }, a_numberOfSeats{ nOS } {
		w_tmp.setShinaDiametr(ShDiam);
		w_tmp.setDiscDiametr(DsDiam);
		a_weight = rand() % 200 + 900 + w_tmp.getWheelWeight() * 4 + e_tmp.getEngineWeight() + b_tmp.getBatteryWeight();
		a_maxSpeed = 300; //як рахувати?
		f_tmp = new Battery;
		a_mileage = f_tmp->getBatteryVolume() / e_tmp.getEngineFF();
		if (!w_tmp.isTheSameDiametr())
			cout << "Машина створена, але діаметр шини та диска не співпадають, тому вона не поїде :,(\n";
	}
	void print() {
		cout << a_name << " - ";
		switch (a_type) {
		case car: cout << "легковий автомобіль. "; break;
		case truck: cout << "вантажний автомобіль. "; break;
		case bus: cout << "автобус. "; break;
		}
		cout << "В салоні має " << a_numberOfSeats << " місць для сидіння. ";
		cout << "Важить " << a_weight << " кілограм, максимальна швидкість " << a_maxSpeed;
		cout << ", а на повному заряді може проїхати аж " << a_mileage << " км.\n\n";
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Auto a;
	a.print();
	Auto b("Tesla", car, 5, 20, 20, 80);
	b.print();
	Auto c("Ursus", bus, 48, 19, 18, 115);
	c.print();
}