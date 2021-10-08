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
    void setLeft(treapNode* node) {
        left = node;
        calcSize();
    }
    void setRight(treapNode* node) {
        right = node;
        calcSize();
    }
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};

class treap {
    treapNode* root;
    // organize tree
    treapNode* insert(treapNode* root, treapNode* input) {
        if (root == NULL) {
            return input;
        }
        //
        if (root->priority > input->priority) {
            if (input->key < root->key) {
                root->setLeft(insert(root->left, input));
            } else {
                root->setRight(insert(root->right, input));
            }
            return root;
        }
        //
        auto splitted = split(root, input->key);
        input->setLeft(splitted.first);
        input->setRight(splitted.second);
        return input;
    }
    treapNode* erase(treapNode* root, int key) {
        // get target and parent
        auto node = root;
        treapNode* parentNode = NULL;
        while (node->key != key) {
            if (key < node->key) {
                parentNode = node;
                node = node->left;
            } else {
                parentNode = node;
                node = node->right;
            }
        }
        // erase target and parent->setChild(merge(target->left,targte->right))
        auto merged = merge(node->left, node->right);
        if (parentNode == NULL) {
            return merged;
        } else if (node == parentNode->left) {
            parentNode->setLeft(merged);
            return parentNode;
        } else {
            parentNode->setRight(merged);
            return parentNode;
        }
    }
    pair<treapNode*, treapNode*> split(treapNode* root, int key) {
        pair<treapNode*, treapNode*> result{NULL, NULL};
        if (root == NULL) {
            return result;
        }
        //
        if (key < root->key) {
            auto splitted = split(root->left, key);
            root->setLeft(splitted.second);
            result.first = splitted.first;
            result.second = root;
        } else {
            auto splitted = split(root->right, key);
            root->setRight(splitted.first);
            result.first = root;
            result.second = splitted.second;
        }
        return result;
    }
    treapNode* merge(treapNode* lNode, treapNode* rNode) {
        if (lNode == NULL) return rNode;
        if (rNode == NULL) return lNode;
        //
        if (lNode->priority > rNode->priority) {
            lNode->setRight(merge(lNode->right, rNode));
            return lNode;
        } else {
            rNode->setLeft(merge(lNode, rNode->left));
            return rNode;
        }
    }
    // use tree
    treapNode* find(treapNode* root, int key) {
        auto node = root;
        while (node != NULL) {
            if (node->key == key) {
                return node;
            } else if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return NULL;
    }

   public:
    treap() : root(NULL) {}
    // organize tree
    treap& insert(int key) {
        if (!isExist(key)) {
            root = insert(root, new treapNode(key));
        }
        return *this;
    }
    treap& erase(int key) {
        if (isExist(key)) {
            auto target = find(root, key);
            root = erase(root, key);
            delete target;
        }
        return *this;
    }
    // use tree
    bool isExist(int key) {
        if (root && find(root, key)) return true;
        return false;
    }
    int kthNode(int num) {  // idx begin from 0
        num++;              // idx begin from 0, but size begin from 1
        if (root == NULL || root->size < num) {
            return -1;
        }
        auto node = root;
        while (true) {
            int nodeIdx = 1;
            if (node->left) nodeIdx += node->left->size;
            if (num == nodeIdx) {
                return node->key;
            } else if (num < nodeIdx) {
                node = node->left;
            } else {
                num -= nodeIdx;
                node = node->right;
            }
        }
    }
    int countLessThan(int key) {
        if (!isExist(key)) {
            return -1;
        }
        auto node = root;
        int count = 0;
        while (true) {
            int leftSize = 0;
            if (node->left) leftSize += node->left->size;
            if (key == node->key) {
                count += leftSize;
                break;
            } else if (key > node->key) {
                count += leftSize + 1;
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return count;
    }
    int size() { return root ? root->size : 0; }
    int min() { return kthNode(0); }
    int max() { return kthNode(size() - 1); }
};

#endif