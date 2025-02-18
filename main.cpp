#include "HashTable.h"

#include <iostream>

using namespace std;


int main() {
    hash<string> myHash;
    cout << myHash("hello") << endl;
    return 0;
}