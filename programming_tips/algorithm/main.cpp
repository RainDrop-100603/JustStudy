#include <iostream>

#include "treap.h"
#include "useful.h"

using namespace std;

int main() {
    treap tree;
    for (int i = 0; i < 10; i++) {
        tree.insert(i);
    }
    cout << tree.kthNode(9) << endl;
    cout << tree.kthNode(10) << endl;
    cout << tree.isExist(10) << endl;
    cout << tree.isExist(9) << endl;
    cout << tree.countLessThan(9) << endl;
    cout << tree.countLessThan(10) << endl;
    cout << tree.size() << endl;
    cout << tree.min() << endl;
    cout << tree.max() << endl;
    for (int i = 0; i < 10; i++) {
        tree.erase(i);
        cout << "erase: " << i << endl;
    }
    return 0;
}