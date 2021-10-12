#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

/*
    tree: 원하는 값을 원하는 위치(idx)에 넣을 수 있는 tree
    목적
        원하는 위치에 value를 넣으면, 나머지 값들은 자동으로 뒤로 밀리는 tree
    기능
        setTree: 특정 size의 balancetree를 만든다, idx번째 node의 값은 idx
        kthNode: kth idx node의 값을 반환
        moveNode(from, to): remove 와 insert를 통해 구현
        removeNode(idx): idx번째 node를 삭제
        insertNode(value, idx): idx번째 위치에 value insert
        pushNode(value): 가장 마지막 위치에 value insert
    필요조건
        serarch가 lgN이내에 이루어지기 위해서, tree의 크기는 평균적으로 lgN이어야한다.
    문제
        algospot INSERTION 문제를 풀 수 있다.
        todo - list와 같은것을 사용할 때, 전체크기N 이 크면 유용할 수 있다.
*/

class Sequence_node {
   public:
    int key, size;
    Sequence_node *left, *right;
    Sequence_node(int _key) : key(_key), size(1), left(NULL), right(NULL) {}
    void setLeft(Sequence_node* node) {
        left = node;
        calcSize();
    }
    void setRight(Sequence_node* node) {
        right = node;
        calcSize();
    }
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};
class Sequence_tree {
    Sequence_node* root;
    Sequence_node* makeBalanceTree(int size, int now) {
        if (now >= size) {
            return NULL;
        }
        auto node = new Sequence_node(now);
        node->setLeft(makeBalanceTree(size, now * 2 + 1));
        node->setRight(makeBalanceTree(size, now * 2 + 2));
        return node;
    }
    void setBalanceTree() {
        for (int i = 0; i < root->size; i++) {
            find(i)->key = i;
        }
    }
    Sequence_node* find(int idx) {
        auto node = root;
        while (true) {
            int nodeIdx = node->left->size;
            if (idx == nodeIdx) {
                return node;
            } else if (idx < nodeIdx) {
                node = node->left;
            } else {
                node = node->right;
                idx -= nodeIdx;
            }
        }
    }
    Sequence_node* findParent(int idx) {
        auto node = root;
        Sequence_node* parent = NULL;
        while (true) {
            int nodeIdx = node->left->size;
            if (idx == nodeIdx) {
                return parent;
            } else if (idx < nodeIdx) {
                parent = node;
                node = node->left;
            } else {
                parent = node;
                node = node->right;
                idx -= nodeIdx;
            }
        }
    }
    Sequence_node* remove(int idx) {
        auto parent = findParent(idx);
        if (parent == NULL) {
            root = merge(root->left, root->right);
        } else if (parent->left->key == idx) {
            auto child = parent->left;
            parent->setLeft(merge(child->left, child->right));
        } else {
            auto child = parent->right;
            parent->setRight(merge(child->left, child->right));
        }
    }
    Sequence_node* merge(Sequence_node* leftNode, Sequence_node* rightNode) {
        if (leftNode == NULL) return rightNode;
        if (rightNode == NULL) return leftNode;
        // root =
    }

   public:
    Sequence_tree() : root(NULL) {}
    void setTree(int size) {
        if (size > 0) {
            root = new Sequence_node(0);
            makeBalanceTree(size, 0);
            setBalanceTree();
        }
    }
    int kthNode(int idx) {
        if (root == NULL || root->size <= idx) return -1;
        return find(idx)->key;
    }
    void moveNode(int from, int to) {
        remove(from);
        // insert(to, from);
    }
};
