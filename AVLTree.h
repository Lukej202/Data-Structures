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
    int height = 0;
    int depth;
    int balance ;
    int leftHeight = -1;
    int rightHeight = -1;
    AVLNode* parent;
    AVLNode *left;
    AVLNode *right;

    AVLNode(string k, int v) {
        key = k;
        value = v;
        height = -1;
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

    bool ReplaceChild(AVLNode* currentChild, AVLNode* newChild) {
        if (left == currentChild) {
            left = newChild;
            return true;
        }
        else if (right == currentChild) {
            right = newChild;
            return true;
        }

        // currentChild is not a child of this node
        return false;
    }

    void getBalance() {
        balance = leftHeight - rightHeight;
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

    void insertHelper(AVLNode *&current, AVLNode *insertNode);

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


    void rebalance(AVLNode *&node) {
        if (node == nullptr) {
            return;
        }
        if (node->balance < -2) {
            if (node->right != nullptr) {
                if (node->right->balance > 1) {
                    rightRotate(node->right);
                }
            }
            leftRotate(node);
        }
        if (node->balance > 2) {
            if (node->left != nullptr) {
                if (node->left->balance < -1) {
                    leftRotate(node->left);
                }
            }
            rightRotate(node);
        }
    }

    void rightRotate(AVLNode*& node) {
        AVLNode* parent = node->parent;
        AVLNode* leftChild;
        AVLNode* leftRightChild;
        if (node->left != nullptr) {
            leftChild = node->left;
        }else {
            leftChild = nullptr;
        }
        if (leftChild != nullptr && leftChild->right != nullptr) {
            leftRightChild = leftChild->right;
        }else {
            leftRightChild = nullptr;
        }


        node->left = leftRightChild;
        if (leftChild != nullptr) {
            leftChild->right = node;
        }

        if (parent) {
            parent->ReplaceChild(node, leftChild);
        }
        else {
            root = leftChild;
            root->parent = nullptr;
        }
    }

    void leftRotate(AVLNode*& node) {
        AVLNode* parent = node->parent;
        AVLNode* rightChild;
        AVLNode* rightLeftChild;
        if (node->right != nullptr) {
            rightChild = node->right;
        }else {
            rightChild = nullptr;
        }
        if (rightChild != nullptr && rightChild->left != nullptr) {
            rightLeftChild = rightChild->left;
        }else {
            rightLeftChild = nullptr;
        }


        node->right = rightLeftChild;
        if (rightChild != nullptr) {
            rightChild->left = node;
        }

        if (parent) {
            parent->ReplaceChild(node, rightChild);
        }
        else {
            root = rightChild;
            root->parent = nullptr;
        }
    }

};



#endif //AVLTREE_H