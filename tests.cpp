//
// Created by lukej on 2/27/2025.
//
#include <iostream>
#include <functional>
#include <string>

int main() {
    std::hash<std::string> hasher;
    std::cout  << hasher("Hello") << std::endl;
    return 0;
}
