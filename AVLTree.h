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
    int depth;
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
    mutable AVLNode *root;

    int treeSize = 0;

    int treeHeight = -1;

    AVLTree();

    ~AVLTree();

    void destructorHelper(const AVLNode *node);

    bool insert(const string& key, int value);

    void insertHelper(AVLNode *&current, AVLNode *insertNode) const;

    bool remove(const string& key);

    bool removeHelper(AVLNode*& current, const string& key);

    bool contains(const string &key) const;

    bool containsHelper(AVLNode *node, const string &key) const;

    optional<int> get(const string& key) const;

    optional<int> getHelper(AVLNode *node, const string &key) const;

    int& operator[](const string& key);

    int& overLoadOneHelper(const string& key, AVLNode *node);

    vector<int> findRange(string lowKey, string highKey) const;

    void findRangeHelper(AVLNode *node, AVLNodeVisitor& visitor, const string& lowKey, const string& highKey) const;

    vector<string> keys() const;

    void keysHelper(AVLNode *node, AVLNodeVisitor& visitor) const;

    size_t size() const;

    size_t getHeight() const;

    friend ostream& operator<<(ostream& os, const AVLTree & avltree);

    ostream& printerHelper(AVLNode* node, ostream& os) const;

    AVLTree(const AVLTree& other);

    void copyConstructorHelper(const AVLTree &other ,AVLNode *node, AVLNode *&newTreeNode);

    void operator=(const AVLTree& other);

    void assignmentOperatorHelper(const AVLTree& other, AVLNode *node, AVLNode *&newTreeNode);

    void updateDepths(AVLNode *&node, int count) {
        if (node == nullptr) {
            return;
        }

        node->depth = count;
        updateDepths(node->left, count + 1);
        updateDepths(node->right, count + 1);

    }

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
        if (node->balance > 1) {
            this->rightRotate(node);
        }
        if (node->balance < -1) {
            this->leftRotate(node);
        }
        checkBalnces(node->right);
    }

    void rightRotate(AVLNode*& problemNode) {

    }

    void leftRotate(AVLNode*& problemNode) {

    }

};



#endif //AVLTREE_H