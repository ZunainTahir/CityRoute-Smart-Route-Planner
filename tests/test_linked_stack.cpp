#include <iostream>
#include <string>
#include "LinkedStack.h"
#include "ArrayStack.h"
using namespace std;

int failures = 0;

void check(bool ok, string name) {
    if (!ok) {
        cout << "FAILED: " << name << endl;
        failures++;
    }
}

void testOrder() {
    LinkedStack<int> s;
    check(s.isEmpty(), "new stack is empty");

    s.push(1);
    s.push(2);
    s.push(3);
    check(s.size() == 3, "size after 3 pushes");

    int x = 0;
    check(s.pop(x) && x == 3, "first pop gives 3");
    check(s.pop(x) && x == 2, "second pop gives 2");
    check(s.pop(x) && x == 1, "third pop gives 1");
    check(s.isEmpty(), "empty after popping everything");
}

void testPeek() {
    LinkedStack<int> s;
    s.push(42);
    s.push(43);

    int x = 0;
    check(s.peek(x) && x == 43, "peek gives the top");
    check(s.size() == 2, "peek does not remove");
}

void testEmpty() {
    LinkedStack<int> s;
    int x = 0;
    check(!s.pop(x), "pop on empty fails");
    check(!s.peek(x), "peek on empty fails");

    s.push(5);
    s.pop(x);
    check(!s.pop(x), "pop fails again after emptying");
    s.push(6);
    check(s.pop(x) && x == 6, "works after being emptied");
}

void testClear() {
    LinkedStack<int> s;
    s.push(1);
    s.push(2);
    s.clear();
    check(s.isEmpty(), "clear empties the stack");
    check(s.size() == 0, "size is 0 after clear");

    s.push(9);
    int x = 0;
    check(s.pop(x) && x == 9, "stack works after clear");
}

void testCopy() {
    LinkedStack<string> a;
    a.push("Saddar");
    a.push("Blue Area");

    LinkedStack<string> b = a;
    b.push("Faisal Mosque");
    check(a.size() == 2, "original not changed by copy");
    check(b.size() == 3, "copy has the extra item");

    string s;
    check(b.pop(s) && s == "Faisal Mosque", "copy top");
    check(b.pop(s) && s == "Blue Area", "copy keeps the same order");
    check(b.pop(s) && s == "Saddar", "copy bottom");

    LinkedStack<string> c;
    c.push("old");
    c = a;
    check(c.size() == 2, "assignment replaces the old items");
    check(c.pop(s) && s == "Blue Area", "assigned copy has the same top");

    LinkedStack<string>& same = c;
    c = same;
    check(c.size() == 1, "self assignment is fine");
}

void testBigStack() {
    LinkedStack<int> s;
    int n = 200000;
    for (int i = 0; i < n; i++) {
        s.push(i);
    }
    check(s.size() == n, "size after 200000 pushes");

    int x = 0;
    long long sum = 0;
    while (s.pop(x)) {
        sum += x;
    }
    check(sum == (long long)n * (n - 1) / 2, "sum of everything popped");
    check(s.isEmpty(), "empty at the end");
}

void testSameAsArrayStack() {
    LinkedStack<int> linked;
    ArrayStack<int> array;
    bool same = true;
    int a = 0;
    int b = 0;

    for (int i = 0; i < 1000; i++) {
        if (i % 3 == 2) {
            bool gotA = linked.pop(a);
            bool gotB = array.pop(b);
            if (gotA != gotB || (gotA && a != b)) {
                same = false;
            }
        } else {
            linked.push(i * 7);
            array.push(i * 7);
        }
        if (linked.size() != array.size()) {
            same = false;
        }
    }
    check(same, "gives the same answers as ArrayStack");
}

int main() {
    testOrder();
    testPeek();
    testEmpty();
    testClear();
    testCopy();
    testBigStack();
    testSameAsArrayStack();

    if (failures == 0) {
        cout << "test_linked_stack: all passed" << endl;
        return 0;
    }
    cout << "test_linked_stack: " << failures << " failed" << endl;
    return 1;
}
