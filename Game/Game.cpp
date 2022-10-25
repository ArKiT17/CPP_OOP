// Max Likarenko Homework 018 - 021
/*
Дописати гру що робили на парі. Код тут.
Додати 2 проміжні класи в структуру.
На базі класу Weapon створити 2 наслідника:
● Холодна зброя
● Вогнепальна зброя
Клас Ніж та Мечета успадкувати від базового класу Холодна
зброя
Клас Gun, P90, AK47 i Granata спадкувати від базового класу
Вогнепальна зброя
В Weapon створити метод virtual bool isAvailableWeapon() = 0;
В клас Холодна зброя isAvailableWeapon() завжди повертає true
В клас Вогнепальна зброя зброя isAvailableWeapon() повертає true
якщо є набої і відповідно false як немає відповідно атакувати не
годен і потрібно або вибрати іншу зброю або вивести немає куль.
Кожна зброя має свою кількість набоїв (1 граната, Gun(пістолет) - 10
куль, AK4 - 30 куль i P90 - 50 куль) і після атаки зменшується на
певну кількість (1 для гранат та Gun(пістолет) - 1, та на 5 куль для
P90, AK47 - так як атакуємо чергами)
Переробити клас Player
Attack по замовчуванню вибирає вогнепальну зброю якщо є
набої. Якщо немає тоді холодну.
Add переробити щоб як в функції Атак - Pos був по замовчуванню 0
void Add (Weapon * pWeapon, int pos = 0)
і тоді як pos = 0 додавати в пусту ячейку або сумувати кулі чи
гранати якщо вже є така зброя:
● для гранат додає +1 гранату а не замінює на іншу (якщо в ту
саму ячейку масиву додаємо гранату де вже є гранати, якщо
інший тип в тій ячейці то замінює як зараз в коді),
● аналогічно збільшує кулі для вогнепальної зброї на кількість
куль скільки є по замовчуванню. Реалізувати можна все в
класі Вогнепальна зброя а в наслідниках задаки кількість
набоїв по замовчуванню (1 граната, Gun - 10, AK4 - 30 i P90 -
50)
якщо pos > 0 додати зброю в потрібну ячейку як реалізовано
зараз, наприклад щоб мати 2 ножі чи 2 пістолети при бажанні
гравця :-))
Масив зі броєю зробити через константу чи маркос і збільшити до 5
(PLAYER_WEAPON_MAX = 5).
Доробити функцію для виводу - ShowAllWeapons виводить
кількість набоїв для Вогнепальної зброї
На ваш вибір генеруйте винятки в разі помилок
*/

#include <iostream>
using namespace std;
enum wtype {cold, fire, unknown};

class Weapon
{
protected:
	string m_name;
	string m_model;
	wtype m_type;
public:
	Weapon(string model = "", string name = "Unknown Weapon", wtype type = unknown) :
		m_name{ name }, m_model{ model }, m_type{ type } {}

	virtual ~Weapon() //= 0;
	{
		//        cout << "Weapon DESTRUCTOR" << endl;
	}

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
	/*void Print() override {
		cout << getName() << (m_model.empty() ? "" : " " + m_model) << endl;
	}*/
};

class Machete : public ColdWeapon {
public:
	Machete(string model = "") : ColdWeapon(model, "Machete") {}
	void Atack() override {
		cout << "Atack with a Machete !" << endl;
	}
	/*void Print() override {
		cout << getName() << (m_model.empty() ? "" : " " + m_model) << endl;
	}*/
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

//1 Array of Weapon 4
//2 Constructie = NULL
//3 Add (1, 2, Granata)
//4 Remove
//4 Attac ()
//5 Select(1-4) if null selec NEXT
//5.1 ShowAllGans
//6 Create class Granata

typedef Weapon* TpWeapon;
class Player {
	int m_maxWeaponCount = 4;
	TpWeapon* m_pWeaponSt = nullptr;
	int m_activeWeapon = 0;
public:
	Player() {
		//cout << "Player CONSTRUCTOR" << endl;
		m_pWeaponSt = new TpWeapon[m_maxWeaponCount] {NULL};
		//for (int i = 0; i < m_maxWeaponCount; i++) {
		//	m_pWeaponSt[i] = NULL;
		//}
	}

	~Player() {
		//cout << "Player DESTRUCTOR" << endl;
		delete[] m_pWeaponSt;
		//for (int i = 0; i < m_maxWeaponCount; i++) {
		//	Weapon* pWeapon = m_pWeaponSt[i];
		//	if (pWeapon != NULL)
		//		delete pWeapon;
		//}
		//delete m_pWeaponSt;
	}

	void IncreaseWaponsSize(int addCount = 1) {
		int maxWeaponCountTmp = m_maxWeaponCount + addCount;
		TpWeapon* pWeaponStTmp = new TpWeapon[maxWeaponCountTmp] {NULL};
		for (int i = 0; i < m_maxWeaponCount; i++)
			pWeaponStTmp[i] = m_pWeaponSt[i];

		//for (int i = 0; i < maxWeaponCountTmp; i++) {
		//	if (i < m_maxWeaponCount)
		//		pWeaponStTmp[i] = m_pWeaponSt[i];
		//	else
		//		pWeaponStTmp[i] = NULL;
		//}
		if (m_pWeaponSt != nullptr)
			delete[] m_pWeaponSt;
		m_maxWeaponCount = maxWeaponCountTmp;
		m_pWeaponSt = pWeaponStTmp;
		cout << "Weapons increased to " << m_maxWeaponCount << endl;
	}

