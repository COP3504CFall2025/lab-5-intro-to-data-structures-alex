#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"
#include <utility>
using namespace std;

//  ________________________________________________________________
// |                                                                |
// |                       Array-Based Deque                        |
// |________________________________________________________________|

template <typename T>
class ABDQ : public DequeInterface<T> {

private:

	//  ________________________________
	// |                                |
	// |           Attributes           |
	// |________________________________|

    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)
    static constexpr std::size_t SCALE_FACTOR = 2;

public:

	// ================================================================
	//  ________________________________
	// |                                |
	// |          Constructors          |
	// |________________________________|

    // Default Constructor
    ABDQ() {
        capacity_ = 4;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }

    // Parameterized Constructor
    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity];
    }

    // ================================================================
	//  ________________________________
	// |                                |
	// |          The Big Five          |
	// |________________________________|

    // Copy Constructor
    ABDQ(const ABDQ& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[other.capacity_];

        for (size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
    }

    // Copy Assignment Operator 
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;

        delete[] data_;

        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[other.capacity_];

        for (size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }

        return *this;
    }

    // Move Constructor
    ABDQ(ABDQ&& other) noexcept {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    // Move Assignment Operator
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) return *this;

        delete[] data_;

        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;
    }

    // Destructor
    ~ABDQ() override {
        delete[] data_;
        capacity_ = 0;
		size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // ================================================================

    //  ________________________________
	// |                                |
	// |            Methods             |
	// |________________________________|

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) { ensureCapacity(); }
        front_ = (front_ == 0) ? capacity_ - 1 : front_ - 1;
        data_[front_] = item;
        size_++;
    }

    void pushBack(const T& item) override {
        if (size_ == capacity_) { ensureCapacity(); }
        back_ = (back_ + 1) % capacity_;
        data_[back_] = item;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) throw std::runtime_error("Array is empty.");
        T item = data_[front_];

        front_ = (front_ + 1) % capacity_;
        size_--;

        if (size_ == capacity_ / SCALE_FACTOR) { shrinkIfNeeded(); }

        return item;
    }

    T popBack() override {
        if (size_ == 0) throw std::runtime_error("Array is empty.");
        T item = data_[back_];

        back_ = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        size_--;

        if (size_ == capacity_ / SCALE_FACTOR) { shrinkIfNeeded(); }

        return item;
    }

    // Access
    const T& front() const override { 
        if (size_ == 0) throw std::runtime_error("Array is empty.");
        return data_[front_]; 
    }
    const T& back() const override { 
        if (size_ == 0) throw std::runtime_error("Array is empty.");
        return data_[back_]; 
    }

    // Getters
    std::size_t getSize() const noexcept override { return size_; }

    void ensureCapacity() {
        T* newData = new T[capacity_ * SCALE_FACTOR];
        for (size_t i = 0; i < size_; i++) {
            newData[i] = data_[(front_ + i) % capacity_];
        }
        delete[] data_;
        data_ = newData;
        capacity_ *= SCALE_FACTOR;
        front_ = 0;
        back_ = size_ - 1;
    }

    void shrinkIfNeeded() {
        T* newData = new T[capacity_ / SCALE_FACTOR];
        for (size_t i = 0; i < size_; i++) {
            newData[i] = data_[(front_ + i) % capacity_];
        }
        delete[] data_;
        data_ = newData;
        capacity_ /= SCALE_FACTOR;
        front_ = 0;
        back_ = size_ - 1;
    }

    void PrintForward() {
        for (size_t i = 0; i < size_; i++) {
            cout << data_[(front_ + i) % capacity_] << " ";
        }
        cout << endl;
    }

    void PrintReverse() {
        for (size_t i = size_; i > 0; i++) {
            cout << data_[(front_ + (i - 1)) % capacity_] << " ";
        }
        cout << endl;
    }

};
