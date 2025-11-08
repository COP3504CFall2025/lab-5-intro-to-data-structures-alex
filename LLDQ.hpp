#pragma once
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>

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
	// |     Insertion and Removal      |
	// |________________________________|

    // Core Insertion Operations
    void pushFront(const T& item) override { list.addHead(item); }
    void pushBack(const T& item) override { list.addTail(item); }

    // Core Removal Operations
    T popFront() override {
        if(list.getHead() == nullptr) throw std::runtime_error("List is empty.");
        T headNode = list.getHead()->data;
        list.removeHead();
        return headNode;
    }
    T popBack() override { 
        if(list.getTail() == nullptr) throw std::runtime_error("List is empty.");
        T tailNode = list.getTail()->data;
        list.removeTail();
        return tailNode;
    }

    // ================================================================
	//  ________________________________
	// |                                |
	// |           Accessors            |
	// |________________________________|

    // Element Accessors
    const T& front() const override {
        if(list.getHead() == nullptr) throw std::runtime_error("List is empty.");
        return list.getHead()->data; 
    }

    const T& back() const override {
        if(list.getTail() == nullptr) throw std::runtime_error("List is empty.");
        return list.getTail()->data; 
    }

    // Getter
    std::size_t getSize() const noexcept override { return list.getCount(); }
};






