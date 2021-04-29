#pragma once
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Trie {
public:
    vector<shared_ptr<Trie>> children;
    bool isEnd;
    
    Trie(bool isEnd = false) : children(26), isEnd(isEnd) { }
    ~Trie() = default;

    void insert(const string& word, shared_ptr<Trie> t) {
        shared_ptr<Trie> node = t;
        for (auto i : word) {
            i -= 'a';
            if (node->children[i] == nullptr) {
                node->children[i] = make_shared<Trie>(false);
            }
            node = node->children[i];
        }
        node->isEnd = true;
    }
    
    bool search(const string& word, shared_ptr<Trie> t) {
        auto ptr = searchPrefix(word, t);
        if (ptr != nullptr && ptr->isEnd) return true;
        else return false;
    }

    bool searchWith(const string& word, shared_ptr<Trie> t) {
        auto ptr = searchPrefix(word, t);
        if (ptr == nullptr) return false;
        else return true;
    }

    shared_ptr<Trie> searchPrefix(const string& word, shared_ptr<Trie> t) {
        shared_ptr<Trie> node = t;
        for (auto i : word) {
            i -= 'a';
            if (node->children[i] == nullptr) {
                return nullptr;
            }
            else {
                node = node->children[i];
            }
        }
        return node;
    }



};
