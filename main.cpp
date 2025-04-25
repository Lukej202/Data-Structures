#include <iostream>

#include "MultiSet.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    MultiSet<char> myset;
    myset.insert('a');
    myset.insert('b');
    myset.insert('c');
    myset.insert('d');
    myset.insert('e');
    myset.insert('f');
    myset.insert('g');

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.