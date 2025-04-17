

/**
 * HashTable.h
 * CS 3100/5100
 */


#include "HashTable.h"

#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <utility>
#include <sstream>
#include <vector>

using namespace std;
// HashTable methods

/// The "default" constructor uses our default capacity
/// You can create a hashtable without passing any parameters
/// @param initCapacity
/// @param size the initial capacity of the hash table
HashTable::HashTable(size_t initCapacity) {

    for (int i = 0; i < initCapacity; i++) {
        HashTableBucket bucket = HashTableBucket();
        buckets.push_back(bucket);
    }
}

void HashTable::clear() {
    for (auto bucket : buckets) {
        LinkedListNode* current = bucket.head;
        while (current != nullptr) {
            LinkedListNode* next = current->next;
            delete current;
            current = next;
        }
        bucket.head = nullptr;
    }
}


/// hash(key, value)
/// hash function that takes the key if it can be conveted
/// to an integer it will and will have a different hashing algorithm
/// then if it were a regular string of character
/// @param k the key which is used to determine where in the table the value is stored
/// @param size the current size of capacity of the hash table
/// @ return an int which is what index in the hash table the key and value will go
int HashTable::hash(const std::string &k, const int size) {
        try {
            return abs(stoi(k) %size);
        }catch (const invalid_argument &e) {
            return k.length()%size;
        }

}


/// insert(key, value)
/// insert the key value pair into the table
/// @param key the key which is used to determine where in the table the value is stored
/// @param value the value assosiated with the given key
/// @return if key is in the table, or if the table is full, return false
/// otherwise return true
bool HashTable::insert(const string& key) {
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

    return false;
}

/// remove(key)
/// the key and value are "deleted" from the table
/// in actuality, the buckets are "killed" and marked as
/// EAR (tombstone)
/// @param key the key for the value to be removed
/// @return true if the key was found and removed, otherwise false
bool HashTable::remove(const string& key) {
    // This function is O(n)
    // because the function .deleteNode() is called which iterates over a buckets list of size n
    // making deleteNode() O(n)
    // therefore remove is O(n)
    int h = hash(key, buckets.size());
    return buckets[h].deleteNode(key);
}

/// contains(key)
/// determines whether the key is in the table or not
/// @param key the key to be searched for
/// @return true if given key is in the table, otherwise false
bool HashTable::contains(const string& key) const {
    //the time complexity for this function is O(n)
    //because .search() is called to find the key which is O(n) because it has to iterate a buckets linked list of size n
    //making contains O(n)
    int h = hash(key, buckets.size());
    return buckets[h].search(key);
}

/// get(key)
/// searches for the value associated with the given key
/// @param key the key to search for
/// @return the value associated with the key, if the key is not
/// in the table find returns nullopt
// optional<size_t> HashTable::get(const string& key) const {
//     //the time complexity for this function is O(n)
//     //its calling 2 separate functions .search() and .listGet()
//     //these are both O(n) which makes this function O(n) because they iterate over a buckets linked list of size n
//     //making get() O(n)
//     int h = hash(key, buckets.size());
//     if (buckets[h].search(key) == false) {
//         return nullopt;
//     }
//     return  buckets[h].listGet(key);
// }

/// operator[key]
/// return a reference to the value associated with the key
/// this allows statements like:
/// int value = hashTable[key];
/// and
/// hashTable[key] = value;
/// @param key the key associated with the value to search for
/// @return a reference to the value associated with the key
/// if the key is not in the table, the behavior is undefined
// int& HashTable::operator[](const string& key) {
//     // DO NOT return a local variable, you want to return the value
//     // stored in the slot with the key argument
//     // this return is just here so the code will compile correctly
//     // you will eventually replace this
//
//     //This function is O(n)
//     //because it is calling getRef() which is O(n) because it is iterating over a buckets linked list of size n
//     //making this function O(n)
//     int h = hash(key, buckets.size());
//
//     return buckets[h].getRef(key);
//
// }

