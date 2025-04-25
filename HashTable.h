/**
 * HashTable.h
 * CS 3100/5100
 *
 * You should not modify any of the code you are given in this file, however
 * you will need to add a few things per the assignment instructions
 */



#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <functional>
#include <optional>
#include <ostream>
#include <set>
#include <string>
#include <vector>
template <typename T>
class LinkedListNode {
public:
    T key;
    LinkedListNode* next;

    explicit LinkedListNode(T k) {
        key = k;
        next = nullptr;
    }
};




/// enum BucketType
/// NORMAL: bucket is currently occipied with a valid key/value
/// ESS: bucket has empty since start (has never had a key/value)
/// EAR: bucket is empty after removal (aka tombstone, bucket used to hold
/// a key/value but they have been removed from the table)

/// all members of HashTableBucket are public to make it easy
/// methods are defined in HashTable.cpp,
/// they are already written for you
///
/// I modifies the HashTableBucket class a little to fit my solution for chaining
/// instead of a bucket holding a value and a key it holds a linked list each node has a value and a key
template <typename T>
class HashTableBucket {
public:
    LinkedListNode<T>* head{};
    LinkedListNode<T>* tail{};
    int size = 0;

    /// empty constructor
/// initializes the value to zero (not really necessary)
/// and sets the bucket type to empty since start
HashTableBucket(){
    head = nullptr;
    tail = nullptr;
}

void clear() {
    destructoHelper(head);
}


void destructoHelper(const LinkedListNode<T> *node) {
    if (node == nullptr) {
        return;
    }
    if (node == tail) {
        delete node;
        return;
    }
    LinkedListNode<T>* next = node->next;
    destructoHelper(next);
    delete node;

}



/// listInsert(string k, int v)
/// inserts a key vaulue pair as a linked list node into a bucket list
/// @param k the key
/// @param v the value
void listInsert(T k) {
    LinkedListNode<T>* newNode = new LinkedListNode(k);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        size++;
    }
    else {
        tail->next = newNode;
        tail = newNode;
        size++;
    }
}
/// search(string k)
/// searches to sey if a key is in a buckets list
/// @param k the key to search for
/// @return true if the key was found false if it was not
bool search(T k) const {
   LinkedListNode<T>* current = head;
    while (current != nullptr) {
        if (current->key == k) {
            return true;
        }
        current = current->next;
    }
    return false;
}

///deleteNode(k)
///finds and deletes a node in a buckets list associated with a key
///@param k the key
///@return returns true if the node with the key was found and removed returns false otherwise
bool deleteNode(T k) {
    LinkedListNode<T>* current = head;
    LinkedListNode<T>* previous = nullptr;
    while (current != nullptr) {
        if (current->key == k) {
            if (previous == nullptr) {
                head = current->next;
                tail = current;
                return true;
            }
            previous->next = current->next;
            delete current;
            size--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;

}

///listSize()
///gets the size of a buckets list
///@return returns the size of the list
int listSize() const {
    return size;
}



std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    LinkedListNode<T>* current = bucket.head;
    while (current != nullptr) {
        os << "<" << current->key << "> ";
        current = current->next;
    }
    return os;
}

};

/// operator<<(ostream, HashTableBucket)
/// overload of << for outputting bucket to stream
/// @param os the ostream to output to
/// @param bucket the bucket being output
/// @return reference to the ostream


template <typename T>
class HashTable {
private:

    // TODO: after you decide if you are doing chaining or a probing method
    // you will need to declare any member variables for your hash table
    // you may also want a method for your chosen probe function


    // you may want a private method to resize your table
    void resizeTable(const double resizeFactor = 2.0) {
        const int newCapacity = static_cast<int>(resizeFactor) * capacity();
        std::vector<T> keys;
        for (int i = 0; i < std:: size(buckets); i++) {
            if (buckets[i].head != nullptr) {
                LinkedListNode<T>* current = buckets[i].head;
                while (current != nullptr) {
                    keys.push_back(current->key);
                    current = current->next;
                }
            }
        }
        buckets.clear();
        for (int i = 0; i < newCapacity; i++) {
            buckets.emplace_back();
        }
        for (int i = 0; i < std:: size(keys); i++) {
            int h = hash(keys[i], buckets.size());
            buckets[h].listInsert(keys[i]);
        }
    }

