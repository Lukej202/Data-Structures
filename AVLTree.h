//
// Created by lukej on 3/14/2025.
//

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <optional>
#include <string>
#include <vector>


using namespace std;


class AVLNode {
public:
    string key;
    int value;
    int height;
    int balance;
    int leftHeight;
    int rightHeight;
    AVLNode *left;
    AVLNode *right;

    AVLNode(string k, int v) {
        key = k;
        value = v;
        height = 0;
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

    int findHeight(AVLNode *node) {
        if (node == nullptr) {
            this->height = -1;
            return -1;
        }else {
            int leftHeight = findHeight(node->left);
            int rightHeight = findHeight(node->right);
            node->height = max(leftHeight, rightHeight) + 1;
            node->leftHeight = leftHeight;
            node->rightHeight = rightHeight;
            return 1 + max(leftHeight, rightHeight);
        }
    }


    int numChildren(AVLNode *node);

    int getBalance(AVLNode *node) {
        balance = node->leftHeight - node->rightHeight;
        return balance;
    }
};

class AVLNodeVisitor {
public:
    virtual void visit(AVLNode *node) = 0;
};

class AVLNodeVectorVisit : public AVLNodeVisitor {
    public:
    vector<string> keys;
    vector<int> values;
    void visit(AVLNode *node) override{
        keys.push_back(node->key);
        values.push_back(node->value);
    }
};

class AVLTree {

public:
    AVLNode *root;

    int treeSize = 0;

    int treeHeight = -1;

    AVLTree();

    //~AVLTree();

    bool insert(const string& key, int value);

    void insertHelper(AVLNode*& current, AVLNode* insertNode);

    bool remove(const string& key);

    bool removeHelper(AVLNode*& current, const string& key);

    bool contains(const string &key) const;

    bool containsHelper(AVLNode *node, const string &key) const;

    optional<int> get(const string& key) const;

    optional<int> getHelper(AVLNode *node, const string &key) const;

    int& operator[](const string& key);

    int& overLoadOneHelper(const string& key, AVLNode *node);

    vector<int> findRange(string lowKey, string highKey) const;

    void findRangeHelper(AVLNode *node, AVLNodeVisitor& visitor, string lowKey, string highKey) const;

    vector<string> keys() const;

    void keysHelper(AVLNode *node, AVLNodeVisitor& visitor) const;

    size_t size() const;

    size_t getHeight() const;

    //ostream& operator<<(ostream& os, const AVLTree & avltree) const;

    //AVLTree(const AVLTree& other);

    //void operator=(const AVLTree& other);

    void updateBalances(AVLNode *node) {
        if (node == nullptr) {
            return;
        }
        updateBalances(node->left);
        node->getBalance(node);
        updateBalances(node->right);
    }

    void checkBalnces(AVLNode *node) {
        if (node == nullptr) {
            return;
        }
        checkBalnces(node->left);
        if (node->balance > 1 || node->balance < -1) {
            this->Rotate(node);
        }
        checkBalnces(node->right);
    }

    void Rotate(AVLNode*& problemNode) {
        AVLNode* hook = problemNode->right;
        AVLNode* newNode = new AVLNode(problemNode->key, problemNode->value);
        problemNode = hook;
        this->insertHelper(hook, newNode);
    }

};



#endif //AVLTREE_H