// Max Likarenko Homework 028
/*
Використовуючи контейнер map реалізувати
програму — словник.
Основні можливості:
■ пошук слова;
■ додавання, видалення, редагування слів;
■ читання і запис словника в файл.
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <map>
using namespace std;

class Dictionary {
	multimap<string, string> OneTwo;
	multimap<string, string> TwoOne;
	string from;
	string to;
public:
	Dictionary() : Dictionary("Eng.txt", "UA.txt") {}
	//Dictionary() {
	//	cout << "Ласкаво просимо до перекладача \"Розумна Черепаха\"!\n";
	//	cout << "Будь ласка, завантажте словники командою \"turtle.exe\"\nC:\\";
	//}
	Dictionary(string filename1, string filename2) : from{ filename1 }, to{ filename2 } {
		Load(filename1, filename2, OneTwo);
		Load(filename2, filename1, TwoOne);
		if (OneTwo.empty() || TwoOne.empty())
			throw 2;
	}
	~Dictionary() {
		ofstream fout;
		ofstream fout2;
		fout.open(from);
		fout2.open(to);
		for (auto i = OneTwo.begin(); i != OneTwo.end(); i++) {
			fout << i->first << endl;
			fout2 << i->second << endl;
		}
		fout.close();
		fout2.close();
	}
	void LoadSome(string file1, string file2) {
		Load(file1, file2, OneTwo);
		Load(file2, file1, TwoOne);
	}
	void Load(string file, string file2, multimap<string, string>& m) {
		ifstream fin;
		fin.open(file);
		ifstream fin2;
		fin2.open(file2);
		if (!fin.is_open() || !fin2.is_open())
			throw 1;
		string tmp;
		string tmp2;
		while (!fin.eof() || !fin2.eof()) {
			getline(fin, tmp);
			getline(fin2, tmp2);
			m.emplace(tmp, tmp2);
		}
		fin.close();
		fin2.close();
	}
	string Translate(string word, bool direction) {
		if (OneTwo.empty() || TwoOne.empty())
			throw 2;
		if (word != "") {
			if (direction) {
				if (OneTwo.find(word) == OneTwo.end())
					return "Слово не знайдено";
				return OneTwo.find(word)->second;//OneTwo[word];
			}
			else {
				if (TwoOne.find(word) == TwoOne.end())
					return "Слово не знайдено";
				return TwoOne.find(word)->second;//TwoOne[word];
			}
		}
		return "";
	}
	bool isLoad() { return (!OneTwo.empty() && !TwoOne.empty()); }
	bool Add(string word, string word2) {
		if (word != "") { // && OneTwo.find(word) == OneTwo.end()) {	//OneTwo[word] 
			OneTwo.emplace(word, word2);
			TwoOne.emplace(word2, word);
			return 1;
		}
		else
			return 0;
	}
	bool Remove(string word) {
		if (word != "" && OneTwo.find(word) != OneTwo.end()) {	//OneTwo[word]
			TwoOne.erase(OneTwo.find(word)->second);
			OneTwo.erase(word);
			//			TwoOne.erase(OneTwo[word]);
			return 1;
		}
		else
			return 0;
	}
	bool Edit(string whatWord, string newWord) {
		if (newWord != "" && OneTwo.find(whatWord) != OneTwo.end()){	//OneTwo[whatWord]
			OneTwo.find(whatWord)->second = newWord;	//OneTwo[whatWord]
			return 1;
		}
		else
			return 0;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try {
		Dictionary dictionary;
		if (!dictionary.isLoad()) {
			string turtle;
			cin >> turtle;
			if (turtle == "turtle.exe")
				cout << "Словники завантажені! Дякую!\n";
			else
				cout << "Не так :(\n(Але словники все одно завантажені)\n";
			dictionary.LoadSome("Eng.txt", "UA.txt");
			system("pause");
			system("cls");
		}
		int index;
		string tmp, tmp2;
		bool p = true;
		while (true) {
			cout << "Виберіть дію:\n1. Англ - Укр\n2. Укр - Англ\n0. Вихід\n";
			cin >> index;
			if (index == 0)
				return 0;
			if (index == 2)
				p = false;
			while (true) {
				cout << "\n1. Переклад\n2. Додати слово\n3. Видалити слово\n4. Редагувати слово\n";
				cout << "0. Назад\n";
				cin >> index;
				switch (index) {
				case 0: return 0;
				case 1: {
					cout << "Введіть слово: ";
					cin >> tmp;
					cout << endl << tmp << " - " << dictionary.Translate(tmp, p) << endl;
					break;
				}
				case 2: {
					cout << "Введіть слово та його переклад: ";
					cin >> tmp >> tmp2;
					cout << (dictionary.Add(tmp, tmp2) ? "Слово успішно додано" : "Сталася помилка");
					cout << endl << endl;
					break;
				}
				case 3: {
					cout << "Введіть слово: ";
					cin >> tmp;
					cout << (dictionary.Remove(tmp) ? "Слово успішно видалено" : "Сталася помилка");
					cout << endl;
					break;
				}
				case 4: {
					cout << "Введіть старе та нове слова: ";
					cin >> tmp >> tmp2;
					cout << (dictionary.Edit(tmp, tmp2) ? "Слово відредаговано" : "Сталася помилка");
					cout << endl;
					break;
				}
				default:
					cout << "Невірна цифра." << endl;
				}
			}
		}
		//cout << dictionary.Translate("go", true) << endl; //"EN-UA"
		//cout << dictionary.Translate("йти", false) << endl; //"UA-EN"

		//cout << dictionary.Translate("мета", false) << endl; //"UA-EN"
		//cout << dictionary.Translate("article", true) << endl; //"UA-EN"
		//cout << dictionary.Translate("guarantee", true) << endl; //"UA-EN"
		//cout << dictionary.Translate("інструмент", false) << endl; //"UA-EN"
		//cout << dictionary.Translate("трубка", false) << endl; //"UA-EN"
	}
	catch (int e) {
		switch (e) {
		case 1: cout << "Помилка відкриття файлу."; break;
		case 2: cout << "Словники не завантажені."; break;
		}
	}
}