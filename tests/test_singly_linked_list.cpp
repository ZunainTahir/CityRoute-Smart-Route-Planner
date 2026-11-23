#include <iostream>
#include <string>
#include "SinglyLinkedList.h"
using namespace std;

int failures = 0;

void check(bool ok, string name) {
    if (!ok) {
        cout << "FAILED: " << name << endl;
        failures++;
    }
}

bool isSame(SinglyLinkedList<int>& list, int expected[], int n) {
    if (list.size() != n) {
        return false;
    }
    SinglyLinkedList<int>::ListNode* p = list.getHead();
    for (int i = 0; i < n; i++) {
        if (p == nullptr || p->data != expected[i]) {
            return false;
        }
        p = p->next;
    }
    return p == nullptr;
}

void testPushFrontBack() {
    SinglyLinkedList<int> list;
    check(list.isEmpty(), "new list is empty");

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushFront(0);

    int expected[] = {0, 1, 2, 3};
    check(isSame(list, expected, 4), "order after pushes");
    check(*list.front() == 0, "front is 0");
    check(*list.back() == 3, "back is 3");
}

void testPopFront() {
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);

    int x = 0;
    check(list.popFront(x) && x == 10, "pop gives 10");
    check(list.popFront(x) && x == 20, "pop gives 20");
    check(list.isEmpty(), "empty after popping all");
    check(!list.popFront(x), "pop on empty fails");

    list.pushBack(5);
    check(*list.front() == 5 && *list.back() == 5, "push after emptying");
    check(list.size() == 1, "size is 1");
}

void testInsertAt() {
    SinglyLinkedList<int> list;
    check(list.insertAt(0, 2), "insert into empty list");
    check(list.insertAt(0, 1), "insert at front");
    check(list.insertAt(2, 4), "insert at back");
    check(list.insertAt(2, 3), "insert in the middle");

    int expected[] = {1, 2, 3, 4};
    check(isSame(list, expected, 4), "order after inserts");
    check(*list.back() == 4, "back is 4");

    check(!list.insertAt(10, 99), "bad index rejected");
    check(!list.insertAt(-1, 99), "negative index rejected");
    check(list.size() == 4, "size did not change");
}

void testRemoveAt() {
    SinglyLinkedList<int> list;
    for (int i = 1; i <= 5; i++) {
        list.pushBack(i);
    }

    list.removeAt(2);
    int a[] = {1, 2, 4, 5};
    check(isSame(list, a, 4), "remove middle");

    list.removeAt(0);
    int b[] = {2, 4, 5};
    check(isSame(list, b, 3), "remove head");

    list.removeAt(2);
    int c[] = {2, 4};
    check(isSame(list, c, 2), "remove tail");
    check(*list.back() == 4, "back moved");

    list.pushBack(6);
    int d[] = {2, 4, 6};
    check(isSame(list, d, 3), "pushBack after removing tail");

    check(!list.removeAt(3), "bad index rejected");
}

void testAt() {
    SinglyLinkedList<int> list;
    list.pushBack(7);
    list.pushBack(8);

    check(*list.at(0) == 7, "at 0");
    check(*list.at(1) == 8, "at 1");
    *list.at(1) = 80;
    check(*list.back() == 80, "changing through at works");
    check(list.at(2) == nullptr, "at out of range");
    check(list.at(-1) == nullptr, "at negative");

    SinglyLinkedList<int> empty;
    check(empty.front() == nullptr, "front of empty");
    check(empty.back() == nullptr, "back of empty");
}

void testReverse() {
    SinglyLinkedList<int> empty;
    empty.reverse();
    check(empty.isEmpty(), "reverse empty");

    SinglyLinkedList<int> list;
    for (int i = 1; i <= 4; i++) {
        list.pushBack(i);
    }
    list.reverse();
    int a[] = {4, 3, 2, 1};
    check(isSame(list, a, 4), "reversed order");
    check(*list.back() == 1, "back after reverse");

    list.pushBack(0);
    int b[] = {4, 3, 2, 1, 0};
    check(isSame(list, b, 5), "pushBack after reverse");
}

void testContainsClear() {
    SinglyLinkedList<string> list;
    list.pushBack("Saddar");
    list.pushBack("Blue Area");
    check(list.contains("Saddar"), "contains Saddar");
    check(!list.contains("Murree Road"), "does not contain Murree Road");

    list.clear();
    check(list.isEmpty(), "clear empties it");
    check(!list.contains("Saddar"), "nothing after clear");
}

void testCopy() {
    SinglyLinkedList<int> a;
    a.pushBack(1);
    a.pushBack(2);

    SinglyLinkedList<int> b = a;
    b.pushBack(3);
    int ea[] = {1, 2};
    int eb[] = {1, 2, 3};
    check(isSame(a, ea, 2), "original not changed");
    check(isSame(b, eb, 3), "copy has extra item");

    SinglyLinkedList<int> c;
    c.pushBack(99);
    c = a;
    check(isSame(c, ea, 2), "assignment copies");

    SinglyLinkedList<int>& same = c;
    c = same;
    check(isSame(c, ea, 2), "self assignment is fine");
}

void testBigList() {
    SinglyLinkedList<int> list;
    int n = 200000;
    for (int i = 0; i < n; i++) {
        list.pushBack(i);
    }
    check(list.size() == n, "big list size");

    long long sum = 0;
    SinglyLinkedList<int>::ListNode* p = list.getHead();
    while (p != nullptr) {
        sum += p->data;
        p = p->next;
    }
    check(sum == (long long)n * (n - 1) / 2, "big list sum");
}

int main() {
    testPushFrontBack();
    testPopFront();
    testInsertAt();
    testRemoveAt();
    testAt();
    testReverse();
    testContainsClear();
    testCopy();
    testBigList();

    if (failures == 0) {
        cout << "test_singly_linked_list: all passed" << endl;
        return 0;
    }
    cout << "test_singly_linked_list: " << failures << " failed" << endl;
    return 1;
}
