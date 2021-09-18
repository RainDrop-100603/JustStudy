#include <iostream>

#include "useful.h"

using namespace std;

int main() {
    string str1("aabaabaac"), str2("aab"), str3("aa");
    auto tmp1 = useful_getFailure(str1);
    auto tmp2 = useful_getFailure(str2);
    auto tmp3 = useful_getFailure(str3);
    auto tmp4 = useful_KmpSearch(str1, str1);
    auto tmp5 = useful_KmpSearch(str1, str2);
    auto tmp6 = useful_KmpSearch(str1, str3);
    for (auto& ele : tmp1) {
        cout << ele << " ";
    }
    cout << endl;
    for (auto& ele : tmp2) {
        cout << ele << " ";
    }
    cout << endl;
    for (auto& ele : tmp3) {
        cout << ele << " ";
    }
    cout << endl;
    for (auto& ele : tmp4) {
        cout << ele << " ";
    }
    cout << endl;
    for (auto& ele : tmp5) {
        cout << ele << " ";
    }
    cout << endl;
    for (auto& ele : tmp6) {
        cout << ele << " ";
    }
    cout << endl;
    return 0;
}