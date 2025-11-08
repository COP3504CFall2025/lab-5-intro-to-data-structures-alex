#pragma once
#include <iostream>
using namespace std;

//  ________________________________________________________________
// |                                                                |
// |                         Linked-List                            |
// |________________________________________________________________|

template <typename T>
class LinkedList {

private:

	//  ________________________________
	// |                                |
	// |           Attributes           |
	// |________________________________|

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

	// ================================================================
	//  ________________________________
	// |                                |
	// |          The Big Five          |
	// |________________________________|

	// Copy Constructor
	LinkedList(const LinkedList<T>& list) {
		head = nullptr;
		tail = nullptr;
		count = 0;

		Node* current = list.head;
		while(current != nullptr) {
			addTail(current->data);
			current = current->next;
		}
	}

	// Copy Assignment Operator
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) return *this;

		clear();

		Node* current = rhs.head;
		while(current != nullptr) {
			addTail(current->data);
			current = current->next;
		}

		return *this;
	}

	// Move Constructor
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}

	// Move Assignment Operator
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) return *this;

		clear();

		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return *this;
	}

	// Destructor
	~LinkedList() {
		clear();
	}

	// ================================================================
	//  ________________________________
	// |                                |
	// |           Accessors            |
	// |________________________________|

	// Returns the number of nodes
	[[nodiscard]] unsigned int getCount() const { return count; }

	// Returns a pointer to the head node
	Node* getHead() {return head;}
	const Node* getHead() const { return head; }

	// Returns a pointer to the tail node
	Node* getTail() {return tail;}
	const Node* getTail() const { return tail; }

	// ================================================================
	//  ________________________________
	// |                                |
	// |            Printers            |
	// |________________________________|

	// Prints all nodes starting from the head
    void printForward() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr)
                cout << " ";
            current = current->next;
        }
        cout << endl;
    }

	// Prints all nodes starting from the tail
    void printReverse() const {
        Node* current = tail;
        while (current != nullptr) {
            cout << current->data;
            if (current->prev != nullptr)
                cout << " ";
            current = current->prev;
        }
        cout << endl;
    }

	// ================================================================
	//  ________________________________
	// |                                |
	// |           Inserters            |
	// |________________________________|

	// Inserts a new node at the beginning
	void addHead(const T& data) {
		Node* newNode = new Node(data);

		if (head == nullptr) { // If list is empty
			head = newNode;
			tail = newNode;
		} else { // If there is at least one node
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		count++;
	}

	// Inserts a new node at the end
	void addTail(const T& data) {
		Node* newNode = new Node(data);

		if (tail == nullptr) { // If list is empty
			head = newNode;
			tail = newNode;
		} else { // If there is at least one node
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
		count++;
	}

	// ================================================================
	//  ________________________________
	// |                                |
	// |            Removers            |
	// |________________________________|

	// Removes the first node
	bool removeHead() {
		if (head == nullptr) { // If list is empty
			return false;
		} else {
			Node* temp = head;
			head = head->next;
			if (head) {
				head->prev = nullptr;
			} else {
				tail = nullptr;
			}
			delete temp;
			count--;
			return true;
		}
	}

	// Removes the last node
	bool removeTail() {
		if (tail == nullptr) { // If list is empty
			return false;
		} else {
			Node* temp = tail;
			tail = tail->prev;
			if (tail) {
				tail->next = nullptr;
			} else {
				head = nullptr;
			}
			delete temp;
			count--;
			return true;
		}
	}

	// Deletes all nodes
	void clear() {
		while(head) {
			removeHead();
		}
	}
};