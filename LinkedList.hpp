#pragma once
#include <iostream>
using namespace std;

//  ________________________________________________________________
// |                                                                |
// |                      Linked List Class                         |
// |________________________________________________________________|


template <typename T>
class LinkedList {

// ================================================================

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




// ================================================================

public:


	// ================================================================

	// CONSTRUCTOR AND DESTRUCTOR

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


	// ================================================================

	// PRINTERS

	void printForward() const;
	void printReverse() const;


	// ================================================================

	// ACCESSORS

	[[nodiscard]] unsigned int getCount() const {return count;}
	Node* getHead() {return head;}
	const Node* getHead() const {return head;}
	Node* getTail() {return tail;}
	const Node* getTail() const {return tail;}
	

	// ================================================================

	// INSERTION

	// Add new node to the head
	void addHead(const T& data) {
		Node* newNode = new Node(data);

		if (head == nullptr) { // If list is empty
			head = newNode;
			tail = newNode;
		} else { // If there is one node (head = currentNode)
			newNode->next = head; // newNode[next] --> currentNode
			head->prev = newNode; // newNode <-- currentNode[prev]
			head = newNode; // head = newNode
		}
		count++;
	}

	// Add new node to the tail
	void addTail(const T& data) {
		Node* newNode = new Node(data);

		if (tail == nullptr) { // If list is empty
			head = newNode;
			tail = newNode;
		} else { // If there is one node (tail = currentNode)
			newNode->prev = head; // currentNode <-- newNode[prev]
			tail->next = newNode; // currentNode[next] --> newNode
			tail = newNode; // tail = newNode
		}
		count++;
	}


	// ================================================================

	// REMOVAL

	bool removeHead() {
		if (head == nullptr) { // If list is empty
			return false
		} else {
			Node* temp = head; // temp = oldHead
			head = head->next; // oldHead[next] --> newHead
			if (head) {
				head->prev = nullptr; // oldHead <-- newHead[prev]
			} 
			delete temp; // null <-- newHead[prev]
			count--;
		}
	}

	bool removeTail() {
		if (tail == nullptr) { // If list is empty
			return false
		} else {
			Node* temp = tail; // temp = oldTail
			tail = tail->prev; // newTail <-- oldTail[prev]
			if (tail) {
				tail->next = nullptr; // newTail[next] --> oldTail
			} 
			delete temp; // newTail[next] --> null
			count--;
		}
	}

	void Clear() {
		while(head) {
			Node* temp = head;
			head = head->next;
			if (head) {
				head->prev = nullptr;
			}
			delete temp;
			count--;
		}
		tail = nullptr;
	}


	// ================================================================

	// THE BIG FIVE


	// Constructor
	LinkedList();

	// Destructor
	~LinkedList();

	// Copy constructor
	LinkedList(const LinkedList<T>& list);

	// Copy assignment operator
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Move constructor
	LinkedList(LinkedList<T>&& other) noexcept;

	// Move assignment operator
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;

};


