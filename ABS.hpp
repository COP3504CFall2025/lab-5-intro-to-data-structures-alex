#pragma once
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
using std::size_t; // Technically bad, but size_t isn't likely to conflict with any client code.

//  ________________________________________________________________
// |                                                                |
// |                       Array-Based Stack                        |
// |________________________________________________________________|

template<typename T>
class ABS : public StackInterface<T> {

private:

    // ================================================================
    //  ________________________________
    // |                                |
    // |           Attributes           |
    // |________________________________|

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
    ABS() {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }

    // Parameterized Constructor
    explicit ABS(const size_t capacity) {
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
    ABS(const ABS& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[other.capacity_];

        for (size_t i = 0; i < other.curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }

    // Copy Assignment Operator
    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) return *this;

        delete[] array_;

        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;

        return *this;
    }

    // Move Constructor
    ABS(ABS&& other) noexcept {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;

        other.array_ = nullptr;
		other.capacity_ = 0;
		other.curr_size_ = 0;
    }

    // Move Assignment Operator
    ABS& operator=(ABS&& rhs) noexcept {
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
    ~ABS() noexcept override {
        delete[] array_;
        capacity_ = 0;
		curr_size_ = 0;
    }

	// ================================================================
	//  ________________________________
	// |                                |
	// |           Accessors            |
	// |________________________________|

    // Returns the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}

    // Returns the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}

    // Returns underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {return array_;}

    // ================================================================
	//  ________________________________
	// |                                |
	// |        Push, Peek, Pop         |
	// |________________________________|

    // Pushes item onto the stack
    void push(const T& data) override {
        if (capacity_ == curr_size_) {
            capacity_ *= scale_factor_;
            T* newArray = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                newArray[i] = array_[i];
            }
            delete[] array_;
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    // Returns top element
    T peek() const override {
        if (curr_size_ == 0) throw std::out_of_range("Array is empty.");
        return array_[curr_size_ - 1];
    }

    // Removes the last inserted element
    T pop() override {
        if (curr_size_ == 0) throw std::out_of_range("Array is empty.");
        T item = array_[curr_size_ - 1];
        curr_size_--;
        return item;
    }
};
