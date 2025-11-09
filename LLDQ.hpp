#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include "Interfaces.hpp"
#include "LinkedList.hpp"

//  ________________________________________________________________
// |                                                                |
// |                       Linked-List Deque                        |
// |________________________________________________________________|

template <typename T>
class LLDQ : public DequeInterface<T> {
    
private:

    LinkedList<T> list;

public:
    // Constructor
    LLDQ() = default;

    // ================================================================
	//  ________________________________
	// |                                |
	// |          The Big Five          |
	// |________________________________|

    // Copy Constructor
    LLDQ(const LLDQ& other) {
        list = other.list;
    }
    
    // Copy Assignment Operator
    LLDQ& operator=(const LLDQ& other) {
        if (this == &other) return *this;
        list = other.list;
        return *this;
    }

    // Move Constructor
    LLDQ(LLDQ&& other) noexcept {
        list = std::move(other.list);
    }

    // Move Assignment Operator
    LLDQ& operator=(LLDQ&& other) noexcept {
        if (this == &other) return *this;
        list = std::move(other.list);
        return *this;
    }

    // Destructor
    ~LLDQ() = default;

    // ================================================================
	//  ________________________________
	// |                                |
	// |           Accessors            |
	// |________________________________|

    // Returns the head element's data
    const T& front() const override {
        if(list.getHead() == nullptr) throw std::runtime_error("List is empty.");
        return list.getHead()->data; 
    }

    // Returns the tail element's data
    const T& back() const override {
        if(list.getTail() == nullptr) throw std::runtime_error("List is empty.");
        return list.getTail()->data; 
    }

    // Returns the size of the list
    std::size_t getSize() const noexcept override { return list.getCount(); }

    // ================================================================
	//  ________________________________
	// |                                |
	// |            Mutators            |
	// |________________________________|

    // Inserts an element in the front
    void pushFront(const T& item) override { list.addHead(item); }

    // Inserts an element in the back
    void pushBack(const T& item) override { list.addTail(item); }

    // Deletes the element in the front
    T popFront() override {
        if(list.getHead() == nullptr) throw std::runtime_error("List is empty.");
        T headNode = list.getHead()->data;
        list.removeHead();
        return headNode;
    }

    // Deletes the element in the back
    T popBack() override { 
        if(list.getTail() == nullptr) throw std::runtime_error("List is empty.");
        T tailNode = list.getTail()->data;
        list.removeTail();
        return tailNode;
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






