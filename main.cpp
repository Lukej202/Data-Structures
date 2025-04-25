#include <iostream>

#include "MultiSet.h"

using namespace std;
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    MultiSet myset;

    myset.insert("4");
    myset.insert("5");
    myset.insert("6");
    myset.insert("7");
    myset.insert("8");
    myset.insert("9");
    myset.insert("8");
    myset.insert("9");

    MultiSet myset2;
    myset2.insert("8");
    myset2.insert("9");
    myset2.insert("8");
    myset2.insert("9");
    myset2.insert("10");
    myset2.insert("11");

    cout << myset<< endl;

    cout << myset2<< endl;

    MultiSet myset3 = myset.symmetricDifferenceWith(myset2);
    cout << myset3<< endl;
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.