// Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <string>
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

// @*@*@* treap, sort-de_sort의 관계와 같이, 순차적으로 수행된 어떤작업은, 반대로 수행함으로서 원래 상태로 되돌릴 수 있다.
// treap을 이용할때, return값 조심
void INSERTION_Input(int& size, vector<int>& shifted) {
    cin >> size;
    shifted.resize(size);
    for (auto& ele : shifted) {
        cin >> ele;
    }
}
vector<int> INSERTION_Algo(int size, vector<int> shifted) {
    treap sorted;
    for (int i = 1; i <= size; i++) {
        sorted.insert(i);
    }
    vector<int> original(size);

    while (!sorted.empty()) {
        int lastIdx = sorted.size() - 1;
        original[lastIdx] = sorted[lastIdx - shifted[lastIdx]];
        sorted.erase(original[lastIdx]);
    }
    return original;
}
void INSERTION() {
    /*설명 및 입력
    설명
        1부터 N까지의 자연수가 한 번씩 포함된 길이 N 인 수열 A[] 를 삽입 정렬했습니다.
        원래 수열은 알 수 없지만, 그 과정에서 각 원소가 왼쪽으로 몇 칸이나 이동했는지를 알고 있습니다.
            예를 들어, 5 1 4 3 2 수열이 움직인 칸수를 표현하면 {0,1,1,2,3} 이 됩니다.
        이 때 원래 수열을 찾아내는 프로그램을 작성하세요.
    입력
        입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다.
        각 테스트 케이스의 첫 줄에는 원 배열의 길이 N (1 <= N <= 50000) 이 주어집니다.
        그 다음 줄에 N 개의 정수로 A의 각 위치에 있던 값들이 움직인 칸수가 주어집니다.
        A 는 1부터 N 까지의 정수를 한 번씩 포함합니다.
    출력
        각 테스트 케이스마다 재구성한 A[] 를 한 줄에 출력합니다.
    제한조건
        2초, 64MB
    */
    /*힌트
        입력이 크므로, 빠른 입력을 이용한다.
        한번 움직인것은, 왼쪽으로 한칸 이동한 것이다.
            즉 가상의 행렬을 만들어서 이를 움직이고, 움직인 결과가 insertion sort의 결과임을 이용하여, A[]를 재구성한다
                예: ABCDE를 움직이면 BEDCA = 12345 이므로, ABCDE = 51432 이다.
            문제점: 매번 최대 n time움직이면, 전체 시간은 O(n^2)이 된다.
            특정한 방법을 이용하여 lgn시간내에 목적지를 찾아 한번에 이동하면 O(nlgn)으로 풀 수 있다.
        custom tree를 이용하는 방법
            초기상태: n번째 위치에 있는 node의 key는 n 이다.
                n개의 node를 갖는 balance tree를 만들어서, n번째 node의 key를 n으로 대체한다.
                balance tree 생성법
                    root에서부터 높은 depth로 내려가면서
                        차례대로 왼쪽에서 부터 순서를 센다고 가정하고 (0, 12, 34 56 과 같은식)
                    n번째 node의 child는 각각 2n+1, 2n+2 번째 node다.
                    재귀적으로, child가 범위 안에 들어오면 추가하고, 아니면 null을 추가한다.
            특징: key로 정렬하지 않고, 임의로 정렬한다.
            k번째 node가 어디에 있는지 알 수 있다.
            원하는 n번째 위치에 input이 가능하다. 단, 더 큰 위치에서 더 작은 위치로만 가능하다.
                    (더 작은 위치로도 약간만 생각하면 가능하다)
                n번째 위치의 값을 input으로 대체한다.
                기존에 있던 prev는 input의 right child으로 대체한다.
            tree를 완성하고 나서, 트리를 0~N-1 번째 까지 순회한다.
                0번째 값이 k라면, 0의 최초 위치는 k번째라는 뜻이다.-
        책 참고: 역순으로 문제를 해결하는 방법
            변수
                shifted_arr(움직인횟수) original_arr(sort이전) sorted_treap(sort된 것, treap로 저장)
            방법
                앞에서부터 뒤로가면서 insertion sort를 수행한다 -> 맨 마지막 원소는 단 한번만 움직인다.
                    original[idx] = sorted_treap[treap_size - shifted[idx]]
                        idx == unsorted된 것들 중 last
                    sorted_treap.pop[treap_size - shifted[idx]]
            분석
                time complexity: n times * O(lgn)
        n^2 time
            arr, linked list,
    */
    /*전략
        아이디어: treap
            args: shifted_arr(움직인횟수)
            sorted_treap 생성, treap에 1~N까지 입력
            original_arr 생성, 원래 배열 의미
            while(sorted_tree.size>0)
                lastIdx = sorted_tree.size -1
                original_arr[lastIdx] = sorted_treap[lastIdx - shifted_arr[lastIdx]]
                sorted_treap.remove(original_arr[lastIdx])
        분석
            time complexity: O(nlgn)
                입력처리 : 반복 n회
                    treap[idx] (search) -> = O(lgn)
                    treap.remove -> O(lgn)
            mem complexity: O(n)
        피드백
            sort는 순서대로 수행되었으므로, 반대로 하면 원래 행렬을 구할 수 있다.
    */
    // Sol
    int testCase;
    cin >> testCase;
    //전역변수
    cout << fixed;
    cout.precision(10);
    //각 테스트케이스
    while (testCase--) {
        int size;
        vector<int> shifted;
        INSERTION_Input(size, shifted);
        auto result = INSERTION_Algo(size, shifted);
        // cout << "::::";
        for (auto& ele : result) {
            cout << ele << " ";
        }
        cout << endl;
    }
}

int main(void) {
    // clock_t start,end;
    // start=clock();
    INSERTION();
    // end=clock();;
    // cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}
