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
                elements.remove(key);
        }
}

std::vector<std::string> MultiSet::remove(size_t num) {
        return elements.remove(num);
}

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
        elements.clear();
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


MultiSet& MultiSet::operator=(const MultiSet &other) {
        clear();
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

MultiSet MultiSet::intersectionWith(const MultiSet &other) const {
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

MultiSet MultiSet::differenceWith(const MultiSet &other) const {
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

MultiSet MultiSet::symmetricDifferenceWith(const MultiSet &other) const {
        MultiSet setOne = differenceWith(other);
        MultiSet setTwo = other.differenceWith(*this);
        MultiSet result = setOne.unionWith(setTwo);
        return result;
}

std::ostream &operator<<(std::ostream &os, const MultiSet &set) {
        os << set.elements;
        return os;
}









