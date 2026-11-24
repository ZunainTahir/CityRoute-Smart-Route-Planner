#pragma once
#include <string>
using namespace std;

class TrieNode {
public:
    TrieNode* child[128];
    bool isEnd;

    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 128; i++) {
            child[i] = nullptr;
        }
    }

    ~TrieNode() {
        for (int i = 0; i < 128; i++) {
            delete child[i];
        }
    }

    TrieNode(const TrieNode&) = delete;
    TrieNode& operator=(const TrieNode&) = delete;
};

class Trie {
private:
    TrieNode* root;
    int words;

    char toLower(char c) const {
        if (c >= 'A' && c <= 'Z') {
            return (char)(c + 32);
        }
        return c;
    }

    TrieNode* findNode(const string& text) const {
        TrieNode* current = root;
        int len = text.length();
        for (int i = 0; i < len; i++) {
            int index = toLower(text[i]);
            if (index < 0 || index > 127) {
                return nullptr;
            }
            if (current->child[index] == nullptr) {
                return nullptr;
            }
            current = current->child[index];
        }
        return current;
    }

public:
    Trie() {
        root = new TrieNode();
        words = 0;
    }

    ~Trie() {
        delete root;
    }

    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    bool insert(const string& word) {
        int len = word.length();
        if (len == 0) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            int c = word[i];
            if (c < 0 || c > 127) {
                return false;
            }
        }

        TrieNode* current = root;
        for (int i = 0; i < len; i++) {
            int index = toLower(word[i]);
            if (current->child[index] == nullptr) {
                current->child[index] = new TrieNode();
            }
            current = current->child[index];
        }

        if (current->isEnd) {
            return false;
        }
        current->isEnd = true;
        words++;
        return true;
    }

    bool search(const string& word) const {
        if (word.length() == 0) {
            return false;
        }
        TrieNode* node = findNode(word);
        return node != nullptr && node->isEnd;
    }

    int wordCount() const {
        return words;
    }

    bool isEmpty() const {
        return words == 0;
    }
};
