#include <iostream>
#include <Windows.h>

using namespace std;

class Array {
	int* arr;
	int count;
public:
	Array() : arr{ nullptr }, count{ 0 } {}
	Array(int size) : arr{ new int[size] }, count{ size } {}
	Array(const Array& obj) {
		arr = new int[obj.count];
		for (int i = 0; i < obj.count; i++)
			arr[i] = obj.arr[i];
		count = obj.count;
	}
	~Array() { delete[] arr; }
	void setCount(int size) { arr = new int[size]; count = size; };
	void setValue(int index, int value) {
		if (index >= 0 && index <= count)
			arr[index] = value;
	}
	int* getValue(int index) {
		if (index >= 0 && index <= count)
			return arr + index;
		else
			return nullptr;
	}
	void newCount(int newSize) {
		int* arr2 = new int[newSize];
		for (int i = 0; i < newSize; i++)
			if (i > count)
				arr2[i] = 0;
			else
				arr2[i] = arr[i];
		delete[] arr;
		arr = arr2;
	}
	void sort() {
		int help;
		for (int i = 1; i < count; i++)
			for (int j = count; j > i; j--)
				if (arr[j - 1] > arr[j]) {
					help = arr[j - 1];
					arr[j - 1] = arr[j];
					arr[j] = help;
				}
	}
	int getMax() {
		int max = arr[0];
		for (int i = 1; i < count; i++)
			if (arr[i] > max)
				max = arr[i];
		return max;
	}
	int getMin() {
		int min = arr[0];
		for (int i = 1; i < count; i++)
			if (arr[i] < min)
				min = arr[i];
		return min;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}