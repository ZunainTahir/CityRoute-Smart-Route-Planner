#include <iostream>
#include <string>
#include "Trie.h"
using namespace std;

int failures = 0;

void check(bool ok, string name) {
    if (!ok) {
        cout << "FAILED: " << name << endl;
        failures++;
    }
}

void testInsertSearch() {
    Trie t;
    check(t.isEmpty(), "new trie is empty");
    check(t.insert("Saddar"), "insert Saddar");
    check(t.insert("Blue Area"), "insert Blue Area");
    check(t.search("Saddar"), "find Saddar");
    check(t.search("Blue Area"), "find Blue Area");
    check(!t.search("Murree Road"), "Murree Road is not there");
    check(t.wordCount() == 2, "two words stored");
}

void testCase() {
    Trie t;
    t.insert("Faisal Mosque");
    check(t.search("faisal mosque"), "lower case search");
    check(t.search("FAISAL MOSQUE"), "upper case search");
    check(t.search("FaIsAl MoSqUe"), "mixed case search");
}

void testPrefix() {
    Trie t;
    t.insert("faisalabad");
    check(!t.search("faisal"), "a prefix is not a word");
    check(!t.search("faisalabadx"), "longer text is not a word");

    t.insert("faisal");
    check(t.search("faisal"), "faisal is a word now");
    check(t.search("faisalabad"), "faisalabad is still there");
}

void testDuplicatesAndEmpty() {
    Trie t;
    check(t.insert("rawalpindi"), "first insert");
    check(!t.insert("rawalpindi"), "duplicate rejected");
    check(!t.insert("RAWALPINDI"), "duplicate with other case rejected");
    check(t.wordCount() == 1, "still one word");

    check(!t.insert(""), "empty word rejected");
    check(!t.search(""), "empty search is false");
}

void testNonAscii() {
    Trie t;
    string bad = "caf";
    bad += (char)200;
    check(!t.insert(bad), "non ascii word rejected");
    check(t.isEmpty(), "nothing was stored");
}

void testManyWords() {
    Trie t;
    for (int i = 0; i < 5000; i++) {
        t.insert("place" + to_string(i));
    }
    check(t.wordCount() == 5000, "5000 words stored");
    check(t.search("place0"), "find first");
    check(t.search("place4999"), "find last");
    check(!t.search("place5000"), "does not find a missing one");
}

int main() {
    testInsertSearch();
    testCase();
    testPrefix();
    testDuplicatesAndEmpty();
    testNonAscii();
    testManyWords();

    if (failures == 0) {
        cout << "test_trie_basic: all passed" << endl;
        return 0;
    }
    cout << "test_trie_basic: " << failures << " failed" << endl;
    return 1;
}
