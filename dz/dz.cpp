#include <iostream>
using namespace std;
enum wtype { cold, fire, unknown };

class Weapon
{
protected:
	string m_name;
	string m_model;
	wtype m_type;
public:
	Weapon(string model = "", string name = "Unknown Weapon", wtype type = unknown) :
		m_name{ name }, m_model{ model }, m_type{ type } {}
	virtual void Atack() = 0;
	virtual void ShowInfo() final {
		cout << "Info about Weapon !" << endl;
		Print();
	}
	virtual void Print() {
		cout << getName() << (m_model.empty() ? "" : " " + m_model);
	}
	virtual string& getName() final { return m_name; };
	virtual bool isAvailableWeapon() = 0;
	wtype getType() { return m_type; }
	virtual int getBullets() { return 0; }
};

class ColdWeapon : public Weapon {
public:
	ColdWeapon(string model = "", string name = "Unknown Weapon", wtype type = cold) :
		Weapon(model, name, type) {}
	bool isAvailableWeapon() override final { return true; }
	void Print() {
		Weapon::Print();
		cout << endl;
	}
};

class FireWeapon : public Weapon {
	int constBullet;
protected:
	int countBullets;
public:
	FireWeapon(string model = "", string name = "Unknown Weapon", int countBullet = 0) :
		Weapon(model, name, fire), countBullets{ countBullet }, constBullet{ countBullet } {}
	bool isAvailableWeapon() override final { return countBullets > 0; }
	void addBullet() { countBullets += constBullet; }
	int getBullets() override { return countBullets; }
	void Print() {
		Weapon::Print();
		cout << " " << getBullets() << endl;
	}
};

class Knife : public ColdWeapon {
public:
	Knife(string model = "") : ColdWeapon(model, "Knife") {}
	void Atack() override {
		cout << "Atack with a Knife !" << endl;
	}
};

class Machete : public ColdWeapon {
public:
	Machete(string model = "") : ColdWeapon(model, "Machete") {}
	void Atack() override {
		cout << "Atack with a Machete !" << endl;
	}
};

class Gun : public FireWeapon {
public:
	Gun(string model = "", int countBullet = 10) : FireWeapon(model, "Gun", countBullet) {}
	void Atack() override {
		cout << "Atack with a Gun !" << endl;
		countBullets--;
	}
};

class P90 : public FireWeapon {
public:
	P90(string model = "", int countBullet = 50) : FireWeapon(model, "P90", countBullet) {}
	void Atack() override {
		cout << "Atack with a P90 !" << endl;
		countBullets -= 5;
	}
};

class AK47 : public FireWeapon {
public:
	AK47(string model = "", int countBullet = 30) : FireWeapon(model, "AK47", countBullet) {}
	void Atack() override {
		cout << "Atack with a AK47 !" << endl;
		countBullets -= 5;
	}
};

class Granata : public FireWeapon {
public:
	Granata(string model = "", int countBullet = 1) : FireWeapon(model, "Granata", countBullet) {}
	void Atack() override {
		cout << "Atack with a Granata !" << endl;
		countBullets--;
	}
};

void main() {

}