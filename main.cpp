#include "HashTable.h"

#include <iostream>

using namespace std;


int main() {
    std::hash<std::string> stringHash;
    cout<<stringHash("hello")<<endl;
    return 0;
}