	bool Add(Weapon* pWeapon, int pos = 0) //1-4
	{
		if (pWeapon == NULL)
			return false;
		pos--;
		if (pos < 0) {
			if (pos == -1 && pWeapon->getType() == fire) {
				FireWeapon** tmp = (FireWeapon**)m_pWeaponSt;
				for (int i = 0; i < m_maxWeaponCount; i++)
					if (tmp[i]->getName() == pWeapon->getName()) {
						tmp[i]->addBullet();
						break;
					}
				return true;
			}
			for (int i = 0; i < m_maxWeaponCount; i++) {
				if (m_pWeaponSt[i] == NULL) {
					pos = i;
					break;
				}
			}
		}
		if (pos >= 0 && pos < m_maxWeaponCount) {
			Weapon* pWeaponTmp = m_pWeaponSt[pos];
			if (pWeaponTmp != NULL)
				delete pWeaponTmp;
			m_pWeaponSt[pos] = pWeapon;
			return true;
		}
		return false;
	}

	void Attack(int pos = 0) //1-4
	{
		pos--;
		Weapon* pWeapon = NULL;
		if (pos >= 0 && pos < m_maxWeaponCount)
			pWeapon = m_pWeaponSt[pos];
		if (pWeapon == NULL) {
			FireWeapon* fpWeapon = nullptr;
			for (int i = 0; i < m_maxWeaponCount; i++) {
				fpWeapon = dynamic_cast <FireWeapon*> (m_pWeaponSt[i]);
				//pWeapon = m_pWeaponSt[i];
				if (fpWeapon) {	//pWeapon != NULL && pWeapon->getType() == fire
					pos = i;
					pWeapon = fpWeapon;
					break;
				}
			}
			if (fpWeapon && !pWeapon->isAvailableWeapon())	//pWeapon != NULL && !pWeapon->isAvailableWeapon()
				for (int i = 0; i < m_maxWeaponCount; i++) {
					ColdWeapon* cpWeapon = dynamic_cast <ColdWeapon*> (m_pWeaponSt[i]);
					//pWeapon = m_pWeaponSt[i];
					if (cpWeapon)	//pWeapon != NULL && pWeapon->getType() == cold
						pWeapon = cpWeapon;
						break;
				}
		}
		if (pWeapon != NULL && pWeapon->isAvailableWeapon()) {
			pWeapon->Atack();
			if (pWeapon->getBullets() == 0 && pWeapon->getType() == fire)
				cout << (pWeapon->getName() == "Granata" ? "No " : "No bullets in ") << pWeapon->getName() << endl;
		}
		else {
			cout << "Attack with hands :((( !" << endl;
		}
	}

	void ShowAllWeapons()
	{
		bool showTitle = false;
		for (int i = 0; i < m_maxWeaponCount; i++) {
			Weapon* pWeapon = m_pWeaponSt[i];
			if (pWeapon != NULL) {
				if (!showTitle) {
					cout << "\n========== Weapons ==========" << endl;
					showTitle = true;
				}
				pWeapon->Print();
			}
		}
		if (showTitle)
			cout << "=============================" << endl << endl;
	}

	void Remove(int pos) //1-4
	{
		pos--;
		if (pos >= 0 && pos < m_maxWeaponCount)
		{
			Weapon* pWeaponTmp = m_pWeaponSt[pos];
			if (pWeaponTmp != NULL) {
				delete pWeaponTmp;
				m_pWeaponSt[pos] = NULL;
			}
		}
	}
};

int main()
{
	Player pl1;
	pl1.Add(new Machete(), 1);
	pl1.Add(new Knife(), 2);
	pl1.Add(new Gun("", 5), 3);
	pl1.Add(new Granata("", 2), 4);
	pl1.ShowAllWeapons();
	pl1.Attack();
	pl1.ShowAllWeapons();
	pl1.Attack();
	pl1.Attack();
	pl1.Attack();
	pl1.Attack();
	pl1.Attack();
	pl1.ShowAllWeapons();

	//pl1.Add(new Gun("", 10), 2);
	//pl1.Attack();
	//pl1.ShowAllWeapons();
	//
	//pl1.Add(new Granata("", 0), 3);
	//pl1.Attack(3);
	//pl1.ShowAllWeapons();

	//pl1.Add(new Knife(), 2);
	//pl1.Attack(1);
	//pl1.ShowAllWeapons();

	//pl1.Add(new Machete(), 1);
	//pl1.Attack(1);
	//pl1.ShowAllWeapons();


	//pl1.Attack(1);
	//pl1.Attack(3);
	////pl1.Add(new Granata(), 1);
	//pl1.Add(new Granata());
	//pl1.Add(new Knife(), 4);
	//pl1.Attack(4);
	//pl1.Attack(1);
	//bool b = pl1.Add(new Granata());
	//if (!b)
	//	cout << "Can't add weapon" << endl;
	//pl1.ShowAllWeapons();
	//pl1.IncreaseWaponsSize();
	//b = pl1.Add(new Granata());
	//if (!b)
	//	cout << "Can't add weapon" << endl;
	//pl1.ShowAllWeapons();

	//cout << "======= Remove 1 and 3 ======" << endl;

	//pl1.Remove(1);
	//pl1.Remove(3);
	//pl1.ShowAllWeapons();
	//pl1.Attack();
}