/// keys()
/// get all the keys stored in the table
/// @return a vector of strings of all the keys
///  should all be just from NORMAL slots
vector<string> HashTable::keys() const {
    vector<string> keys;
    for (const auto & bucket : buckets) {
        if (bucket.head != nullptr) {
            LinkedListNode* current = bucket.head;
            while (current != nullptr) {
                keys.push_back(current->key);
                current = current->next;
            }
        }
    }
    return keys;
}

set<string> HashTable::uniqueKeys() const {
    set<string> keys;
    for (const auto & bucket : buckets) {
        if (bucket.head != nullptr) {
            LinkedListNode* current = bucket.head;
            while (current != nullptr) {
                keys.insert(current->key);
                current = current->next;
            }
        }
    }
    return keys;
}

/// alpha()
/// the load factor
/// number of elements / table capacity
/// @return the current alpha/load factor
double HashTable::alpha() const {
    double count = 0;
    for (int i = 0; i < std:: size(buckets); i++) {
        if (buckets[i].head != nullptr) {
            count += buckets[i].listSize();
        }
    }
    double alpha = count / std::size(buckets);
    return alpha;
}

/// capacity()
/// how many buckets the table can currently hold
/// @return the current capacity of the table
size_t HashTable::capacity() const {
    return std::size(buckets);
}

/// size()
/// how many key-value pairs are currently in the table
/// alternatively, how many buckets are NORMAL
/// @return number of elements currently in the table
size_t HashTable::size() const {
    int count = 0;
    for (int i = 0; i < std:: size(buckets); i++) {
        if (buckets[i].head != nullptr) {
                count += buckets[i].size;
            }
        }
    return count;
}

