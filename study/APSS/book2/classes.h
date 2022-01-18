#ifndef __CLASSES_H__
#define __CLASSES_H__

#include <memory.h>

#include <iostream>
#include <vector>

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

class fenwicktree {
    vector<int> tree;
    int size;

   public:
    fenwicktree(int _size) : tree(_size + 1), size(_size) {}
    void add(int pos, int value) {
        pos++;  // idx starts from 1
        while (pos <= size) {
            tree[pos] += value;
            pos += (pos & -pos);  // add pos' last bit
        }
    }
    int pSum(int pos) {
        pos++;
        int result = 0;
        while (pos > 0) {
            result += tree[pos];
            pos -= (pos & -pos);
        }
        return result;
    }
};

class RangeMinimunQuery {
    vector<int> rangeMin;
    int capacity, size;
    int USELESS = INT32_MAX;
    int init(vector<int>& inputArr, int node, int left, int right) {
        if (left == right) {
            return rangeMin[node] = inputArr[left];
        }
        int leftMin = init(inputArr, node * 2 + 1, left, (left + right) / 2);
        int rightMin = init(inputArr, node * 2 + 2, (left + right) / 2 + 1, right);
        return rangeMin[node] = min(leftMin, rightMin);
    }
    int query(int node, int left, int right, int rangeLeft, int rangeRight) {
        // query 범위 밖
        if (rangeRight < left || right < rangeLeft) return USELESS;
        // query 범위에 완전히 포함
        if (rangeLeft <= left && right <= rangeRight) return rangeMin[node];
        // query 범위에 일부 포함
        int leftQuery = query(node * 2 + 1, left, (left + right) / 2, rangeLeft, rangeRight);
        int rightQuery = query(node * 2 + 2, (left + right) / 2 + 1, right, rangeLeft, rangeRight);
        return min(leftQuery, rightQuery);
    }
    int update(int node, int left, int right, int idx, int value) {
        if (idx < left || right < idx) return USELESS;
        if (left == right) {
            return rangeMin[node] = value;
        }
        int leftMin = update(node * 2 + 1, left, (left + right) / 2, idx, value);
        int rightMin = update(node * 2 + 2, (left + right) / 2 + 1, right, idx, value);
        return rangeMin[node] = min(leftMin, rightMin);
    }

   public:
    RangeMinimunQuery(vector<int>& inputArr) {
        capacity = pow(2, ceil(log(inputArr.size()) / log(2)));
        size = inputArr.size();
        rangeMin.resize(capacity * 2);
        init(inputArr, 0, 0, size - 1);
    }
    int query(int left, int right) { return query(0, 0, size - 1, left, right); }
    bool update(int idx, int value) {
        if (idx >= size) return false;
        update(0, 0, size - 1, idx, value);
        return true;
    }
    bool push(int value) {
        if (size == capacity) return false;
        size++;
        update(0, 0, size - 1, size - 1, value);
        return true;
    }
    bool pop() {
        if (size == 0) return false;
        update(0, 0, size - 1, size - 1, USELESS);
        size--;
        return true;
    }
};

class SOLONG_TrieNode {
   public:
    SOLONG_TrieNode* children[26];
    int terminal = -1;
    int priority = -1;
    int autoTerminal = -1;
    int autoPriority = -1;
    SOLONG_TrieNode() { memset(children, 0, sizeof(children)); }
    ~SOLONG_TrieNode() {
        for (auto& ele : children) {
            if (ele) delete ele;
        }
    }
    int stringToIdx(char chars) { return chars - 'A'; }
    void insert(const vector<string>& dict, const string& str, int idx, int terminal, int priority) {
        // set autoComplete, root do not have autoComplete
        if (idx > 0) {
            if (priority > this->autoPriority) {
                this->autoPriority = priority;
                this->autoTerminal = terminal;
            } else if (priority == this->autoPriority && str.compare(dict[this->autoTerminal]) < 0) {
                this->autoTerminal = terminal;
            }
        }
        // if insert finished
        if (idx == str.length()) {
            this->terminal = terminal;
            this->priority = priority;
            return;
        }
        // goto next node
        auto& target = children[stringToIdx(str[idx])];
        if (target == NULL) target = new SOLONG_TrieNode();
        target->insert(dict, str, idx + 1, terminal, priority);
    }
    SOLONG_TrieNode* find(const string& str, int idx) {
        // found
        if (str.length() == idx) return this;
        // find
        auto& target = children[stringToIdx(str[idx])];
        if (target == NULL) return NULL;
        return target->find(str, idx + 1);
    }
    int autoComplete(const string& str, int idx, int terminal) {
        // found
        if (this->autoTerminal == terminal) return idx + 1;
        if (str.length() == idx) return idx;
        // find
        auto& target = children[stringToIdx(str[idx])];
        if (target == NULL) return 20;
        return target->autoComplete(str, idx + 1, terminal);
    }
};

class SOLONG_TrieNode2 {
   public:
    SOLONG_TrieNode2* children[26];
    int terminal = -1;
    int first = -1;
    SOLONG_TrieNode2() { memset(children, 0, sizeof(children)); }
    ~SOLONG_TrieNode2() {
        for (auto& ele : children) {
            if (ele) delete ele;
        }
    }
    int stringToIdx(char chars) { return chars - 'A'; }
    void insert(const string& str, int idx, int terminal) {
        // if insert finished
        if (idx == str.length()) {
            this->terminal = terminal;
            return;
        }
        // goto next node
        auto& target = children[stringToIdx(str[idx])];
        if (target == NULL) {
            target = new SOLONG_TrieNode2();
            target->first = terminal;
        }
        target->insert(str, idx + 1, terminal);
    }
    SOLONG_TrieNode2* find(const string& str, int idx) {
        // found
        if (str.length() == idx) return this;
        // find
        auto& target = children[stringToIdx(str[idx])];
        if (target == NULL) return NULL;
        return target->find(str, idx + 1);
    }
    int autoComplete(const string& str, int idx, int terminal) {
        // found
        if (this->first == terminal) return idx + 1;
        if (str.length() == idx) return idx;
        // find
        auto& target = children[stringToIdx(str[idx])];
        if (target == NULL) return 20;
        return target->autoComplete(str, idx + 1, terminal);
    }
};

#endif