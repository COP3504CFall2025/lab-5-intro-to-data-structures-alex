#pragma once
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

//  ________________________________________________________________
// |                                                                |
// |                       Linked-List Stack                        |
// |________________________________________________________________|

template <typename T>
class LLS : public StackInterface<T> {

private:

    LinkedList<T> list;

public:

    // Constructor
    LLS() = default;

    // ================================================================
	//  ________________________________
	// |                                |
	// |          The Big Five          |
	// |________________________________|

    // Copy Constructor
    LLS(const LLS& other) {
        list = other.list;
    }
    
    // Copy Assignment Operator
    LLS& operator=(const LLS& other) {
        if (this == &other) return *this;
        list = other.list;
        return *this;
    }

    // Move Constructor
    LLS(LLS&& other) noexcept {
        list = other.list;
        other.list.clear();
    }

    // Move Assignment Operator
    LLS& operator=(LLS&& other) noexcept {
        if (this == &other) return *this;
        list = other.list;
        other.list.clear();
        return *this;
    }

    // Destructor
    ~LLS() = default;

    // ================================================================
	//  ________________________________
	// |                                |
	// |            Mutators            |
	// |________________________________|

    // Inserts an element on top
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletes the element on top
    T pop() override {
        if (list.getCount() == 0) throw std::runtime_error("List is empty.");
        T headNode = list.getHead()->data;
        list.removeHead();
        return headNode;
    }

    // ================================================================
	//  ________________________________
	// |                                |
	// |           Accessors            |
	// |________________________________|

    // Returns the head element's data
    T peek() const override {
        if (list.getCount() == 0) throw std::runtime_error("List is empty.");
        return list.getHead()->data;
    }

    // Returns the size of the list
    std::size_t getSize() const noexcept override { return list.getCount(); }

    // ================================================================
	//  ________________________________
	// |                                |
	// |            Printers            |
	// |________________________________|

    // Prints elements from top to bottom
    void PrintForward() { list.printForward(); }

    // Prints elements from bottom to top
    void PrintReverse() { list.printReverse(); }
    
};