/**
 * HashTable.h
 * CS 3100/5100
 */


#include "HashTable.h"

#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <utility>
#include <sstream>
#include <vector>

using namespace std;
// HashTable methods

/// The "default" constructor uses our default capacity
/// You can create a hashtable without passing any parameters
/// @param size the initial capacity of the hash table
HashTable::HashTable(size_t initCapacity) {
    for (int i = 0; i < initCapacity; i++) {
        buckets[i] = HashTableBucket();
    }
}

/// insert(key, value)
/// insert the key value pair into the table
/// @param key the key which is used to determine where in the table the value is stored
/// @param value the value assosiated with the given key
/// @return if key is in the table, or if the table is full, return false
/// otherwise return true
bool HashTable::insert(const string& key, int value) {

    //if the buckets linked list was empty this sets the bucket type to normal
    if (buckets[key.length() % std::size(buckets)].getBucketList().head == nullptr) {
        buckets[key.length() % std::size(buckets)].load();
    }
    if (buckets[key.length() % std::size(buckets)].getBucketList().search(key) == false){
    buckets[key.length() % std::size(buckets)].getBucketList().insert(key, value);
        return true;
        }
    return false;
}

/// remove(key)
/// the key and value are "deleted" from the table
/// in actuality, the buckets are "killed" and marked as
/// EAR (tombstone)
/// @param key the key for the value to be removed
/// @return true if the key was found and removed, otherwise false
bool HashTable::remove(const string& key) {

    //sets the bucket to EAR if the Linked list in the bucket only has one item
    if (buckets[key.length() % std::size(buckets)].getBucketList().head->next == nullptr) {
        buckets[key.length() % std::size(buckets)].kill();
    }

    return buckets[key.length() % std::size(buckets)].getBucketList().deleteKey(key);
}

/// contains(key)
/// determines whether the key is in the table or not
/// @param key the key to be searched for
/// @return true if given key is in the table, otherwise false
bool HashTable::contains(const string& key) const {

    return buckets[key.length() % std::size(buckets)].getBucketList().search(key);
}

/// get(key)
/// searches for the value associated with the given key
/// @param key the key to search for
/// @return the value associated with the key, if the key is not
/// in the table find returns nullopt
optional<int> HashTable::get(const string& key) const {

    return  buckets[key.length() % std::size(buckets)].getBucketList().get(key);
}

/// operator[key]
/// return a reference to the value associated with the key
/// this allows statements like:
/// int value = hashTable[key];
/// and
/// hashTable[key] = value;
/// @param key the key associated with the value to search for
/// @return a reference to the value associated with the key
/// if the key is not in the table, the behavior is undefined
int& HashTable::operator[](const string& key) {
    // DO NOT return a local variable, you want to return the value
    // stored in the slot with the key argument
    // this return is just here so the code will compile correctly
    // you will eventually replace this

    int i = buckets[key.length() % std::size(buckets)].getBucketList().get(key);
    int* ptr = &i;
    return ptr[i];
}

/// keys()
/// get all the keys stored in the table
/// @return a vector of strings of all the keys
///  should all be just from NORMAL slots
vector<string> HashTable::keys() const {
    vector<string> keys;
    for (int i = 0; i < std:: size(buckets); i++) {
        if (buckets[i].getBucketList().head != nullptr) {
            LinkedListNode* current = buckets[i].getBucketList().head;
            while (current != nullptr) {
                keys.push_back(current->key);
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
    int count = 0;
    for (int i = 0; i < std:: size(buckets); i++) {
        if (buckets[i].getBucketList().head != nullptr) {
            LinkedListNode* current = buckets[i].getBucketList().head;
            while (current != nullptr) {
                count += 1;
                current = current->next;
            }
        }
    }
    int alpha = count / std:: size(buckets);
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
        if (buckets[i].getBucketList().head != nullptr) {
            LinkedListNode* current = buckets[i].getBucketList().head;
            while (current != nullptr) {
                count += 1;
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
    for (int i = 0; i < hashTable.size(); i++) {
        if (hashTable.buckets[i].getBucketList().head != nullptr) {
            
        }
    }
    return os;
    }

/******************************************************
 **************    HashTableBucket    *****************
 ******************************************************/
// you shouldn't need to change these, but read through
// and make sure you understand what each one does

/// empty constructor
/// initializes the value to zero (not really necessary)
/// and sets the bucket type to empty since start
HashTableBucket::HashTableBucket() : type(BucketType::ESS) {
}

/// parameterized constructor(key, value)
/// creates a new bucket with the given key and value
/// the bucket is marked as normal
/// @param k the lookup key for the bucket
/// @param v the value associated with the key
HashTableBucket::HashTableBucket(const string& k,
                                 int v) : type(BucketType::NORMAL){
    this->bucketList.insert(k, v);
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


bucketLinkedList HashTableBucket::getBucketList() const {
    return bucketList;
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

/// toString()
/// format the bucket's contents to a string
/// if bucket is empty, the string does not
/// have the key and value
/// @return a string with the key and value
/// if bucket is empty, string is: "[empty]"
string HashTableBucket::toString() const {
    return {};
}

/// format the bucket's contents to a string
/// along with the given index
/// if bucket is empty, the string does not
/// have the key and value
/// @param index the index of the bucket in the table
/// @return a string with the index, key and value
string HashTableBucket::toString(size_t index) const {
    stringstream result;
    if (isEmpty()) {
        result << "[empty]";
    } else {
        result << "Bucket "<< index << ": " << *this;
    }
    return result.str();
}

/// operator<<(ostream, HashTableBucket)
/// overload of << for outputting bucket to stream
/// @param os the ostream to output to
/// @param bucket the bucket being output
/// @return reference to the ostream
ostream& operator<<(ostream& os, const HashTableBucket& bucket) {
    os << bucket.toString();
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
LinkedListNode::LinkedListNode(std::string k, int v) {
    key = k;
    value = v;
    next = nullptr;
}

bucketLinkedList::bucketLinkedList() {
    head = nullptr;
    tail = nullptr;
}

void bucketLinkedList::insert(std::string k, int v) {
    LinkedListNode* newNode = new LinkedListNode(k, v);
    if (head == nullptr) {
       head = newNode;
        tail = newNode;
        delete newNode;
        return;
    }
    LinkedListNode* temp = head;
    while (temp != nullptr) {
        if (temp->next == nullptr) {
            temp->next = newNode;
            delete newNode;
            delete temp;
            return;
        }else {
            temp = temp->next;
        }
    }
}
 bool bucketLinkedList::search(std::string k) {
    LinkedListNode* temp = head;
    while (temp != nullptr) {
        if (temp->key == k) {
            return true;
        }
    }
    return false;
}

int bucketLinkedList::get(std::string k) {
    LinkedListNode* temp = head;
    while (temp != nullptr) {
        if (temp->key == k) {
            return temp->value;
        }
        temp = temp->next;
    }
    return 0;
}


bool bucketLinkedList::deleteKey(std::string k) {
    LinkedListNode* temp = head;
    while (temp != nullptr) {
        if (temp->next->key == k) {
            temp->next = temp->next->next;
            return true;
        }else {
            temp = temp->next;
        }
    }
    return false;
}

void bucketLinkedList::Print() {
    LinkedListNode* temp = head;
    while (temp != nullptr) {
        cout << "<" << temp->key << temp->value << ">" << endl;
        temp = temp->next;
    }
}

