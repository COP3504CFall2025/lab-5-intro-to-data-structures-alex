#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"
using std::size_t; // Technically bad, but size_t isn't likely to conflict with any client code.
using namespace std;

//  ________________________________________________________________
// |                                                                |
// |                       Array-Based Queue                        |
// |________________________________________________________________|

template<typename T>
class ABQ : public QueueInterface<T>{

private:

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:

	// ================================================================
	//  ________________________________
	// |                                |
	// |          Constructors          |
	// |________________________________|

    // Default Constructor
    ABQ() {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }

    // Parameterized Constructor
    explicit ABQ(const size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity];
    }

    // ================================================================
	//  ________________________________
	// |                                |
	// |          The Big Five          |
	// |________________________________|

    // Copy Constructor
    ABQ(const ABQ& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[other.capacity_];

        for (size_t i = 0; i < other.curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }

    // Copy Assignment Operator
    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) return *this;

        delete[] array_;

        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;

        return *this;
    }

    // Move Constructor
    ABQ(ABQ&& other) noexcept {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;

        other.array_ = nullptr;
		other.capacity_ = 0;
		other.curr_size_ = 0;
    }

    // Move Assignment Operator
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) return *this;

        delete[] array_;

        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;

        rhs.array_ = nullptr;
		rhs.capacity_ = 0;
		rhs.curr_size_ = 0;

        return *this;
    }

    // Destructor
    ~ABQ() noexcept override {
        delete[] array_;
        capacity_ = 0;
		curr_size_ = 0;
    }

	// ================================================================
	//  ________________________________
	// |                                |
	// |           Accessors            |
	// |________________________________|

    // Returns the number of items in the ABQ
    [[nodiscard]] size_t getSize() const noexcept override { return curr_size_; }

    // Returns the max size of the ABQ
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }

    // Returns underlying data for the queue
    [[nodiscard]] T* getData() const noexcept { return array_; }

    // ================================================================
	//  ________________________________
	// |                                |
	// |    Enqueue, Dequeue, Peek      |
	// |________________________________|

    // Adds element to the back
    void enqueue(const T& data) override {
        if (curr_size_ == capacity_) {
            capacity_ *= scale_factor_;
            T* newArray = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                newArray[i] = array_[i];
            }
            delete[] array_;
            array_ = newArray;
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    // Returns element in the front
    T peek() const override {
        if (curr_size_ == 0) throw std::runtime_error("Array is empty.");
        return array_[0];
    }

    // Removes element in the front
    T dequeue() override {
        if (curr_size_ == 0) throw std::runtime_error("Array is empty.");
        T item = array_[0];
        curr_size_--;

        if (curr_size_ < capacity_ / scale_factor_) {
            capacity_ /= scale_factor_;
        }

        T* newArray = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            newArray[i] = array_[i + 1];
        }
        delete[] array_;
        array_ = newArray;

        return item;
    }

    // ================================================================
	//  ________________________________
	// |                                |
	// |            Printers            |
	// |________________________________|

    // Print Forward
    void PrintForward() { 
        for (size_t i = 0; i < curr_size_; i++) {
            cout << array_[i] << " ";
        }
        cout << endl;
    }

    // Print Reverse
    void PrintReverse() {
        for (size_t i = curr_size_; i > 0; i--) {
            cout << array_[i - 1] << " ";
        }
        cout << endl;
    }
};