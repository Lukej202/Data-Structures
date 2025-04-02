//
// Created by lukej on 3/14/2025.
//

#include "AVLTree.h"

///constructor for the AVLTree class
AVLTree::AVLTree() {
    root = nullptr;
}
///destructor for the AVLTree class calls a function that deletes
///every node in the tree recursively
AVLTree::~AVLTree() {
    this->destructorHelper(root);
}
///destructorHelper(const AVLNode *node)
///helper function for the destructor that
///recursively deletes all of the trees nodes using a preorder traversal
///@param *node the tree node to start with typically root
void AVLTree::destructorHelper(const AVLNode *node) {
    if (node != nullptr) {
        return;
    }

    destructorHelper(node->left);
    delete node;
    destructorHelper(node->right);
}


///iinsert(const string &key, int value)
///inserts a node into the tree by calling a helper function that does it recursively
///also increases the trees size and calls a function to update the
///heights of all ot the trees nodes
///@param key the nodes key
///@param value the nodes value
///@return returns a boolean true if the node was sucessfully inserted and false if not
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
///insertHelper(AVLNode *&current, AVLNode *insertNode)
///inserts helper function to recursively insert a node into the tree
///@param current the node to start at typically root
///@param insertNode the node to insert
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
///contains(const string &key)
///checks if the tree contains a node with a certain key
///calls a helper function to recursively check the tree
///@param key the nodes key
///@return returns true if the node is found and false if not
bool AVLTree::contains(const string &key) const {
    return containsHelper(root, key);
}

///containsHelper(AVLNode *node, const string& key)
///helper function for contains to recursively check for the node
///@param node the node to start the search at typically root
///@param key the key to search for
///@return returns true if the node is found and false if not
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
///get(const string &key)
///searches for a node with a certain key and gets the value
///calls a helper function to do this recursively
///@param key the key to search for
///@return returns an optional<int> or it returns the value associated with a key if found and returns nullopt if it is not found
optional<int> AVLTree::get(const string &key) const {
    return getHelper(root, key);
}

///getHelper(AVLNode *node, const string& key
///gets helper function finds the node recursively
///@param node the node to start the search at typically root
///@param key the key to search for
///@return returns true if the node is found and false if not
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
///remove(const string &key)
///removes a node from the tree
///calls a helper function to do it recursively
///@param key the key to remove
///@return returns true if the key is found and removed and false if not
bool AVLTree::remove(const string &key) {
    bool removed = removeHelper(root, key);
    return removed;
}
///removeHelper(AVLNode *&node, const string& key)
///removes helper function to remove the node recursively
///@param node the node to start the search at typically root
///@param key the key to search for
///@return returns true if the node is found and false if not
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
            int counter = 1;
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
///operator[](const string &key)
///[] overload function calls a helper function to do it recursively
///@param key the key to search for
///@return returns a reference to a nodes value
int &AVLTree::operator[](const string &key) {
    return overLoadOneHelper(key,root);
}
///overLoadOneHelper(const string &key, AVLNode *node)
///[] overload functions helper function this is the same as get but returns a reference to a nodes value
///@param key tbe key to search for
///@param node the node to start the search at typically root
///@return returns a reference to a nodes value
int &AVLTree::overLoadOneHelper(const string &key, AVLNode *node) {
    if (node == nullptr) {
        return node->value;
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
///findRange(string lowKey, string highKey)
///this function returns a vector of values associated with keys
///that are within a certain range of keys that are entered
///calls a helper function to do this recursively uses a custom visitor class
///@param lowKey the lower bound for the range
///@param highKey the upper bound for the range
///@return returns a vector of values
vector<int> AVLTree::findRange(string lowKey, string highKey) const {
    AVLNodeVectorVisit v;
    findRangeHelper(root, v, lowKey, highKey);

    return v.values;
}
///findRangeHelper(AVLNode *node, AVLNodeVisitor& visitor, string lowKey, string highKey)
///findRange's helper function to recursively find all of the values
///@param node the node to start the search typically root
///@param visitor a visitor object which has a vector with the values in it
///@param lowKey the lower bound for the range
///@param highKey the upper bound for the range
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
///keys()
///this function returns a vector of all the keys in the tree
///uses a custom visitor class to do this calls a helper function to do this recursively
///@return returns a vector of all the keys in the tree
vector<string> AVLTree::keys() const {
    AVLNodeVectorVisit v;
    keysHelper(root, v);

    return v.keys;
}
///keysHelper(AVLNode *node, AVLNodeVisitor& visitor)
///helper function for keys works the same as findRange but just finds all the keys
///@param node the node to start the search typically root
///@param visitor a visitor object which has a vector with the values in it
void AVLTree::keysHelper(AVLNode *node, AVLNodeVisitor& visitor) const {
    if (node == nullptr) {
        return;
    }

    keysHelper(node->left, visitor);
    visitor.visit(node);
    keysHelper(node->right, visitor);

}
///size()
///@return returns the size of the tree
size_t AVLTree::size() const {
    return treeSize;
}
///getHeight()
///@return returns the trees height
size_t AVLTree::getHeight() const {
    return treeHeight;
}
