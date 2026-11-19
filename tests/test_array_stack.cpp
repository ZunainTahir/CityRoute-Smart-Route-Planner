// Tests for ArrayStack (Member 2).
// Plain C++ (no framework): returns 0 when every check passes.

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "ArrayStack.h"

static int g_failures = 0;

#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "FAIL: " #cond " (line " << __LINE__ << ")\n";          \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)

void testLifoOrder() {
    ArrayStack<int> s;
    CHECK(s.isEmpty());
    s.push(1);
    s.push(2);
    s.push(3);
    CHECK(s.size() == 3);
    CHECK(s.pop() == 3);
    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
    CHECK(s.isEmpty());
}

void testPeekDoesNotRemove() {
    ArrayStack<int> s;
    s.push(42);
    CHECK(s.peek() == 42);
    CHECK(s.size() == 1);
    s.peek() = 7;  // peek returns a reference
    CHECK(s.pop() == 7);
}

void testGrowthBeyondInitialCapacity() {
    ArrayStack<int> s(2);
    for (int i = 0; i < 1000; ++i) {
        s.push(i);
    }
    CHECK(s.size() == 1000);
    CHECK(s.capacity() >= 1000);
    bool ordered = true;
    for (int i = 999; i >= 0; --i) {
        if (s.pop() != i) {
            ordered = false;
        }
    }
    CHECK(ordered);
    CHECK(s.isEmpty());
}

void testUnderflowThrows() {
    ArrayStack<int> s;
    bool popThrew = false;
    try {
        s.pop();
    } catch (const std::underflow_error&) {
        popThrew = true;
    }
    CHECK(popThrew);

    bool peekThrew = false;
    try {
        s.peek();
    } catch (const std::underflow_error&) {
        peekThrew = true;
    }
    CHECK(peekThrew);
}

void testClearAndReuse() {
    ArrayStack<int> s;
    s.push(1);
    s.push(2);
    s.clear();
    CHECK(s.isEmpty());
    CHECK(s.size() == 0);
    s.push(9);
    CHECK(s.pop() == 9);
}

void testStringsAndCopy() {
    ArrayStack<std::string> a;
    a.push("Faisal Mosque");
    a.push("Saddar");

    ArrayStack<std::string> b = a;  // deep copy
    b.push("Blue Area");
    CHECK(a.size() == 2);
    CHECK(b.size() == 3);
    CHECK(b.pop() == "Blue Area");
    CHECK(b.pop() == "Saddar");
    CHECK(a.pop() == "Saddar");  // original is unaffected

    ArrayStack<std::string> c;
    c = a;  // copy assignment
    CHECK(c.size() == 1);
    CHECK(c.peek() == "Faisal Mosque");
}

void testMove() {
    ArrayStack<int> a;
    a.push(1);
    a.push(2);
    ArrayStack<int> b = std::move(a);
    CHECK(b.size() == 2);
    CHECK(b.peek() == 2);
    CHECK(a.isEmpty());  // moved-from stack is empty but still usable
    a.push(5);
    CHECK(a.pop() == 5);
}

int main() {
    testLifoOrder();
    testPeekDoesNotRemove();
    testGrowthBeyondInitialCapacity();
    testUnderflowThrows();
    testClearAndReuse();
    testStringsAndCopy();
    testMove();

    if (g_failures == 0) {
        std::cout << "test_array_stack: all tests passed\n";
        return 0;
    }
    std::cerr << "test_array_stack: " << g_failures << " check(s) failed\n";
    return 1;
}
