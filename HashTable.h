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
#include <string>
#include <vector>
class LinkedListNode {
public:
    std::string key;
    int value;
    LinkedListNode* next;

    LinkedListNode(std::string k, int v);;
};
class bucketLinkedList {
public:
    LinkedListNode* head;
    LinkedListNode* tail;

    bucketLinkedList();

    ~bucketLinkedList();

    void insert(std::string k, int v);

    bool search(std::string k);

    int get(std::string k);

    bool deleteKey(std::string k);

    void Print();
};

/// enum BucketType
/// NORMAL: bucket is currently occipied with a valid key/value
/// ESS: bucket has empty since start (has never had a key/value)
/// EAR: bucket is empty after removal (aka tombstone, bucket used to hold
/// a key/value but they have been removed from the table)
enum class BucketType { NORMAL, ESS, EAR };

/// all members of HashTableBucket are public to make it easy
/// methods are defined in HashTable.cpp,
/// they are already written for you
///
/// I modifies the HashTableBucket class a little to fit my solution for chaining
/// instead of a bucket holding a value and a key it holds a linked list each node has a value and a key
class HashTableBucket {
public:
    bucketLinkedList bucketList;
    BucketType type;

    HashTableBucket();

    HashTableBucket(const std::string& k, int v);

    void load();

    void kill();

    bucketLinkedList getBucketList() const;

    BucketType getType() const;

    std::string toString() const;

    std::string toString(size_t index) const;

    bool isEmpty() const;

    bool isNormal() const;

    bool isEmptySinceStart() const;

    bool isEmptyAfterRemoval() const;
};

// overloads for operator<< to print buckets using cout
std::ostream& operator<<(std::ostream& os, const HashTableBucket& me);
std::ostream& operator<<(std::ostream& os,  std::pair<const HashTableBucket&,  size_t> bucket);

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
    HashTableBucket buckets[DEFAULT_INITIAL_CAPACITY];
    //this vector is mfor when the table needs to be resized
    std::vector<HashTableBucket> table;
    HashTable(size_t initCapacity = DEFAULT_INITIAL_CAPACITY);

    bool insert(const std::string& key, int value);

    bool remove(const std::string& key);

    std::optional<int> get(const std::string& key) const;

    bool contains(const std::string& key) const;

    int& operator[](const std::string& key);

    std::vector<std::string> keys() const;

    double alpha() const;

    size_t capacity() const;

    size_t size() const;
};

std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);

#endif //HASHTABLE_H