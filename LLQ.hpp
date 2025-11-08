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
        list = other.list;
        other.list.clear();
    }

    // Move Assignment Operator
    LLQ& operator=(LLQ&& other) noexcept {
        if (this == &other) return *this;
        list = other.list;
        other.list.clear();
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
        T headNode = list.getHead();
        list.removeHead();
        return headNode()->data;
    }

    // Access
    T peek() const override { return list.getHead(); }

    // Getter
    std::size_t getSize() const noexcept override { return list.getCount(); }

    // Print Forward
    void PrintForward() { list.printForward(); }

    // Print Reverse
    void PrintReverse() { list.printReverse(); }

};