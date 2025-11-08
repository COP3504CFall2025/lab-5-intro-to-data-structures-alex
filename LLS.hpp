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

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
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

    // Access
    T peek() const override {
        if (list.getCount() == 0) throw std::runtime_error("List is empty.");
        return list.getHead()->data;
    }

    // Get Size
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};