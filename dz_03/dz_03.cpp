/* Max Likarenko Homework 003 */
/*
Розробити клас String, який в подальшому будемо
використовувати для роботи з рядками.
Клас повинен містити:
● Конструктор за замовчуванням, що дозволяє створити
рядок довжиною 80 символів;
● Конструктор, що дозволяє створювати рядок довільного
розміру;
● Конструктор, який створює рядок і ініціалізує його рядком,
отриманим від користувача.
Необхідно створити деструктор, а також використовувати
механізми делегування конструкторів, якщо це можливо.
Клас повинен містити методи для введення рядків з клавіатури
і виведення рядків на екран.
Також потрібно реалізувати статичну функцію-член, яка буде
повертати кількість створених об’єктів рядків.
*/

#include <iostream>
#include <Windows.h>

using namespace std;

class String {
	char* m_word;
	static int m_count;
public:
	String(int size) : m_word{ size > 0 ? new char[size] : new char[1] } { m_word[size] = '\0';  m_count++; }
	String() : String{ 80 } {}
	String(const char* word) {
		if (word) {
			m_word = new char[strlen(word)] + 1;
			strcpy_s(m_word, strlen(word) + 1, word);
		}
		else
			m_word = nullptr;
		m_count++;
	}
	~String() { delete[] m_word; m_count--; };
	void setWord(const char* word);
	char* getWord() { return m_word; };
	static int getCountObj() { return m_count; };
};
int String::m_count{ 0 };

void String::setWord(const char* word) {
	if (word)
		strcpy_s(m_word, strlen(word) + 1, word);
	else
		m_word = nullptr;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	String w1;
	w1.setWord("Перше слово");
	cout << "w1:\t" << w1.getWord() << endl;
	cout << "Кількість активних об'єктів - " << String::getCountObj() << endl;
	String w2("Друге_слово");
	cout << "w2:\t" << w2.getWord() << endl;
	cout << "Кількість активних об'єктів - " << String::getCountObj() << endl;
	String w3(15);
	cout << "w3:\t" << "кількість символів - " << strlen(w3.getWord()) << endl;
	cout << "Кількість активних об'єктів - " << String::getCountObj() << endl;
}