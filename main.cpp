#include "HashTable.h"

#include <iostream>

using namespace std;


int main() {
    HashTable ht;
    ht.insert("Luke", 26);
    ht.insert("Bob", 22);
    ht.insert("Rob", 27);
    ht.remove("Bob");
    return 0;
}