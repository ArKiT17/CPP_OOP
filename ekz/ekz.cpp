// Max Likarenko

#include <iostream>
#include <Windows.h>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

class LogIn {
	map<string, string> account;
public:
	LogIn() { Load(); }
	~LogIn() { Save(); }
	void Load() {
		ifstream fin;
		fin.open("accounts.txt", ios::binary);
		if (!fin.is_open())
			throw exception("Помилка відкриття файлу при завантаженні");
		int size;
		char* tmpF;
		char* tmpS;
		fin.read((char*)&size, sizeof(int));
		while (!fin.eof()) {
			tmpF = new char[size + 1];
			fin.read(tmpF, size);
			tmpF[size] = '\0';
			fin.read((char*)&size, sizeof(int));
			tmpS = new char[size + 1];
			fin.read(tmpS, size);
			tmpS[size] = '\0';
			account.emplace(tmpF, tmpS);
			fin.read((char*)&size, sizeof(int));
		}
		fin.close();
	}
	void Save() {
		ofstream fout;
		fout.open("accounts.txt", ios::binary);
		if (!fout.is_open())
			throw exception("Помилка відкриття файлу при збереженні");
		int size;
		for (auto i = account.begin(); i != account.end(); i++) {
			size = i->first.size();
			fout.write((char*)&size, sizeof(int));
			fout.write(i->first.c_str(), size);
			size = i->second.size();
			fout.write((char*)&size, sizeof(int));
			fout.write(i->second.c_str(), size);
		}
		fout.close();
	}
	void add(string login, string password) {
		if (login.size() > 5 && password.size() > 5)
			if (account.find(login) == account.end())
				account.emplace(login, password);
			else
				throw exception("Данний логін зайнятий");
		else
			throw exception("Логін і пароль повиненні містити не меньше 6 символів");
	}
	string isLogedIn(string login, string password) {
		if (account.find(login) != account.end())
			if (account[login] == password)
				return login;
			else
				throw exception("Неправильний пароль");
		else
			throw exception("Користувача не знайдено");
		return "";
	}
};

class Menu {
	map<string, float> list;
	Menu() { Load(); }
	static Menu* pMenu;
public:
	~Menu() { 
		Save();
		pMenu = nullptr;
	}
	static Menu* getInstance() {
		if (!pMenu)
			pMenu = new Menu;
		return pMenu;
	}
	Menu(const Menu& a) = delete;
	void operator=(const Menu& a) = delete;
	void Load() {
		ifstream fin;
		fin.open("menu.txt");
		if (!fin.is_open())
			throw exception("Помилка відкриття файлу при завантаженні");
		string tmps;
		float tmpf;
		fin >> tmps;
		while (!fin.eof()) {
			fin >> tmpf;
			list.emplace(tmps, tmpf);
			fin >> tmps;
		}
		fin.close();
	}
	void Save() {
		ofstream fout;
		fout.open("menu.txt");
		if (!fout.is_open())
			throw exception("Помилка відкриття файлу при збереженні");
		for (auto i = list.begin(); i != list.end(); i++)
			fout << i->first << " " << i->second << endl;
		fout.close();
	}
	float getPrice(string meal) { return list.find(meal) != list.end() ? list[meal] : -1; }
	void add(string meal, float cost) {
		if (meal != "")
			if (list.find(meal) == list.end())
				list.emplace(meal, cost);
			else
				throw exception("Страва вже є в меню");
		else
			throw exception("Передано пусте поле");
	}
	void remove(string meal) {
		if (meal != "")
			if (list.find(meal) != list.end())
				list.erase(meal);
			else
				throw exception("Страви не існує");
		else
			throw exception("Передано пусте поле");
	}
	void editCost(string meal, float newCost) {
		if (meal != "")
			if (list.find(meal) != list.end())
				list[meal] = newCost;
			else
				throw exception("Страви не існує");
		else
			throw exception("Передано пусте поле");
	}
	void showAll() {
		for (auto i = list.begin(); i != list.end(); i++)
			cout << i->first << "\t\t" << i->second << " грн" << endl;
	}
};

Menu* Menu::pMenu = nullptr;

class Order {
	static int countOrders;
	int number;
	map<string, float> orderList;
	float cost;
	Menu* pMenu;
public:
	Order() {
		pMenu = Menu::getInstance();
		ask();
	}
	int getNumber() const { return number; }
	void suma() {
		cost = 0;
		for (auto i = orderList.begin(); i != orderList.end(); i++)
			cost += i->second;
	}
	void add(string meal) {
		orderList.emplace(meal, pMenu->getPrice(meal));
	}
	void ask() {
		cout << "Що бажаєте замовити? Будь ласка, вибирайте по черзі та повідомте про кінець замовлення (кінець)\n\n";
		pMenu->showAll();
		cout << endl;
		string tmp;
		cin >> tmp;
		while (tmp != "кінець" && tmp != "Кінець") {
			if (pMenu->getPrice(tmp) != -1)
				add(tmp);
			else
				cout << tmp << " в меню немає\n";
			cin >> tmp;
		}
		suma();
		countOrders++;
		number = countOrders;
		cout << "\nВаш заказ сформовано під номером " << number << ". Загальна сума - " << cost << " грн.\n";
	}
	void showOrder() {
		cout << "Замовлення номер " << number << ":\n";
		for (auto i = orderList.begin(); i != orderList.end(); i++)
			cout << i->first << "\t\t" << i->second << " грн" << endl;
		cout << endl;
	}
};

