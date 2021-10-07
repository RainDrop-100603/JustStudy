#include <iostream>

#include "treap.h"
#include "useful.h"

using namespace std;

int main() {
    treapNode root(10);
    for (int i = 0; i < 10; i++) {
        root.insert(&treapNode(i));
    }

    return 0;
}