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
    treapNode(int _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) { cout << "treapNode" << _key << "created\n"; }
    ~treapNode() { cout << "treapNode" << key << "deleted\n"; }
    // base func
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
    // do not use this pointer
    treapNode* insert(treapNode* root, treapNode* input) {  // only insert via key, not node
        if (root == NULL) {
            return input;
        }
        // input->priority < priority
        if (input->priority < root->priority) {
            if (input->key < root->key) {
                root->setLeft(insert(root->left, input));
            } else {
                root->setRight(insert(root->right, input));
            }
            return root;
        }
        // input->priority > priority
        auto splitted = split(root, input->key);
        input->setLeft(splitted.first);
        input->setRight(splitted.second);
        return input;
    }
    treapNode* erase(treapNode* root, int key) {
        if (root->key == key) {
            return merge(root->right, root->left);
        } else if (root->key < key) {
            root->setRight(erase(root->right, key));
            return root;
        } else {
            root->setLeft(erase(root->left, key));
            return root;
        }
    }
    pair<treapNode*, treapNode*> split(treapNode* root, int value) {
        // divide subtree by value
        if (root == NULL) {
            return pair<treapNode*, treapNode*>{NULL, NULL};
        }
        if (value > root->key) {
            auto rightSplit = split(root->right, value);
            root->setRight(rightSplit.first);
            return pair<treapNode*, treapNode*>{root, rightSplit.second};
        } else {
            auto leftSplit = split(root->left, value);
            root->setLeft(leftSplit.second);
            return pair<treapNode*, treapNode*>{leftSplit.first, root};
        }
    }
    treapNode* merge(treapNode* leftNode, treapNode* rightNode) {
        // 기저
        if (leftNode == NULL) return rightNode;
        if (rightNode == NULL) return leftNode;
        // left node is smaller than right node
        if (leftNode->key > rightNode->key) return merge(rightNode, leftNode);
        // should be left.max < right.min
        if (leftNode->max() > rightNode->min()) {
            cout << "subtree(root=" << leftNode->key << ") and subtree(root=" << rightNode->key << ") cant be merged, cause leftSubtree.max >= rightSubtree.min\n";
            return NULL;
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
    // use this pointer
    treapNode* find(int _key) {
        if (_key == key) {
            return this;
        } else if (_key > key) {
            if (right) {
                return right->find(key);
            } else {
                return NULL;
            }
        } else {
            if (left) {
                return left->find(key);
            } else {
                return NULL;
            }
        }
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
        auto root = this;
        while (root != NULL) {
            int leftSize = root->left ? root->left->size : 0;
            if (key == root->key) {
                result += leftSize;
                return result;
            } else if (key > root->key) {
                result += leftSize + 1;
                root = root->right;
            } else {
                root = root->left;
            }
        }
        return -1;  // there's no key in the root-subtree
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
        if (!find(key)) {
            root = root->insert(root, new treapNode(key));
        }
        return *this;
    }
    treap& erase(int key) {
        if (root) {
            if (auto target = root->find(key)) {
                root = root->erase(root, key);
                delete target;
            }
        }
        return *this;
    }
    bool find(int key) {
        if (root && root->find(key)) {
            return true;
        }
        return false;
    }
    int findKth(int num) { return root->findKth(num)->key; }
    int countLessThan(int key) { return root->countLessThan(key); }
    int size() { return root->size; }
    void printTree() {
        vector<treapNode*> stack;
        stack.push_back(root);
        while (!stack.empty()) {
            vector<treapNode*> tmpStack;
            for (auto& ele : stack) {
                cout << ele->key << " ";
                if (ele->left) {
                    tmpStack.push_back(ele->left);
                }
                if (ele->right) {
                    tmpStack.push_back(ele->right);
                }
            }
            cout << endl;
            stack.swap(tmpStack);
        }
    }
};

#endif