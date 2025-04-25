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
#include <set>
#include <string>
#include <vector>
template <typename T>
class LinkedListNode<T> {
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
enum class BucketType { NORMAL, ESS, EAR };

std::ostream operator<<(const std::ostream & os, char * str);

/// all members of HashTableBucket are public to make it easy
/// methods are defined in HashTable.cpp,
/// they are already written for you
///
/// I modifies the HashTableBucket class a little to fit my solution for chaining
/// instead of a bucket holding a value and a key it holds a linked list each node has a value and a key
template <typename T>
class HashTableBucket {
public:
    BucketType type;
    LinkedListNode<T>* head{};
    LinkedListNode<T>* tail{};
    int size = 0;

    /// empty constructor
/// initializes the value to zero (not really necessary)
/// and sets the bucket type to empty since start
HashTableBucket::HashTableBucket() : type(BucketType::ESS) {
    head = nullptr;
    tail = nullptr;
}

void HashTableBucket::clear() {
    destructoHelper(head);
}


void HashTableBucket::destructoHelper(const LinkedListNode<T> *node) {
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
void HashTableBucket::listInsert(const std::string& k) {
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
bool HashTableBucket::search(const std::string& k) const {
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
bool HashTableBucket::deleteNode(const std::string& k) {
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
int HashTableBucket::listSize() const {
    return size;
}


/// load(key, value)
/// update the key and value stored in the bucket
/// bucket is marked as normal to denote it is occupied
/// @param k new key
/// @param v new value
void HashTableBucket::load() {

    type = BucketType::NORMAL;
}

/// kill()
/// clear the key and value, and mark the slot as EAR (tombstone)
///
/// this will run if there is only one item in the linkelist
void HashTableBucket::kill() {

    type = BucketType::EAR;
}


/// getType()
/// get the current type of the bucket
/// @return the bucket's type (NORMAL, ESS, EAR)
BucketType HashTableBucket::getType() const {
    return type;
}

/// isEmpty()
/// determines if bucket is empty either since start or after remove
/// @return true if bucket is ESS or EAR, otherwise false
bool HashTableBucket::isEmpty() const {
    return type == BucketType::EAR || type == BucketType::ESS;
}

/// isNormal()
/// determines if bucket is normal/occupied
/// @return true if bucket is NORMAL, otherwise false
bool HashTableBucket::isNormal() const {
    return type == BucketType::NORMAL;
}

/// isEmptySinceStart()
/// determines only if bucket is ESS
/// @return true is the bucket is ESS, otherwise false
bool HashTableBucket::isEmptySinceStart() const {
    return type == BucketType::ESS;
}

/// isEmptyAfterRemoval()
/// determines only if bucket is EAR
/// @return true if bucket is EAR, otherwise false
bool HashTableBucket::isEmptyAfterRemoval() const {
    return type == BucketType::EAR;
}



/// operator<<(ostream, HashTableBucket)
/// overload of << for outputting bucket to stream
/// @param os the ostream to output to
/// @param bucket the bucket being output
/// @return reference to the ostream
    std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    LinkedListNode<T>* current = bucket.head;
    while (current != nullptr) {
        os << "<" << current->key << "> ";
        current = current->next;
    }
    return os;
}
};

// overloads for operator<< to print buckets using cout

template <typename T>
class HashTable {
private:

    // TODO: after you decide if you are doing chaining or a probing method
    // you will need to declare any member variables for your hash table
    // you may also want a method for your chosen probe function


    // if using pseudo-random probing, you will need an offsets array
    // I'm also providing a method to make the shuffled vector
    // and a method to generate an offsets array
    // std::vector<size_t> m_offsets;
    static std::vector<size_t> makeShuffledVector(size_t N);

    // you may want a private method to resize your table
    void resizeTable(double resizeFactor = 2.0);

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

    bool remove(const std::string& key);

    std::vector<std::string> remove(size_t num);

    std::optional<size_t> get(const std::string& key) const;

    bool contains(const std::string& key) const;

    // size_t& operator[](const std::string& key);

    std::vector<std::string> keys() const;

    std::set<std::string> uniqueKeys() const;

    double alpha() const;

    size_t capacity() const;

    size_t size() const;

    int count(const std::string& key) const;
};

std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);

#endif //HASHTABLE_H