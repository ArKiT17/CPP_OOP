// Max Likarenko Homework 025
/*
Написати програму перекладач. Для реалізації напишіть клас
Dictionary.
При створення класу передавати назви файлу (-лів) для словника
• через конструктор - Dictionary(string filename1,...)
{ Load(filename1,..); Load(... );}
• через метод - int Load(string path, string* arr )
{...}
Також додати наступні методи в клас:
• конструктор по замовчуванню - Dictionary(){};
• функцію - string Translate(string word, /змінну
з якої на яку мову перекладати/)
// якщо словники не завантажені викликає throw
• додати використання виключних ситуацій, наприклад
виклику методе для перекладу для об'єкту класу створеного
з конструктором по замовчуванню і не загружених
словниках.
Решту функціоналу придумати самостійно
Словники знайти в інтернеті або взяти тут
Приклад використання класу :
Dictionary dictionary("Eng.txt", "UA.txt");
Dictionary dictionary("Eng.txt", "Rus.txt");
string S1 = dictionary.Translate("go", true); //"EN-UA"
string S2 = dictionary.Translate("йти", false); //"UA-EN"
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Dictionary {
	vector<string> words1;
	vector<string> words2;
public:
	Dictionary() : Dictionary("Eng.txt", "UA.txt") {}
	//Dictionary() {	// несумісні (із частини з кристаликом)
	//	cout << "Ласкаво просимо до перекладача \"Розумна Черепаха\"!\n";
	//	cout << "Будь ласка, завантажте словники командою \"turtle.exe\"\nC:\\";
	//}
	Dictionary (string filename1, string filename2) {
		Load(filename1, words1);
		Load(filename2, words2);
		if (words1.empty() || words2.empty())
			throw 2;
	}
	void LoadSome(string file1, string file2) {
		Load(file1, words1);
		Load(file2, words2);
	}
	void Load(string file, vector<string>& word) {
		ifstream fin;
		fin.open(file);
		if (!fin.is_open())
			throw 1;
		string tmp;
		while (!fin.eof()) {
			getline(fin, tmp);
			word.push_back(tmp);
		}
		fin.close();
	}
	string Translate(string word, bool direction) {
		if (words1.empty() || words2.empty())
			throw 2;
		if (word != "") {
			int index = 0;
			string tmp;
			if (direction) {
				for (int i = 0; i < words1.size(); i++)
					if (words1[i] == word)
						return words2[i];
				return "На жаль, слово у словнику відсутнє.";
			}
			else {
				for (int i = 0; i < words2.size(); i++)
					if (words2[i] == word)
						return words1[i];
				return "На жаль, слово у словнику відсутнє.";
			}
		}
		return "";
	}
	bool isLoad() { return (!words1.empty() && !words2.empty()); }
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
		string tmp;
		while (true) {
			cout << "Виберіть дію:\n1. Англ - Укр\n2. Укр - Англ\n0. Вихід\n";
			cin >> index;
			if (index == 0)
				return 0;
			if (index == 1) {
				cout << "Введіть слово англійською: ";
				cin >> tmp;
				cout << endl << tmp << " - " << dictionary.Translate(tmp, true) << endl << endl;
			}
			else
				if (index == 2) {
					cout << "Введіть слово українською: ";
					cin >> tmp;
					cout << endl << tmp << " - " << dictionary.Translate(tmp, false) << endl << endl;
				}
				else
					cout << "Неправильна цифра :(\n";
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