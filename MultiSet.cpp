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
//                 LinkedListNode* current = elements.buckets[i].head;
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
        elements.clear();
}






