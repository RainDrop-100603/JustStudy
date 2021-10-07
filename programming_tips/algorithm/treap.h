#ifndef __TREAP_H__
#define __TREAP_H__

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct treapNode {
    // key의 중복이 없는 tree
    int key;
    int priority, size;
    treapNode *left, *right;
    //생성자
    treapNode(const int _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}
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
    // insert, erase, merge, split, find
    treapNode* insert(int key, treapNode* root) {
        treapNode input(key);
        return insert(&input, root);
    }
    treapNode* insert(treapNode* input, treapNode* root) {
        if (root == NULL) {
            return input;
        }
        // input->priority < root->priority
        if (input->priority < root->priority) {
            if (input->key < root->key) {
                root->setLeft(insert(input, root->left));
            } else {
                root->setRight(insert(input, root->right));
            }
            return root;
        }
        // input->priority > root->priority
        if (input->key < root->key) {
            auto leftSplit = split(input->key, root->left);
            input->setLeft(leftSplit.first);
            root->setLeft(leftSplit.second);
            input->setRight(root);
        } else {
            auto rightSplit = split(input->key, root->right);
            input->setRight(rightSplit.second);
            root->setRight(rightSplit.first);
            input->setLeft(root);
        }
        return input;
    }
    treapNode* merge(treapNode* leftNode, treapNode* rightNode) {
        // left subtree is smaller than right subtree
        if (leftNode == NULL) return rightNode;
        if (rightNode == NULL) return leftNode;
        if (leftNode->priority > rightNode->priority) {
            leftNode->setRight(merge(leftNode->right, rightNode));
            calcSize();
            return leftNode;
        } else {
            rightNode->setLeft(merge(leftNode, rightNode->left));
            calcSize();
            return rightNode;
        }
    }
    pair<treapNode*, treapNode*> split(int value, treapNode* root) {
        if (root == NULL) {
            return pair<treapNode*, treapNode*>{NULL, NULL};
        }
        pair<treapNode*, treapNode*> result;
        if (value > root->key) {
            auto tmp = split(value, root->right);
            result.first = merge(root->left, tmp.first);
            result.second = tmp.second;
        } else {
            auto tmp = split(value, root->left);
            result.first = tmp.first;
            result.second = merge(tmp.second, root->right);
        }
        return result;
    }
    treapNode* erase(int key, treapNode* root) {
        if (root == NULL) {
            cout << "There's no " << key << " in this Tree\n";
            return NULL;
        }
        if (key == root->key) {
            return merge(root->left, root->right);
        }
        if (key > root->key) {
            root->setRight(erase(key, root->right));
        } else {
            root->setLeft(erase(key, root->left));
        }
    }
    treapNode* find(int key, treapNode* root) {
        auto tmp = root;
        while (tmp != NULL) {
            if (key == tmp->key) {
                return tmp;
            } else if (key > tmp->key) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }
        return NULL;
    }
    treapNode* findKth(int num, treapNode* root) {
        int rootIdx = root->left->size + 1;
        if (num < rootIdx) {
            return findKth(num, root->left);
        } else if (num == rootIdx) {
            return root;
        } else {
            return findKth(num - rootIdx, root->right);
        }
    }
};

#endif