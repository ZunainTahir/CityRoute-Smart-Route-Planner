#pragma once

template <typename T>
class LinkedStack {
private:
    struct StackNode {
        T data;
        StackNode* next;

        StackNode(T value) {
            data = value;
            next = nullptr;
        }
    };

    StackNode* top;
    int count;

    void copyFrom(const LinkedStack& other) {
        if (other.top == nullptr) {
            return;
        }
        top = new StackNode(other.top->data);
        count = 1;
        StackNode* last = top;
        StackNode* current = other.top->next;
        while (current != nullptr) {
            last->next = new StackNode(current->data);
            last = last->next;
            current = current->next;
            count++;
        }
    }

public:
    LinkedStack() {
        top = nullptr;
        count = 0;
    }

    LinkedStack(const LinkedStack& other) {
        top = nullptr;
        count = 0;
        copyFrom(other);
    }

    LinkedStack& operator=(const LinkedStack& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    ~LinkedStack() {
        clear();
    }

    void push(T value) {
        StackNode* node = new StackNode(value);
        node->next = top;
        top = node;
        count++;
    }

    bool pop(T& value) {
        if (top == nullptr) {
            return false;
        }
        StackNode* old = top;
        value = old->data;
        top = old->next;
        delete old;
        count--;
        return true;
    }

    bool peek(T& value) const {
        if (top == nullptr) {
            return false;
        }
        value = top->data;
        return true;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    void clear() {
        while (top != nullptr) {
            StackNode* old = top;
            top = top->next;
            delete old;
        }
        count = 0;
    }
};
