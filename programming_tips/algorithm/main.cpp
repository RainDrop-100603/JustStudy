#include <iostream>

#include "treap.h"
#include "useful.h"

using namespace std;

int main() {
    treap tree;
    for (int i = 0; i < 10; i++) {
        tree.insert(i);
    }
    tree.printTree();
    cout << tree.findKth(10) << endl;
    cout << tree.findKth(11) << endl;
    cout << tree.find(10) << endl;
    cout << tree.find(9) << endl;
    cout << tree.countLessThan(9) << endl;
    cout << tree.countLessThan(10) << endl;
    for (int i = 0; i < 10; i++) {
        tree.erase(i);
        cout << tree.size() << endl;
    }
    tree.printTree();
    return 0;
}