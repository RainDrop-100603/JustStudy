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

// @*@*@* binary search tree(map), 시각화를 통해 문제해결의 힌트를 얻을 수 있다.
class INSERTION_node {
   public:
    int key, size;
    INSERTION_node *left, *right;
    INSERTION_node(int _key) : key(_key), size(1), left(NULL), right(NULL) {}
    void setLeft(INSERTION_node* node) {
        left = node;
        calcSize();
    }
    void setRight(INSERTION_node* node) {
        right = node;
        calcSize();
    }
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};
class INSERTION_treap {
    INSERTION_node* root;
    INSERTION_node* makeBalanceTree(int size, int now) {
        if (now >= size) {
            return NULL;
        }
        auto node = new INSERTION_node(now);
        node->setLeft(makeBalanceTree(size, now * 2 + 1));
        node->setRight(makeBalanceTree(size, now * 2 + 2));
        return node;
    }
    void setBalanceTree() {
        for (int i = 0; i < root->size; i++) {
            find(i)->key = i;
        }
    }
    INSERTION_node* find(int idx) {
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

   public:
    INSERTION_treap(int size) : root(NULL) {
        if (size > 0) {
            root = new INSERTION_node(0);
            makeBalanceTree(size, 0);
            setBalanceTree();
        }
    }
    int kthNode(int idx) {
        if (root == NULL) return -1;
        return find(idx)->key;
    }
    void moveNode(int from, int to) {
        auto fromNode = find(from);
        auto toNode = find(to);
        if (to == 0) {
        }
        auto toNodeParent = find(to / 2);
    }
};
void INSERTION_Input(int& applicantsNum, vector<int>& arg1Arr, vector<int>& arg2Arr) {
    cin >> applicantsNum;
    arg1Arr.resize(applicantsNum);
    arg2Arr.resize(applicantsNum);
    for (int i = 0; i < applicantsNum; i++) {
        cin >> arg1Arr[i] >> arg2Arr[i];
    }
}
int INSERTION_Algo(int applicantsNum, vector<int> arg1Arr, vector<int> arg2Arr) {
    // tree: map을 생성한다
    map<int, int> tree;
    //모든 입력에 대해 순차적으로 처리한다, tree가 빈 경우는 맨 처음밖에 없으므로 미리 처리
    int result(1);
    tree.insert(make_pair(arg1Arr[0], arg2Arr[0]));
    for (int i = 1; i < applicantsNum; i++) {
        int key = arg1Arr[i];
        int value = arg2Arr[i];
        // delete 연산,
        while (true) {
            auto nextIter = tree.lower_bound(key);
            if (nextIter == tree.begin()) {
                break;
            }
            auto prevIter = --nextIter;
            if (value > prevIter->second) {
                tree.erase(prevIter);
            } else {
                break;
            }
        }
        // insert 연산
        auto nextIter = tree.lower_bound(key);
        if (nextIter == tree.end() || value > nextIter->second) {
            tree.insert(make_pair(key, value));
        }
        result += tree.size();
    }
    return result;
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
        n^2 time
            arr, linked list,
    */
    /*전략
        아이디어: custom tree
            custom tree를 만든다.


            custom tree를 순회하며, 적절한 위치에 값을 넣어서 A[]를 복원한다.
        분석
            time complexity: O(nlgn)
                입력처리 : 반복 n회
                    delete: 최대 n회, 평균 1회, lgn
                    insert: lgn
                    tree.size : 1
            mem complexity: O(n)
        피드백
            문제를 시각화 하는것이 도움이 될 수 있다.
    */
    // Sol
    int testCase;
    cin >> testCase;
    //전역변수
    cout << fixed;
    cout.precision(10);
    //각 테스트케이스
    while (testCase--) {
        int applicantsNum;
        vector<int> arg1Arr, arg2Arr;
        INSERTION_Input(applicantsNum, arg1Arr, arg2Arr);
        auto result = INSERTION_Algo(applicantsNum, arg1Arr, arg2Arr);
        // cout << "::::";
        cout << result << endl;
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
