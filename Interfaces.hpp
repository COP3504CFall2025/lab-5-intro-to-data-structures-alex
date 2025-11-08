#pragma once
#include <cstddef>
#include <stdexcept>

//  ________________________________________________________________
// |                                                                |
// |                      Interface Classes                         |
// |________________________________________________________________|

// Stack Interface: Defines standard LIFO (Last-In-First-Out) operations
template <typename T>
class StackInterface {
    virtual ~StackInterface() = default;
    virtual void push(const T& item) = 0;
    virtual T pop() = 0;
    virtual T peek() const = 0;
    virtual std::size_t getSize() const noexcept = 0;
};

// Queue Interface: Defines standard FIFO (First-In-First-Out) operations
template <typename T>
class QueueInterface {
    virtual ~QueueInterface() = default;
    virtual void enqueue(const T& item) = 0;
    virtual T dequeue() = 0;
    virtual T peek() const = 0;
    virtual std::size_t getSize() const noexcept = 0;
};

// Deque Interface: Defines double-ended sequential access operations
template <typename T>
class DequeInterface {
    virtual ~DequeInterface() = default;
    virtual void pushFront(const T& item) = 0;
    virtual void pushBack(const T& item) = 0;
    virtual T popFront() = 0;
    virtual T popBack() = 0;
    virtual const T& front() const = 0;
    virtual const T& back() const = 0;
    virtual std::size_t getSize() const noexcept = 0;
};