#ifndef __FENWICKTREE_H__
#define __FENWICKTREE_H__

#include <iostream>
#include <vector>

using namespace std;

class fenwickTree {
    vector<int> tree;
    void add(int pos, int value) {
        pos++;  // 1부터 시작하도록
        while (pos < tree.size()) {
            tree[pos] += value;
            pos += (pos & -pos);  // pos += pos' last bit, -pos == ~pos + 1
        }
    }

   public:
    fenwickTree() {}
    void init(vector<int>& arr) {
        tree.resize(arr.size() + 1);
        for (int i = 0; i < arr.size(); i++) {
            add(i, arr[i]);
        }
    }
    void push_back(int var) {
        int pos = tree.size() - 1;
        tree.push_back(0);  // var이 들어갈 자리 생성
        add(pos, var);
    }
    int pSum(int pos) {
        // if pos<0, return 0;
        pos++;  // 1부터 시작하도록
        int result = 0;
        while (pos > 0) {
            result += tree[pos];
            pos -= (pos & -pos);  // remove pos' last bit
        }
        return result;
    }
};

void test_fenwickTree() {
    // base condition
    fenwickTree fenwick;
    vector<int> arr;
    int range = 100;
    for (int i = 0; i < range; i++) {
        arr.push_back(i);
    }
    fenwick.init(arr);
    // check 1
    bool chk1(true);
    for (int i = 0; i < range; i++) {
        if (fenwick.pSum(i) - fenwick.pSum(i - 1) != i) {
            chk1 = false;
            break;
        }
    }
    cout << (chk1 ? "chk1 valid\n" : "chk1 invalid\n");
    // check 2
    bool chk2(true);
    for (int i = 0; i < range; i++) {
        int pSum = i * (i + 1) / 2;
        if (fenwick.pSum(i) != pSum) {
            chk2 = false;
            break;
        }
    }
    cout << (chk2 ? "chk2 valid\n" : "chk2 invalid\n");
}

#endif