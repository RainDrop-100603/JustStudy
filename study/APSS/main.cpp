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

// segment tree
void MORDOR_Input(int &signNum, int &roadNum, vector<int> &signInfoArr, vector<pair<int, int>> &roadInfoArr) {
    cin >> signNum >> roadNum;
    signInfoArr.resize(signNum);
    roadInfoArr.resize(roadNum);
    for (auto &ele : signInfoArr) {
        scanf("%d", &ele);
    }
    for (auto &ele : roadInfoArr) {
        scanf("%d %d", &ele.first, &ele.second);
    }
}
pair<int, int> MORDOR_init(vector<pair<int, int>> &segTree, vector<int> &signInfoArr, int node, int left, int right) {
    if (left == right) {
        return segTree[node] = make_pair(signInfoArr[left], signInfoArr[left]);
    }
    auto leftSubtree = MORDOR_init(segTree, signInfoArr, node * 2, left, (left + right) / 2);
    auto rightSubtree = MORDOR_init(segTree, signInfoArr, node * 2 + 1, (left + right) / 2 + 1, right);
    return segTree[node] = make_pair(min(leftSubtree.first, rightSubtree.first), max(leftSubtree.second, rightSubtree.second));
}
pair<int, int> MORDOR_query(vector<pair<int, int>> &segTree, int node, int treeL, int treeR, int targetL, int targetR) {
    pair<int, int> result;
    if (treeR < targetL || targetR < treeL) {
        return segTree[0];
    } else if (targetL <= treeL && treeR <= targetR) {
        return segTree[node];
    } else {
        auto leftSubtree = MORDOR_query(segTree, node * 2, treeL, (treeL + treeR) / 2, targetL, targetR);
        auto rightSubtree = MORDOR_query(segTree, node * 2 + 1, (treeL + treeR) / 2 + 1, treeR, targetL, targetR);
        return make_pair(min(leftSubtree.first, rightSubtree.first), max(leftSubtree.second, rightSubtree.second));
    }
}
vector<int> MORDOR_Algo(int signNum, int roadNum, vector<int> signInfoArr, vector<pair<int, int>> roadInfoArr) {
    // make segment Tree, pair.first = min, pair.second = max
    vector<pair<int, int>> segTree(pow(2, 1 + ceil(log(signNum) / log(2))));
    segTree[0] = make_pair(23456, -1);  // meaningless value
    MORDOR_init(segTree, signInfoArr, 1, 0, signNum - 1);
    // use segment Tree
    vector<int> difficulties(roadNum);
    for (int i = 0; i < roadNum; i++) {
        auto tmp = MORDOR_query(segTree, 1, 0, signNum - 1, roadInfoArr[i].first, roadInfoArr[i].second);
        difficulties[i] = tmp.second - tmp.first;
    }
    return difficulties;
}
void MORDOR() {
    /*설명 및 입력
    설명
        등산로에는 100미터 간격으로 표지판이 있는데, 각 표지판의 해발 고도를 측정한 자료가 있습니다.
        이 때 등산로의 난이도는 등산로를 가다 만나는 표지판 중 최대 해발 고도와 최저 해발 고도의 차이입니다.
        개방을 검토하고 있는 등산로의 일부가 주어질 때, 각 부분의 난이도를 계산하는 프로그램을 작성하세요.
    입력
        입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 30) 가 주어집니다.
        각 테스트 케이스의 첫 줄에는 원래 등산로에 있는 표지판의 수 N (1 <= N <= 100,000)과 개방을 고려하고 있는 등산로의 수 Q (1 <= Q <= 10,000)가 주어집니다.
        그 다음 줄에 N 개의 정수로 각 표지판의 해발 고도 hi 가 순서대로 주어집니다. (0 <= hi <= 20,000)
        각 표지판은 입력에 주어지는 순서대로 0 번부터 N-1 번까지 번호가 매겨져 있습니다.
        그 다음 Q 줄에 각 2개의 정수로 개방을 고려하고 있는 등산로의 첫 번째 표지판과 마지막 표지판의 번호 a , b (0 <= a <= b < N) 가 주어집니다.
    출력
        한 줄에 하나씩 개방을 고려하고 있는 각 등산로의 난이도를 출력합니다.
    제한조건
        5초, 64MB
    */
    /*힌트
        입력이 크므로, 빠른 입력을 이용한다.
        구간의 min, max 를 구하는 것이므로, segment tree를 이용하면 된다.
            min segment tree, max segment tree를 이용하거나, pair를 이용하여 min과 max를 둘다 저장한다.
    */
    /*전략
        아이디어: pair<min,max>를 저장하는 segment tree
            segment tree 생성 O(n)
            m개의 등산로에 대해 m*O(lgn)
                segment tree query O(lgn)
        분석
            time complexity: O(n+mlgn)
            mem complexity: O(n)
        피드백
    */
    // Sol
    int testCase;
    cin >> testCase;
    //각 테스트케이스
    while (testCase--) {
        int signNum, roadNum;
        vector<int> signInfoArr;
        vector<pair<int, int>> roadInfoArr;
        MORDOR_Input(signNum, roadNum, signInfoArr, roadInfoArr);
        auto result = MORDOR_Algo(signNum, roadNum, signInfoArr, roadInfoArr);
        // cout << "::::";
        for (auto &ele : result) {
            cout << ele << "\n";
        }
    }
}

int main(void) {
    // clock_t start,end;
    // start=clock();
    MORDOR();
    // end=clock();;
    // cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}
