#include "HashTable.h"

#include <iostream>

using namespace std;


int main() {
    HashTable ht;
    ht.insert("3", 26);
    ht.insert("22", 22);
    ht.insert("2", 27);
    ht.insert("8", 28);
    ht.insert("16", 29);
    ht.insert("24", 30);

    return 0;
}