#include <iostream>

using namespace std;

class Node {
public:
	int data;
	Node* next, *prev;
	Node(int data, Node* next = nullptr, Node* prev = nullptr) : data{ data }, next{ next }, prev{ prev }{ }
};

class List {
	Node* head;
	Node* tail;
public:
	List() : head{ nullptr }, tail{ nullptr } {}
	Node* Add(int data) {
		Node* newNode = new Node(data);
		if (head == nullptr)
			head = newNode;
		if (tail != nullptr) {
			tail->next = newNode;
			newNode->prev = tail;
		}
		tail = newNode;
		return newNode;
	}
	Node* Get(int index) {
		Node* current = head;
		int currentIndex = 0;
		while (current != nullptr) {
			if (currentIndex == index)
				return current;
			current = current->next;
			++currentIndex;
		}
		return nullptr;
	}
	Node* AddToHead(int data) {
		Node* newNode = new Node(data, head);
		if (tail == nullptr)
			tail = newNode;
		head = newNode;
		return newNode;
	}
	bool Insert(int data, int index) {
		if (index == 0) {
			return AddToHead(data) != nullptr;
		}
		Node* current = Get(index - 1);
		if (current != nullptr) {
			Node* newNode = new Node(data, current->next, current);
			current->next->prev = newNode;
			current->next = newNode;
			if (current == tail)
				tail = newNode;
			return true;
		}
		return false;
	}
	bool Delete(int index) {
		if (head == nullptr)
			return false;
		if (index == 0) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
			if (head == nullptr)
				tail = nullptr;
			return true;
		}
		Node* current = Get(index - 1);
		Node* next = current->next;
		if (next == nullptr)
			return false;
		current->next = next->next;
		if(next->next)
			next->next->prev = current;
		delete next;
		if (current->next == nullptr)
			tail = current;
		return true;
	}
	void Print() {
		Node* current = head;
		while (current != nullptr) {
			std::cout << current->data << std::endl;
			current = current->next;
		}
	}
};

int main() {
	List list;

	cout << "==================" << endl;
	list.Print();
	cout << "==================" << endl;
	list.Add(1);
	list.Print();
	cout << "==================" << endl;

	list.Add(2);
	list.Add(3);
	list.Add(4);
	list.Add(5);
	list.Print();
	cout << "==================" << endl;


	list.Delete(4);
	list.Print();
	cout << "==================" << endl;

	list.Delete(0);
	list.Print();
	cout << "==================" << endl;

	list.Delete(1);
	list.Print();
	cout << "==================" << endl;

	list.Delete(0);
	list.Delete(0);
	list.Print();
	cout << "==================" << endl;

	return 0;
}