#pragma once
// ---------------------------------------------------------------------------
// ArrayStack.h
// Owner: Member 2
//
// LIFO stack stored in a dynamically growing array.
//
// Complexity
//   push   O(1) amortised (the array doubles when full)
//   pop    O(1)
//   peek   O(1)
//   clear  O(1)
//
// Planned use in CityRoute: rebuilding a route by popping the parent chain
// (Router, Day 8) and as the array-based backend compared with LinkedStack
// in the benchmark module.
// ---------------------------------------------------------------------------

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class ArrayStack {
public:
    explicit ArrayStack(std::size_t initialCapacity = 16)
        : data_(nullptr), size_(0), capacity_(initialCapacity == 0 ? 1 : initialCapacity) {
        data_ = new T[capacity_];
    }

    ~ArrayStack() { delete[] data_; }

    // Copy constructor: deep copy of the used part of the array.
    ArrayStack(const ArrayStack& other)
        : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    // Move constructor: steal the buffer, leave the source empty but valid.
    ArrayStack(ArrayStack&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Copy-and-swap assignment (handles both copy and move assignment).
    ArrayStack& operator=(ArrayStack other) {
        swap(other);
        return *this;
    }

    void swap(ArrayStack& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // Pushes a value on top of the stack.
    void push(const T& value) {
        if (size_ == capacity_) {
            grow();
        }
        data_[size_++] = value;
    }

    void push(T&& value) {
        if (size_ == capacity_) {
            grow();
        }
        data_[size_++] = std::move(value);
    }

    // Removes and returns the top element. Throws std::underflow_error if empty.
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("ArrayStack::pop on an empty stack");
        }
        return std::move(data_[--size_]);
    }

    // Returns a reference to the top element without removing it.
    // Throws std::underflow_error if empty.
    T& peek() {
        if (isEmpty()) {
            throw std::underflow_error("ArrayStack::peek on an empty stack");
        }
        return data_[size_ - 1];
    }

    const T& peek() const {
        if (isEmpty()) {
            throw std::underflow_error("ArrayStack::peek on an empty stack");
        }
        return data_[size_ - 1];
    }

    bool isEmpty() const { return size_ == 0; }
    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }

    // Logically empties the stack (the buffer is kept for reuse).
    void clear() { size_ = 0; }

private:
    void grow() {
        std::size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* bigger = new T[newCapacity];
        for (std::size_t i = 0; i < size_; ++i) {
            bigger[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = bigger;
        capacity_ = newCapacity;
    }

    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};