int Order::countOrders = 0;

class Cafe {
	string loggedIn;
	LogIn login;
	vector<Order> ordList;
	Menu* pMenu;
	static Cafe* pCafe;
	Cafe() : loggedIn{ "" } {
		pMenu = Menu::getInstance();
		Enter();
	}
public:
	~Cafe() { pCafe = nullptr; }
	static Cafe* getInstance() {
		if (!pCafe)
			pCafe = new Cafe;
		return pCafe;
	}
	Cafe(const Cafe& a) = delete;
	void operator=(const Cafe& a) = delete;
	void Enter() {
		while (true) {
			cout << "--- Виберіть дію ---\n";
			cout << "1. Зайти в акаунт\n2. Зареєструватися\n0. Зайти як гість\n";
			int index;
			cin >> index;
			switch (index) {
			case 0: system("cls"); return;
			case 1: {
				system("cls");
				cout << "Введіть логін: ";
				string tmpL, tmpP;
				cin >> tmpL;
				cout << "Введіть пароль: ";
				cin >> tmpP;
				loggedIn = login.isLogedIn(tmpL, tmpP);
				break;
			}
			case 2: {
				system("cls");
				cout << "Введіть логін: ";
				string tmpL, tmpP;
				cin >> tmpL;
				cout << "Введіть пароль: ";
				cin >> tmpP;
				login.add(tmpL, tmpP);
				loggedIn = tmpL;
				break;
			}
			default: {
				cout << "Невірна цифра";
				system("pause");
				system("cls");
			}
			}
			if (loggedIn != "") {
				cout << "Вхід виконано!\n";
				system("pause");
				system("cls");
				break;
			}
			else {
				cout << "На жаль, увійти не вдалось\n";
			}
		}
	}
	void Exit() {
		loggedIn = "";
		cout << "Вихід виконано\n";
	}
	void showMenu() {
		pMenu->showAll();
	}
	void showOrders() {
		if (loggedIn == "admin") {
			if (ordList.size() == 0)
				cout << "Заказів немає\n";
			else
				for (auto i = ordList.begin(); i < ordList.end(); i++)
					i->showOrder();
		}
		else
			cout << "Нестача прав для заданої дії\n";
	}
	void makeOrder() {
		if (loggedIn != "")
			ordList.push_back(Order());
		else
			cout << "Увійдіть або зареєструйтесь\n";
	}
	void removeOrder() {
		if (loggedIn != "") {
			if (loggedIn == "admin") {
				cout << "Введіть номер вашого заказу: ";
				int tnum;
				cin >> tnum;
				auto i = find_if(ordList.begin(), ordList.end(), [tnum] (const Order& order) {
					return tnum == order.getNumber(); });
				if (i != ordList.end()) {
					cout << "Ви впевнені???\n";
					string t;
					cin >> t;
					if (t == "так" || t == "Так" || t == "ТАК") {
						ordList.erase(i);
						cout << "Заказ " << tnum << " видалено\n";
					}
					else
						cout << "Заказ " << tnum << " не видалено\n";
				}
				else
					cout << "Заказ " << tnum << " не знайдено\n";
			}
			else
				cout << "Нестача прав для заданої дії\n";
		}
		else
			cout << "Увійдіть або зареєструйтесь\n";
	}
};

Cafe* Cafe::pCafe = nullptr;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try {
		Cafe* cafe = Cafe::getInstance();
		while (true) {
			cout << "--- Виберіть дію ---\n";
			cout << "1. Виконати вхід\n2. Меню\n3. Зробити замовлення\n4. Показати список замовлень\n";
			cout << "5. Видалити заказ\n6. Вийти з акаунту\n0. Вихід\n";
			int index;
			cin >> index;
			system("cls");
			switch (index) {
			case 0: break;
			case 1: cafe->Enter(); break;
			case 2: cafe->showMenu(); system("pause"); break;
			case 3: cafe->makeOrder(); system("pause"); break;
			case 4: cafe->showOrders(); system("pause"); break;
			case 5: cafe->removeOrder(); system("pause"); break;
			case 6: cafe->Exit(); system("pause"); break;
			default: cout << "Неправильна цифра";
			}
			system("cls");
			break;
		}
		delete Menu::getInstance();
		delete Cafe::getInstance();
	}
	catch (exception e) {
		cout << e.what();
	}
}