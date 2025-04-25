
/**
 *  MultiSet.h
 *  Header file for MultiSet class
 *  These are the minimum methods you need to implement. You will also need
 *  to implement a chosen extension function as detailed in the assignment PDF.
 *  You can add to this file, but do not change any of the declarations
 */
#include <string>
#include <vector>
#include <map>

#include "HashTable.h"

template <typename T>
class MultiSet{
    // declare your elements container and any other private member data
public:
    // delete the one you are not using
    // keep this public
    HashTable<T> elements;
    // if using a custom container, delete both above and have Container be your data structure

    /**
     * Default constructor, initializes the set to be empty
     */
    MultiSet() = default;

    /**
     * Destructor, would only be required if you had pointers inside MultiSet
     * Otherwise, your Container or other member variables should be responsible
     * for freeing the memory they are using
     */
    // ~MultiSet();

    /**
     * Copy constructor, this MultiSet should be a deep-copy of other
     *
     * @param other the MultiSet to be copied
     */
    MultiSet(const MultiSet& other) {
        std::vector<HashTableBucket<T>> newBuckets;
        for (int i = 0; i < other.size(); ++i) {
            newBuckets.emplace_back();
        }
        for (int i = 0; i < other.size(); ++i) {
            LinkedListNode<T>* current = other.elements.buckets[i].head;
            while (current != nullptr) {
                newBuckets[i].listInsert(current->key);
            }
        }
    }

    /**
     * Assignment operator, the memory this MultiSet stores should be released (if necessary)
     * then the elements from the other MultiSet copied into this MultiSet
     * @param other the MultiSet to be copied
     * @return
     */
    MultiSet& operator=(const MultiSet& other) {
        clear();
        std::vector<HashTableBucket<T>> newBuckets;
        for (int i = 0; i < other.size(); ++i) {
            newBuckets.emplace_back();
        }
        for (int i = 0; i < other.size(); ++i) {
            LinkedListNode<T>* current = other.elements.buckets[i].head;
            while (current != nullptr) {
                newBuckets[i].listInsert(current->key);
            }
        }
    }

    /**
     * Insert the key into the multiset with an optional parameter
     * for how many of that key to insert
     *
     * @param key element to insert
     * @param num how many elements to insert, defaults to 1
     * @return true if element was insert, false if an error was encountered
     */
    bool insert(T key, size_t num = 1) {
        for (int i = 0; i < num; i++) {
            return elements.insert(key);
        }
    }

    /**
     * Remove the key from the multiset, with optional parameter for how
     * many duplicates to remove. If num > coumt(key), no keys are removed
     *
     * @param key key to be removed
     * @param num how many copies of key to remove
     * @return true if the key was removed, false if key is not in the set,
     * or there were not enough copies based on the number to remove
     */
    bool remove(T key, size_t num = 1) {
        if (num > elements.count(key)) {
            return false;
        }
        for (int i = 0; i < num; i++) {
            elements.remove(key);
        }
    }

    /**
     * Remove the given number of arbitrary elements from the multiset. If
     * num > size(), nothing is removed
     *
     * @param num how many elements to remove
     * @return the elements that were removed
     */
    std::vector<T> remove(size_t num = 1) {
        return elements.remove(num);
    }

    /**
     * Determins if they key is in the multiset at least once
     *
     * @param key element to find
     * @return true if key is in multiset, otherwise false
     */
    bool contains(T key) const {
        return elements.contains(key);
    }

    /**
     * Given an element, count determins how many times that element appears
     * in the multiset
     *
     * @param key element to find the count of
     * @return how many of the given element appear
     */
    size_t count(T key) const {
        return elements.count(key);
    }

    /**
     * Find all elements, including duplicates
     *
     * @return all elements with the vector size == size()
     */
    std::vector<T> keys() const {
        return elements.keys();
    }

    /**
     * Find all the unique keys
     *
     * @return each key with vector size == uniqueSize()
     */
    std::vector<T> uniqueKeys() const {
        std::set<T> keys = elements.uniqueKeys();

        std::vector<std::string> result;
        for (auto key : keys) {
            result.push_back(key);
        }
        return result;
    }

    /**
     * Determines if the multiset contains any elements
     *
     * @return true if there are any elements in the multiset,
     * othersize false
     */
    bool empty() {
        if (elements.size() == 0) {
            return true;
        }
        return false;
    }

    /**
     * Determines the total number of elements
     *
     * @return how many elements in total are currently in the multiset
     */
    size_t size() const {
        return elements.size();
    }

    /**
     * Determines the number of unique keys
     *
     * @return how many unique keys are currently in the multiset
     */
    size_t uniqueSize() const {
        std::set<T> keys = elements.uniqueKeys();
        return keys.size();
    }

    /**
     * Removes all elements from the multiset
     */
    void clear() {
        elements.clear();
    }

    /////////////////
    // Set Operations
    /////////////////

