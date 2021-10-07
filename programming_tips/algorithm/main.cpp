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

    return 0;
}