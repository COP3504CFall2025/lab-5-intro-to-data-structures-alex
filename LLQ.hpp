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
        list = std::move(other.list);
    }

    // Move Assignment Operator
    LLQ& operator=(LLQ&& other) noexcept {
        if (this == &other) return *this;
        list = std::move(other.list);
        return *this;
    }

    // Destructor
    ~LLQ() = default;

    // ================================================================
	//  ________________________________
	// |                                |
	// |           Accessors            |
	// |________________________________|

    // Returns the head element's data
    T peek() const override { 
        if(list.getHead() == nullptr) throw std::runtime_error("List is empty.");
        return list.getHead()->data; 
    }

    // Returns the size of the list
    std::size_t getSize() const noexcept override { return list.getCount(); }

    // ================================================================
	//  ________________________________
	// |                                |
	// |            Mutators            |
	// |________________________________|

    // Inserts an element in queue
    void enqueue(const T& item) override { list.addTail(item); }

    // Deletes the last element in the queue
    T dequeue() override {
        if(list.getHead() == nullptr) throw std::runtime_error("List is empty.");
        T headNode = list.getHead()->data;
        list.removeHead();
        return headNode;
    }

    // ================================================================
	//  ________________________________
	// |                                |
	// |            Printers            |
	// |________________________________|

    // Prints elements from front to back
    void PrintForward() { list.printForward(); }

    // Prints elements from back to front
    void PrintReverse() { list.printReverse(); }

};