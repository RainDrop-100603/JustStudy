#include <iostream>

using namespace std;

class treap_node {
   public:
    int key, size, priority;
    treap_node *left, *right;
    treap_node(int _key) : key(_key), size(1), priority(rand()), left(NULL), right(NULL) {}
    void setLeft(treap_node* node) {
        left = node;
        calcSize();
    }
    void setRight(treap_node* node) {
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
    treap_node* root;
    // organize tree
    treap_node* insert(treap_node* node, treap_node* input) {
        if (node == NULL) {
            return input;
        }
        //
        if (input->priority < node->priority) {
            if (input->key < node->key) {
                node->setLeft(insert(node->left, input));
            } else {
                node->setRight(insert(node->right, input));
            }
            return node;
        }
        //
        auto splitted = split(node, input->key);
        input->setLeft(splitted.first);
        input->setRight(splitted.second);
        return input;
    }
    treap_node* erase(treap_node* node, int key) {
        if (key == node->key) {
            return merge(node->left, node->right);
        } else if (key < node->key) {
            node->setLeft(erase(node->left, key));
            return node;
        } else {
            node->setRight(erase(node->right, key));
            return node;
        }
    }
    pair<treap_node*, treap_node*> split(treap_node* node, int key) {
        pair<treap_node*, treap_node*> result{NULL, NULL};
        if (node != NULL) {
            if (key < node->key) {
                auto splitted = split(node->left, key);
                node->setLeft(splitted.second);
                result.first = splitted.first;
                result.second = node;
            } else {
                auto splitted = split(node->right, key);
                node->setRight(splitted.first);
                result.first = node;
                result.second = splitted.second;
            }
        }
        return result;
    }
    treap_node* merge(treap_node* leftNode, treap_node* rightNode) {
        if (leftNode == NULL) return rightNode;
        if (rightNode == NULL) return leftNode;
        //
        if (leftNode->priority > rightNode->priority) {
            leftNode->setRight(merge(leftNode->right, rightNode));
            return leftNode;
        } else {
            rightNode->setLeft(merge(leftNode, rightNode->left));
            return rightNode;
        }
    }
    // use tree
    treap_node* find(int key) {
        auto node = root;
        while (node != NULL) {
            if (key == node->key) {
                return node;
            } else if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return NULL;
    }
    treap_node* kthNode(int idx) {
        idx++;  // idx begin from 1, instead of 0
        if (root == NULL || root->size < idx) return NULL;
        auto node = root;
        while (true) {
            int nodeIdx = 1;
            if (node->left) nodeIdx += node->left->size;
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
    // erase tree
    void clean(treap_node* node) {
        if (node->left) clean(node->left);
        if (node->right) clean(node->right);
        delete node;
    }

   public:
    treap() : root(NULL) {}
    ~treap() {
        if (root) clean(root);
    }
    void insert(int key) {
        if (!isExist(key)) {
            root = insert(root, new treap_node(key));
        }
    }
    void erase(int key) {
        if (isExist(key)) {
            auto target = find(key);
            root = erase(root, key);
            delete target;
        }
    }
    bool isExist(int key) { return find(key) ? true : false; }
    int kthKey(int idx) {
        if (auto ret = kthNode(idx)) {
            return ret->key;
        } else {
            cout << idx << " is larger than treap size" << endl;
            return -123456789;
        }
    }
    int operator[](int idx) { return kthKey(idx); }
    bool empty() { return root == NULL; }
    int size() { return root ? root->size : 0; }
};
