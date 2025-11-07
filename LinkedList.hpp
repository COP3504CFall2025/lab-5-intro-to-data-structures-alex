#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
private:
struct Node {
    T data;
    Node* prev;
    Node* next;

	Node(const T& value) {
		data = value;
		prev = nullptr;
		next = nullptr;
	}
};

Node* head;
Node* tail;
unsigned int count;

public:

	// Constructor
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

	// Destructor
	~LinkedList() {
		Clear();
	}

	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;}

	Node* getHead() {return head;}
	const Node* getHead() const {return head;}
	Node* getTail() {return tail;}
	const Node* getTail() const {return tail;}
	

	// Insertion
	void addHead(const T& data) {
		Node* newNode = new Node(data);
		head = newNode;
		count++;
	}
	void addTail(const T& data) {
		Node* newNode = new Node(data);
		tail = newNode;
		count++;
	}

	// Removal
	bool removeHead();
	bool removeTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


