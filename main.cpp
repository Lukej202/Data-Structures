#include <iostream>

#include "AVLTree.h"


using namespace std;
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    AVLTree tree;
    tree.insert("F", 76);
    tree.insert("C", 0);
    tree.insert("B", 3);
    tree.insert("Z", 0);
    tree.insert("A", 1);
    tree.insert("L", 2);
    tree.insert("G", 4);
    cout << tree;


    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.