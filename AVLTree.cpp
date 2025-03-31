//
// Created by lukej on 3/14/2025.
//

#include "AVLTree.h"


AVLTree::AVLTree() {
    root = nullptr;
}

bool AVLTree::insert(const string &key, int value) {
    if (this->contains(key) == true) {
        return false;
    }
    AVLNode* newNode = new AVLNode(key, value);
    if (root == nullptr) {
        root = newNode;
        treeSize++;
        treeHeight++;
        return true;
    }
    insertHelper(root, newNode);
    treeHeight = root->findHeight(root);
    this->updateBalances(root);



    treeSize++;
    return true;
}

void AVLTree::insertHelper(AVLNode *&current, AVLNode *insertNode) {
    if (current == nullptr) {
        current = insertNode;
        return;
    }
    if (insertNode->key < current->key) {
        insertHelper(current->left, insertNode);
    }
    if (insertNode->key > current->key) {
        insertHelper(current->right, insertNode);
    }
}

bool AVLTree::contains(const string &key) const {
    return containsHelper(root, key);
}

bool AVLTree::containsHelper(AVLNode *node, const string& key) const {
    if (node == nullptr) {
        return false;
    }
    if (key == node->key) {
        return true;
    }
    if (key < node->key) {
        return containsHelper(node->left, key);
    }
    if (key > node->key) {
        return containsHelper(node->right, key);
    }

}
optional<int> AVLTree::get(const string &key) const {
    return getHelper(root, key);
}

optional<int> AVLTree::getHelper(AVLNode *node, const string& key) const {
    if (node == nullptr) {
        return nullopt;
    }
    if (key == node->key) {
        return node->value;
    }
    if (key < node->key) {
        return getHelper(node->left, key);
    }
    if (key > node->key) {
        return getHelper(node->right, key);
    }
}

bool AVLTree::remove(const string &key) {
    bool removed = removeHelper(root, key);
    return removed;
}

bool AVLTree::removeHelper(AVLNode *&node, const string& key) {
    if (node == nullptr) {
        return false;
    }
    if (key == node->key) {
        if (node->left == nullptr && node->right == nullptr) {
            node = nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr) {
            node = node->left;
        }
        else if (node->left == nullptr && node->right != nullptr) {
            node = node->right;
        }
        else{
            AVLNode *parent = node;
            AVLNode *successor = node->right;
            int counter = 0;
            while (successor != nullptr) {
                if (successor->left == nullptr) {
                    node->key = successor->key;
                    node->value = successor->value;
                    if (counter == 1) {
                        parent->right = nullptr;
                    }else {
                        parent->left = nullptr;
                    }
                }
                counter++;
                parent = successor;
                successor = successor->left;
            }
        }
        treeSize--;
        return true;
    }
    if (key < node->key) {
        return removeHelper(node->left, key);
    }
    if (key > node->key) {
        return removeHelper(node->right, key);
    }
}

int &AVLTree::operator[](const string &key) {
    return overLoadOneHelper(key,root);
}

int &AVLTree::overLoadOneHelper(const string &key, AVLNode *node) {
    if (node == nullptr) {
        return root->value;
    }
    if (key == node->key) {
        return node->value;
    }
    if (key < node->key) {
        return overLoadOneHelper(key, node->left);
    }
    if (key > node->key) {
        return overLoadOneHelper(key, node->right);
    }
}

vector<int> AVLTree::findRange(string lowKey, string highKey) const {
    AVLNodeVectorVisit v;
    findRangeHelper(root, v, lowKey, highKey);

    return v.values;
}

void AVLTree::findRangeHelper(AVLNode *node, AVLNodeVisitor& visitor, string lowKey, string highKey) const {
    if (node == nullptr) {
        return;
    }

    findRangeHelper(node->left, visitor, lowKey, highKey);
    if (node->key >= lowKey && node->key <= highKey) {
        visitor.visit(node);
    }
    findRangeHelper(node->right, visitor, lowKey, highKey);
}



vector<string> AVLTree::keys() const {
    AVLNodeVectorVisit v;
    keysHelper(root, v);

    return v.keys;
}

void AVLTree::keysHelper(AVLNode *node, AVLNodeVisitor& visitor) const {
    if (node == nullptr) {
        return;
    }

    keysHelper(node->left, visitor);
    visitor.visit(node);
    keysHelper(node->right, visitor);

}

size_t AVLTree::size() const {
    return treeSize;
}

size_t AVLTree::getHeight() const {
    return treeHeight;
}
