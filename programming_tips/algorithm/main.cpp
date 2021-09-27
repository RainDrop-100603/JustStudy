#include <iostream>

#include "useful.h"

using namespace std;

int main() {
    string str1("mississipi");
    auto result = useful_getSuffixArr(str1);
    for (auto& ele : result) {
        cout << ele << " ";
    }

    return 0;
}