#pragma once

template <typename T>
class SinglyLinkedList {
public:
    struct ListNode {
        T data;
        ListNode* next;

        ListNode(T value) {
            data = value;
            next = nullptr;
        }
    };

private:
    ListNode* head;
    ListNode* tail;
    int count;

    void copyFrom(const SinglyLinkedList& other) {
        ListNode* current = other.head;
        while (current != nullptr) {
            pushBack(current->data);
            current = current->next;
        }
    }

    ListNode* nodeAt(int index) const {
        ListNode* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }

public:
    SinglyLinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    SinglyLinkedList(const SinglyLinkedList& other) {
        head = nullptr;
        tail = nullptr;
        count = 0;
        copyFrom(other);
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    ~SinglyLinkedList() {
        clear();
    }

    void pushFront(T value) {
        ListNode* node = new ListNode(value);
        node->next = head;
        head = node;
        if (tail == nullptr) {
            tail = node;
        }
        count++;
    }

    void pushBack(T value) {
        ListNode* node = new ListNode(value);
        if (tail == nullptr) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
        count++;
    }

    bool popFront(T& value) {
        if (head == nullptr) {
            return false;
        }
        ListNode* old = head;
        value = old->data;
        head = old->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete old;
        count--;
        return true;
    }

    bool insertAt(int index, T value) {
        if (index < 0 || index > count) {
            return false;
        }
        if (index == 0) {
            pushFront(value);
            return true;
        }
        if (index == count) {
            pushBack(value);
            return true;
        }
        ListNode* before = nodeAt(index - 1);
        ListNode* node = new ListNode(value);
        node->next = before->next;
        before->next = node;
        count++;
        return true;
    }

    bool removeAt(int index) {
        if (index < 0 || index >= count) {
            return false;
        }
        if (index == 0) {
            T temp;
            return popFront(temp);
        }
        ListNode* before = nodeAt(index - 1);
        ListNode* target = before->next;
        before->next = target->next;
        if (target == tail) {
            tail = before;
        }
        delete target;
        count--;
        return true;
    }

    T* front() const {
        if (head == nullptr) {
            return nullptr;
        }
        return &head->data;
    }

    T* back() const {
        if (tail == nullptr) {
            return nullptr;
        }
        return &tail->data;
    }

    T* at(int index) const {
        if (index < 0 || index >= count) {
            return nullptr;
        }
        return &nodeAt(index)->data;
    }

    bool contains(T value) const {
        ListNode* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void reverse() {
        ListNode* before = nullptr;
        ListNode* current = head;
        tail = head;
        while (current != nullptr) {
            ListNode* after = current->next;
            current->next = before;
            before = current;
            current = after;
        }
        head = before;
    }

    void clear() {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* after = current->next;
            delete current;
            current = after;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ListNode* getHead() const {
        return head;
    }

    int size() const {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }
};
