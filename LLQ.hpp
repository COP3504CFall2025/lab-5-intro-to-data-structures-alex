#pragma once
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

//  ________________________________________________________________
// |                                                                |
// |                       Linked-List Queue                        |
// |________________________________________________________________|

template <typename T>
class LLQ : public QueueInterface<T> {

private:

    LinkedList<T> list;
    
public:

    // Constructor
    LLQ() = default;

    // ================================================================
	//  ________________________________
	// |                                |
	// |          The Big Five          |
	// |________________________________|

    // Copy Constructor
    LLQ(const LLQ& other) {
        list = other.list;
    }
    
    // Copy Assignment Operator
    LLQ& operator=(const LLQ& other) {
        if (this == &other) return *this;
        list = other.list;
        return *this;
    }

    // Move Constructor
    LLQ(LLQ&& other) noexcept {
        list.head = other.list.getHead();
        list.tail = other.list.getTail();
        list.count = other.list.getCount();
        
        other.list.head = nullptr
        other.list.tail = nullptr;
        other.list.count = 0;
    }

    // Move Assignment Operator
    LLQ& operator=(LLQ&& other) noexcept {
        if (this == &other) return *this;

        list.head = other.list.getHead();
        list.tail = other.list.getTail();
        list.count = other.list.getCount();

        other.list.head = nullptr
        other.list.tail = nullptr;
        other.list.count = 0;
        
        return *this;
    }

    // Destructor
    ~LLQ() = default;

    // ================================================================
	//  ________________________________
	// |                                |
	// |      Queue, Dequeue, Peek      |
	// |________________________________|

    // Insertion
    void enqueue(const T& item) override { list.addTail(item); }

    // Deletion
    T dequeue() override {
        if(list.getHead() == nullptr) throw std::runtime_error("List is empty.");
        T headNode = list.getHead()->data;
        list.removeHead();
        return headNode;
    }

    // Access
    T peek() const override { 
        if(list.getHead() == nullptr) throw std::runtime_error("List is empty.");
        return list.getHead()->data; 
    }

    // Getter
    std::size_t getSize() const noexcept override { return list.getCount(); }

    // Print Forward
    void PrintForward() { list.printForward(); }

    // Print Reverse
    void PrintReverse() { list.printReverse(); }

};