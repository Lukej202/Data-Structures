//
// Created by lukej on 3/14/2025.
//

#include "AVLTree.h"


AVLTree::AVLTree() {
    root = nullptr;
}

bool AVLTree::insert(const string &key, int value) {
    AVLNode* newNode = new AVLNode(key, value, 0);
    if (root == nullptr) {
        root = newNode;
        return true;
    }
    insertHelper(root, newNode);
    return true;
}

void AVLTree::insertHelper(AVLNode *current, AVLNode *insertNode) {
    if (insertNode->key < current->key) {
        if (current->left == nullptr) {
            current->left = insertNode;
            return;
        }
    } else if (insertNode->key > current->key) {
        if (current->right == nullptr) {
            current->right = insertNode;
            return;
        }
    }
    if (insertNode->key < current->key) {
        insertHelper(current->left, insertNode);
    }
    if (insertNode->key > current->key) {
        insertHelper(current->right, insertNode);
    }
}

bool AVLTree::contains(string &key) const {
    return containsHelper(root, key);
}

bool AVLTree::containsHelper(const AVLNode *node, string& key) const {
    if (node == nullptr) {
        return false;
    }
    if (node->key == key) {
        return true;
    }
    if (key < node->key) {
        containsHelper(node->left, key);
    }
    if (key > node->key) {
        containsHelper(node->right, key);
    }
}




