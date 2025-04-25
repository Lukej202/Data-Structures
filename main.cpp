#include <iostream>

#include "MultiSet.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    MultiSet<char> myset;
    myset.insert('a');
    myset.insert('b');
    myset.insert('b');
    myset.insert('c');
    myset.insert('d');

    MultiSet<char> myset2;
    myset2.insert('a');
    myset2.insert('b');
    myset2.insert('e');
    myset2.insert('y');

    std::cout << myset << std::endl;
    std::cout << myset2 << std::endl;

    MultiSet<char> myset3 = myset.symmetricDifferenceWith(myset2);
    std::cout << myset3 << std::endl;
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.