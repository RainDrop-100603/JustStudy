#ifndef __TREAP_H__
#define __TREAP_H__

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class treapNode {
   public:
    int key, priority, size;
    treapNode *left, *right;
    treapNode(int _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}
    //기본함수
    void setLeft(treapNode* leftNode) {
        left = leftNode;
        calcSize();
    }
    void setRight(treapNode* rightNode) {
        left = rightNode;
        calcSize();
    }
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
    int min() { return findKth(1)->key; }
    int max() { return findKth(size)->key; }
    // function that use this
    treapNode* insert(treapNode* input) {
        if (this == NULL) {
            return input;
        }
        // if input->key already exist
        if (find(input->key)) {
            return this;
        }
        // input->priority < priority
        if (input->priority < priority) {
            if (input->key < key) {
                setLeft(left->insert(input));
            } else {
                setRight(right->insert(input));
            }
            return this;
        }
        // input->priority > priority
        auto splitted = split(input->key);
        input->setLeft(splitted.first);
        input->setRight(splitted.second);
        return input;
    }
    pair<treapNode*, treapNode*> split(int value) {
        // divide subtree by value
        if (this == NULL) {
            return pair<treapNode*, treapNode*>{NULL, NULL};
        }
        if (value > key) {
            auto rightSplit = right->split(value);
            setRight(rightSplit.first);
            return pair<treapNode*, treapNode*>{this, rightSplit.second};
        } else {
            auto leftSplit = left->split(value);
            setLeft(leftSplit.second);
            return pair<treapNode*, treapNode*>{leftSplit.first, this};
        }
    }
    treapNode* erase(int key) {
        if (this == NULL) {
            cout << "There's no " << key << " in this Tree\n";
            return this;
        }
        if (key == key) {
            auto tmp = merge(left, right);
            delete this;
            return tmp;
        }
        if (key > key) {
            setRight(right->erase(key));
        } else {
            setLeft(left->erase(key));
        }
        return this;
    }
    treapNode* find(int key) {
        auto node = this;
        while (node != NULL) {
            if (key == node->key) {
                return node;
            } else if (key > node->key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return NULL;
    }
    treapNode* findKth(int num) {
        int rootIdx = 1;
        if (left) rootIdx += left->size;
        if (num < rootIdx) {
            return left->findKth(num);
        } else if (num == rootIdx) {
            return this;
        } else {
            return right->findKth(num - rootIdx);
        }
    }
    int countLessThan(int key) {
        int result = 0;
        auto node = this;
        while (node != NULL) {
            int leftSize = node->left ? node->left->size : 0;
            if (key == node->key) {
                result += leftSize;
                return result;
            } else if (key > node->key) {
                result += leftSize + 1;
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return -1;  // there's no key in the root-subtree
    }
    // function do not use this
    treapNode* merge(treapNode* leftNode, treapNode* rightNode) {
        // 기저
        if (leftNode == NULL) return rightNode;
        if (rightNode == NULL) return leftNode;
        // left node is smaller than right node
        if (leftNode->key > rightNode->key) return merge(rightNode, leftNode);
        // should be left.max < right.min
        if (leftNode->max() >= rightNode->min()) {
            cout << "subtree(root=" << leftNode->key << ") and subtree(root=" << rightNode->key << ") cant be merged, cause leftSubtree.max >= rightSubtree.min\n";
        }
        // 연산
        if (leftNode->priority > rightNode->priority) {
            leftNode->setRight(merge(leftNode->right, rightNode));
            return leftNode;
        } else {
            rightNode->setLeft(merge(leftNode, rightNode->left));
            return rightNode;
        }
    }
};

class treap {
    treapNode* root;
    void clean(treapNode* _root) {
        if (_root) {
            auto left = _root->left;
            auto right = _root->right;
            delete _root;
            if (left) clean(left);
            if (right) clean(right);
        }
    }

   public:
    treap() : root(NULL) {}
    ~treap() { clean(root); }
    treap& insert(int key) {
        treapNode* node = new treapNode(key);
        root->insert(node);
    }
    treap& erase(int key) { root->erase(key); }
    bool find(int key) { return root->find(key); }
    int findKth(int num) { return root->findKth(num); }
    int countLessThan(int key) { return root->countLessThan(key); }
};

#endif