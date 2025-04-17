//
// Created by lukej on 4/15/2025.
//

#include "MultiSet.h"

MultiSet::MultiSet() = default;


bool MultiSet::insert(const std::string &key, size_t num) {
        for (int i = 0; i < num; i++) {
                return elements.insert(key);
        }
}

bool MultiSet::remove(const std::string &key, size_t num) {
        for (int i = 0; i < num; i++) {
                return elements.remove(key);
        }
}

// std::vector<std::string> MultiSet::remove(size_t num) {
//         std::vector<std::string> elements;
//         for (int i = 0; i < num; i++) {
//                 LinkedListNode* current;
//                 current = elements.buckets[i];
//         }
// }

std::vector<std::string> MultiSet::keys() const {
        return elements.keys();
}

std::vector<std::string> MultiSet::uniqueKeys() const {
        std::set<std::string> keys = elements.uniqueKeys();

        std::vector<std::string> result;
        for (auto key : keys) {
                result.push_back(key);
        }
        return result;
}


bool MultiSet::contains(const std::string &key) const {
        return elements.contains(key);
}

bool MultiSet:: empty(){
        if (elements.size() == 0) {
                return true;
        }
        return false;
}

size_t MultiSet::size() const {
        return elements.size();
}

size_t MultiSet::uniqueSize() const {
        std::set<std::string> keys = elements.uniqueKeys();
        return keys.size();
}


void MultiSet::clear() {

}

size_t MultiSet::count(const std::string &key) const {
        return elements.count(key);
}

MultiSet::MultiSet(const MultiSet &other) {
        std::vector<HashTableBucket> newBuckets;
        for (int i = 0; i < other.size(); ++i) {
                newBuckets.emplace_back();
        }
        for (int i = 0; i < other.size(); ++i) {
                LinkedListNode* current = other.elements.buckets[i].head;
                while (current != nullptr) {
                        newBuckets[i].listInsert(current->key);
                }
        }
}


// MultiSet& MultiSet::operator=(const MultiSet &other) {
//
// }

/////////////////
// Set Operations
/////////////////

MultiSet MultiSet::unionWith(const MultiSet &other) const {
        std::map<std::string, int> setOne;
        std::map<std::string, int> setTwo;
        std::vector<std::string> keys = this->keys();
        std::vector<std::string> otherKeys = other.keys();
        for (int i = 0; i < std::size(keys); ++i) {
                if (setOne.contains(keys[i])) {
                        setOne.at(keys[i])++;
                }else {
                       setOne.emplace(keys[i], 1);
                }
        }
        for (int i = 0; i < std::size(otherKeys); ++i) {
                if (setTwo.contains(otherKeys[i])) {
                        setTwo.at(otherKeys[i])++;
                }
                else {
                        setTwo.emplace(otherKeys[i], 1);
                }
        }
        MultiSet result;
        for (const auto &pair : setOne) {
                if (!setTwo.contains(pair.first)) {
                        result.elements.insert(pair.first);
                }
        }
}









