//
// Created by lukej on 3/14/2025.
//

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

using namespace std;

class AVLNode {
public:
    string key;
    int value;
    int height;
    AVLNode *left;
    AVLNode *right;

    AVLNode(string k, int v, int h) {
        key = k;
        value = v;
        height = h;
        left = nullptr;
        right = nullptr;

    }

    AVLNode(string k, int h, AVLNode *l, AVLNode *r) {
        key = k;
        height = h;
        left = l;
        right = r;
    }

    void setHeight(int h) {
        height = h;
    }

    int findHeight(AVLNode *node);

    int numChildren(AVLNode *node);

    int getBalance(AVLNode *node);
};

class AVLTree {

public:
    AVLNode *root;

    AVLTree();

    //~AVLTree();

    bool insert(const string& key, int value);

    void insertHelper(AVLNode* current, AVLNode* insertNode);

    bool remove(const string& key);

    bool contains(string &key) const;

    bool containsHelper(const AVLNode *node, string &key) const;

    optional<int> get(const string& key) const;

    int& operator[](const string& key);

    vector<string> findRange(string lowKey, string highKey) const;

    vector<string> keys() const;

    size_t size() const;

    size_t getHeight() const;

    //ostream& operator<<(ostream& os, const AVLTree & avltree) const;

    AVLTree(const AVLTree& other);

    //void operator=(const AVLTree& other);

};



#endif //AVLTREE_H