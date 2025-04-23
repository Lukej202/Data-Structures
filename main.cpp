#include <iostream>
#include "MultiSet.h"

using namespace std;
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    MultiSet myset;
    myset.insert("1");
    myset.insert("1");
    myset.insert("2");
    myset.insert("3");
    myset.insert("4");

    MultiSet myset2;
    myset2.insert("1");
    myset2.insert("1");
    myset2.insert("1");
    myset2.insert("2");
    myset2.insert("2");
    myset2.insert("4");
    myset2.insert("9");


    MultiSet myset3 = myset.intersectionWith(myset2);
    std::vector<std::string> vector = myset3.keys();

    for (std::string s : vector) {
        cout << s << endl;
    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.