    /**
     * Returns the union of two multiset, containing all elements of each set
     *
     * @param other the set to find the union with
     * @return the union of the current set with the other one
     */
    MultiSet unionWith(const MultiSet& other) const {
        std::map<T, int> setOne;
        std::map<T, int> setTwo;
        std::vector<T> keys = this->keys();
        std::vector<T> otherKeys = other.keys();
        for (int i = 0; i < std::size(keys); ++i) {
            if (setOne.contains(keys[i])) {
                ++setOne.at(keys[i]);
            }else {
                setOne.emplace(keys[i], 1);
            }
        }
        for (int i = 0; i < std::size(otherKeys); ++i) {
            if (setTwo.contains(otherKeys[i])) {
                ++setTwo.at(otherKeys[i]);
            }
            else {
                setTwo.emplace(otherKeys[i], 1);
            }
        }
        MultiSet result;
        for (const auto &pair : setOne) {
            if (setTwo.contains(pair.first)) {
                if (setTwo.at(pair.first) <= pair.second) {
                    for (int i = 0; i < pair.second; ++i) {
                        result.elements.insert(pair.first);
                    }
                }
            }else {
                result.elements.insert(pair.first);
            }
        }
        for (const auto &pair : setTwo) {
            if (setOne.contains(pair.first)) {
                if (setOne.at(pair.first) < pair.second) {
                    for (int i = 0; i < pair.second; ++i) {
                        result.elements.insert(pair.first);
                    }
                }
            }else {
                result.elements.insert(pair.first);
            }
        }
        return result;
    }

    /**
     * Returns a multiset containing only elements common to both
     *
     * @param other the set to find the intersection with
     * @return multiset with elements only found in both this and the other
     */
    MultiSet intersectionWith(const MultiSet& other) const {
        std::map<T, int> setOne;
        std::map<T, int> setTwo;
        std::vector<T> keys = this->keys();
        std::vector<T> otherKeys = other.keys();
        for (int i = 0; i < std::size(keys); ++i) {
            if (setOne.contains(keys[i])) {
                ++setOne.at(keys[i]);
            }else {
                setOne.emplace(keys[i], 1);
            }
        }
        for (int i = 0; i < std::size(otherKeys); ++i) {
            if (setTwo.contains(otherKeys[i])) {
                ++setTwo.at(otherKeys[i]);
            }
            else {
                setTwo.emplace(otherKeys[i], 1);
            }
        }
        MultiSet result;
        for (const auto &pair : setOne) {
            if (setTwo.contains(pair.first)) {
                if (setTwo.at(pair.first) > pair.second) {
                    for (int i = 0; i < pair.second; ++i) {
                        result.elements.insert(pair.first);
                    }
                }else {
                    for (int i = 0; i < setTwo.at(pair.first); ++i) {
                        result.elements.insert(pair.first);
                    }
                }
            }
        }
        return result;
    }

    /**
     * Returns multiset containing all the elements in the current set that are
     * not in the other
     *
     * @param other the set to find the difference with
     * @return multiset with elements in the current set not found in the other
     */
    MultiSet differenceWith(const MultiSet& other) const {
        std::map<T, int> setOne;
        std::map<T, int> setTwo;
        std::vector<T> keys = this->keys();
        std::vector<T> otherKeys = other.keys();
        for (int i = 0; i < std::size(keys); ++i) {
            if (setOne.contains(keys[i])) {
                ++setOne.at(keys[i]);
            }else {
                setOne.emplace(keys[i], 1);
            }
        }
        for (int i = 0; i < std::size(otherKeys); ++i) {
            if (setTwo.contains(otherKeys[i])) {
                ++setTwo.at(otherKeys[i]);
            }
            else {
                setTwo.emplace(otherKeys[i], 1);
            }
        }
        MultiSet result;
        for (const auto &pair : setOne) {
            if (setTwo.contains(pair.first)) {
                if (setTwo.at(pair.first) < pair.second) {
                    for (int i = 0; i < pair.second - setTwo.at(pair.first); ++i) {
                        result.elements.insert(pair.first);
                    }
                }
            }else {
                for (int i = 0; i < pair.second; ++i) {
                    result.elements.insert(pair.first);
                }
            }
        }
        return result;
    }

    /**
     * Returns a multiset containing elements that are either in this or the
     * other multiset, but not in both
     *
     * @param other the set to find the symmetric differnce with
     * @return set containing elements unique to both this and other
     */
    MultiSet symmetricDifferenceWith(const MultiSet& other) const {
        MultiSet setOne = differenceWith(other);
        MultiSet setTwo = other.differenceWith(*this);
        MultiSet result = setOne.unionWith(setTwo);
        return result;
    }

    /**
     * Outputs a representation of the multiset
     * One possible approach could be to print the key and its count
     * eg: {a:2, b:3, c:1}
     * or, print each element
     * eg. {a, a, b, b, b, c}
     *
     * @param os the ostream to output to
     * @param ms the MultiSet to output
     * @return reference to os
     */
    friend std::ostream& operator<< (std::ostream& os, const MultiSet& ms) {
        os << ms.elements;
        return os;
    }
};
