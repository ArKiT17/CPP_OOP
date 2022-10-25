#include <iostream>
#include <Windows.h>
#include <vector>
#include <fstream>

using namespace std;

struct Traine {
	string num;
	string time;
	string station;
	Traine() : Traine("", "", "") {}
	Traine(string number, string tim, string statio) : num{ number }, time{ tim }, station{ statio } {}
};

class Info {
	vector<Traine> infolist;
public:
	Info() {
		Load();
	}
	~Info() {
		Save();
	}
	void Load() {
		ifstream fin;
		fin.open("infolist.txt", ios::binary);
		if (!fin.is_open())
			throw 1;
		Traine tmp;
		int numSize = 0;
		char* num = nullptr;
		fin.read((char*)&numSize, sizeof(int));
		while (!fin.eof()) {
			num = new char[numSize + 1];
			fin.read(num, numSize);	//fin.read((char*)&num, numSize);
			num[numSize] = '\0';
			tmp.num = num;
			fin.read((char*)&numSize, sizeof(int));
			num = new char[numSize + 1];
			fin.read(num, numSize);	//fin.read((char*)&num, numSize);
			num[numSize] = '\0';
			tmp.time = num;
			fin.read((char*)&numSize, sizeof(int));
			num = new char[numSize + 1];
			fin.read(num, numSize);	//fin.read((char*)&num, numSize);
			num[numSize] = '\0';
			tmp.station = num;
			infolist.push_back(tmp);
			fin.read((char*)&numSize, sizeof(int));
		}
		fin.close();
	}
	void Save() {
		ofstream fout;
		fout.open("infolist.txt", ios::binary);
		int size;
		for (auto i = infolist.begin(); i < infolist.end(); i++) {
			size = i->num.size();
			fout.write((char*)&size, sizeof(int));
			fout.write(i->num.c_str(), size);
			size = i->time.size();
			fout.write((char*)&size, sizeof(int));
			fout.write(i->time.c_str(), size);
			size = i->station.size();
			fout.write((char*)&size, sizeof(int));
			fout.write(i->station.c_str(), size);
		}
		fout.close();
	}
	void Add(string number, string tim, string statio) {
		infolist.push_back(Traine(number, tim, statio));
	}
	void ShowInfo() {
		for (int i = 0; i < infolist.size(); i++) {
			cout << "Поїзд з номером " << infolist[i].num << " відправляється о ";
			cout << infolist[i].time << " у напрямку " << infolist[i].station << endl << endl;
		}
	}
	void ShowInfo(string word) {
		for (int i = 0; i < infolist.size(); i++) {
			if (infolist[i].num == word) {
				cout << "Поїзд з номером " << infolist[i].num << " відправляється о ";
				cout << infolist[i].time << " у напрямку " << infolist[i].station << endl << endl;
				break;
			}
		}
	}
	void Remove(string word) {
		for (auto i = infolist.begin(); i < infolist.end(); i++) {
			if (i->num == word) {
				infolist.erase(i);
				break;
			}
		}
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try {
		Info a;
		//a.Add("120K", "16:04", "Львів");
		//a.Add("705К", "00:04", "Пшемисль");
		//a.Add("001Д", "23:19", "Івано-Франківськ");
		//a.Add("088П", "00:47", "Луцьк");
		//a.Add("092К", "01:35", "Харків-Пас");
		a.ShowInfo();
		cout << endl;
		a.Remove("001Д");
		a.ShowInfo();
		cout << endl;
		a.ShowInfo("088П");
	}
	catch (int e) {
		switch (e) {
		case 1: cout << "File could not be opened.";
		}
	}
}