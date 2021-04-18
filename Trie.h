#pragma once
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Trie {
public:
    vector<shared_ptr<Trie>> children;
    bool isEnd;
    
    Trie():children(26), isEnd(false){}
    ~Trie() = default;

    void insert(const string& word) {
        Trie* node = this;
        for (auto i : word) {
            i -= 'a';
            if (node->children[i] == nullptr) {
                node->children[i] = make_shared<Trie>();
            }
           node = node->children[i].get();
        }
    }
    
    bool search(const string& word) {
        auto ptr = searchPrefix(word);
        if (ptr != nullptr && ptr->isEnd) return true;
        else return false;
    }

    bool searchWith(const string& word) {
        auto ptr = searchPrefix(word);
        if (ptr == nullptr) return false;
        else return true;
    }
    Trie* searchPrefix(const string& word) {
        Trie* node = this;
        for (auto i : word) {
            i -= 'a';
            if (node->children[i] == nullptr) {
                return nullptr;
            }
            else {
                node = node->children[i].get();
            }
        }
        return node;
    }



};