    // you can eventually remove this if you want, it is
    // temporarily here so operator[] will "work"
    int placeholder;
public:
    // don't change this, this is required for the assignment
    static constexpr size_t DEFAULT_INITIAL_CAPACITY = 8;


    HashTable(size_t initCapacity = DEFAULT_INITIAL_CAPACITY) {
        for (int i = 0; i < initCapacity; i++) {
            HashTableBucket bucket = HashTableBucket<T>();
            buckets.push_back(bucket);
        }
    }

    std::vector<HashTableBucket<T>> buckets;

    void clear() {
        for (auto bucket : buckets) {
            bucket.clear();
        }
    }

    //this is a method to give a bucket to put a key and vaulue to
    static int hash(T k, int size) {
        if (typeid(k) == typeid(int) || typeid(k) == typeid(double) || typeid(k) == typeid(float) || typeid(k) == typeid(size_t)) {
            int i = k;
            return abs(i % size);
        }
        if (typeid(k) == typeid(std::string)) {
            std::string s = std::to_string(k);
            try {
                return abs(stoi(s) %size);
            }catch (const std::invalid_argument &e) {
                return s.length()%size;
            }

        }
        if (typeid(k) == typeid(bool)) {
            bool b = k;
            if (b == true) {
                return 1%size;
            }else {
                return 0;
            }
        }
        if (typeid(k) == typeid(char)) {
            return static_cast<int>(k)%size;
        }
    }

    bool insert(T key) {
        //the time complexity for this method would be O(n) if table is not being resized
        //because the function is calling .search() to check if the key is not in the table
        //.search() is not constant time because it is using a for loop to find the node making it O(n)
        //even though .listInsert is O(1)
        int h = hash(key, buckets.size());
        if (buckets[h].listSize() == 3) {
            resizeTable();
        }

        buckets[h].listInsert(key);
        return true;
    }

    bool remove(T key) {
        // This function is O(n)
        // because the function .deleteNode() is called which iterates over a buckets list of size n
        // making deleteNode() O(n)
        // therefore remove is O(n)
        int h = hash(key, buckets.size());
        return buckets[h].deleteNode(key);
    }

    std::vector<T> remove(size_t num) {
        std::vector<std::string> v;
        if (num > size()) {
            return v;
        }
        int count = 0;
        int index = 0;
        LinkedListNode<T>* current = nullptr;
        while (count < num) {
            if (buckets[index].head == nullptr) {
                index++;
            }
            current = buckets[index].head;
            if (current != nullptr) {
                v.push_back(current->key);
                buckets[index].deleteNode(current->key);
                count++;
            }
        }
        return v;
    }

    bool contains(const std::string& key) const {
        //the time complexity for this function is O(n)
        //because .search() is called to find the key which is O(n) because it has to iterate a buckets linked list of size n
        //making contains O(n)
        int h = hash(key, buckets.size());
        return buckets[h].search(key);
    }

    std::vector<std::string> keys() const {
        std::vector<T> keys;
        for (const auto & bucket : buckets) {
            if (bucket.head != nullptr) {
                LinkedListNode<T>* current = bucket.head;
                while (current != nullptr) {
                    keys.push_back(current->key);
                    current = current->next;
                }
            }
        }
        return keys;
    }

    std::set<std::string> uniqueKeys() const {
        std::set<T> keys;
        for (const auto & bucket : buckets) {
            if (bucket.head != nullptr) {
                LinkedListNode<T>* current = bucket.head;
                while (current != nullptr) {
                    keys.insert(current->key);
                    current = current->next;
                }
            }
        }
        return keys;
    }

    size_t capacity() const {
        return std::size(buckets);
    }

    size_t size() const {
        int count = 0;
        for (int i = 0; i < std:: size(buckets); i++) {
            if (buckets[i].head != nullptr) {
                count += buckets[i].size;
            }
        }
        return count;
    }

    int count(const std::string& key) const {
        int count = 0;
        for (int i = 0; i < std:: size(buckets); i++) {
            if (buckets[i].head != nullptr) {
                LinkedListNode<T>* current = buckets[i].head;
                while (current != nullptr) {
                    if (current->key == key) {
                        count++;
                    }
                    current = current->next;
                }
            }
        }
        return count;
    }

    std::ostream& operator<<(std::ostream& os, const HashTable& hashTable) {
        for (int i = 0; i < hashTable.capacity() ; i++) {
            os << hashTable.buckets[i] << std::endl;
        }
        return os;
    }
};



#endif //HASHTABLE_H