int HashTable::count(const std::string& key) const {
    int count = 0;
    for (int i = 0; i < std:: size(buckets); i++) {
        if (buckets[i].head != nullptr) {
            LinkedListNode* current = buckets[i].head;
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

/// resizeTable(factor)
/// precondition: table has elements
/// postcondition: table capacity increased to current capacity * resizeFactor
/// all the elements remain in the table, and will need to be re-hashed based on the new capacity
/// @param resizeFactor how much to resize the table by
void HashTable::resizeTable(double resizeFactor) {
    int newCapacity = (int)resizeFactor * capacity();
    vector<string> keys;
    for (int i = 0; i < std:: size(buckets); i++) {
        if (buckets[i].head != nullptr) {
            LinkedListNode* current = buckets[i].head;
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

/// makeShuffledVector is provided for you
/// @param N ths capacity of our hash table
/// make sure to pass the capacity and not capacity - 1
/// makeShuffledVector takes care of that for us
/// @return vector of length N - 1 that has values 1 to N - 1 shuffled
vector<size_t> HashTable::makeShuffledVector(size_t N) {
    vector<size_t> arrayShuffle(N - 1);

    iota(arrayShuffle.begin(), arrayShuffle.end(), 1);

    // obtain a time-based seed for the shuffle
    auto seed = static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count());
    // seed = 0; // for testing you can comment th is out so the shuffled array is always shuffled the same

    // vector will be shuffled in-place
    shuffle(arrayShuffle.begin(), arrayShuffle.end(), default_random_engine(seed));

    return arrayShuffle;
}

/// opeartor<<(ostream, HashTable)
/// overload of << to output to stream
/// Should only print normal (occupied) buckets
/// You should use the << overload for the bucket and index
/// So the bucket contents are output with the bucket's index
/// You can use it like:
/// os << pair{bucket, index};
/// @param os the ostream to output to
/// @param hashTable the hash table to print
/// @return reference to the ostream
ostream& operator<<(ostream& os, const HashTable& hashTable) {
    for (int i = 0; i < hashTable.capacity() ; i++) {
        os << "Bucket: " << i << " ";
        os << hashTable.buckets[i] << endl;
    }
    return os;
    }

/// I turned the hash table bucket class into a singly linked list to implement chaining
/******************************************************
 **************    HashTableBucket    *****************
 ******************************************************/
// you shouldn't need to change these, but read through
// and make sure you understand what each one does

/// empty constructor
/// initializes the value to zero (not really necessary)
/// and sets the bucket type to empty since start
HashTableBucket::HashTableBucket() : type(BucketType::ESS) {
    head = nullptr;
    tail = nullptr;
}

/// listInsert(string k, int v)
/// inserts a key vaulue pair as a linked list node into a bucket list
/// @param k the key
/// @param v the value
void HashTableBucket::listInsert(const std::string& k) {
    LinkedListNode* newNode = new LinkedListNode(k);
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
   LinkedListNode* current = head;
    while (current != nullptr) {
        if (current->key == k) {
            return true;
        }
        current = current->next;
    }
    return false;
}
///listGet(string k)
///finds and gets the value in a buckets list associated with a key
///@param k key
///@return if key is found the value for that key is returned if not return 0
// size_t HashTableBucket::listGet(const std::string &k) const {
//     LinkedListNode* temp = head;
//     while (temp != nullptr) {
//         if (temp->key == k) {
//             return temp->key;
//         }
//         temp = temp->next;
//     }
//     return 0;
// }

/// getRef(string k)
/// this function is identical to list get but returns a reference
/// to the value in a buckets linked list associated with a key
///  this is so the operator[] function works
// size_t &HashTableBucket::getRef(const std::string &k) const {
//     LinkedListNode* temp = head;
//     if (this->search(k) == true) {
//         while (temp != nullptr) {
//             if (temp->key == k) {
//                 return temp->value;
//             }
//             temp = temp->next;
//         }
//     }
//         size_t i = 0;
//         size_t* j = &i;
//         cout << "Error: Key " << k << " does not exist in HashTable" << endl;
//         return *j;
// }


///deleteNode(k)
///finds and deletes a node in a buckets list associated with a key
///@param k the key
///@return returns true if the node with the key was found and removed returns false otherwise
bool HashTableBucket::deleteNode(const std::string& k) {
    LinkedListNode* current = head;
    LinkedListNode* previous = nullptr;
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


/// format the bucket's contents to a string
/// along with the given index
/// if bucket is empty, the string does not
/// have the key and value
/// @param index the index of the bucket in the table
/// @return a string with the index, key and value
string HashTableBucket::toString(const size_t index) const {
    stringstream result;
    if (isEmpty()) {
        result << "[empty]";
    } else {
        result << "Bucket "<< index << ": ";
        LinkedListNode* current = head;
        while (current != nullptr) {
            result << "<" << current->key << ">";
            current = current->next;
        }
    }
    return result.str();
}


/// operator<<(ostream, HashTableBucket)
/// overload of << for outputting bucket to stream
/// @param os the ostream to output to
/// @param bucket the bucket being output
/// @return reference to the ostream
ostream& operator<<(ostream& os, const HashTableBucket& bucket) {
    LinkedListNode* current = bucket.head;
    while (current != nullptr) {
        os << "<" << current->key << "> ";
        current = current->next;
    }
    return os;
}

/// operator<<(ostream, pair<HashTableBucket, size_t>)
/// overload of << to output bucket to stream
/// second argument used to print the index of the bucket in the table
/// would be used like:
/// cout << pair{bucket, index};
/// @param os the ostream to output to
/// @param bucket a pair with the bucket and bucket's index
/// @return reference to the ostream
ostream& operator<<(ostream& os, pair<const HashTableBucket&,  size_t> bucket) {
    os << bucket.first.toString(bucket.second);
    return os;
}

// Linked List stuff for chaining
LinkedListNode::LinkedListNode(const std::string &k) {
    this->key = k;
    next = nullptr;
}
