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

void MEASURETIME_Input(int &peopleNum, int &relationsNum, vector<int> &parentsArr, vector<pair<int, int>> &relationsArr) {
    cin >> peopleNum >> relationsNum;
    signInfoArr.resize(peopleNum);
    roadInfoArr.resize(relationsNum);
    for (auto &ele : parentsArr) {
        scanf("%d", &ele);
    }
    for (auto &ele : relationsArr) {
        scanf("%d %d", &ele.first, &ele.second);
    }
}
int MEASURETIME_getSize(int signNum) {
    int power = log(signNum) / log(2);
    if (signNum <= pow(2, power)) {
        return pow(2, power + 1);
    } else {
        return pow(2, power + 2);
    }
}
pair<int, int> MEASURETIME_init(vector<pair<int, int>> &segTree, vector<int> &signInfoArr, int node, int left, int right) {
    if (left == right) {
        return segTree[node] = make_pair(signInfoArr[left], signInfoArr[left]);
    }
    auto leftSubtree = MEASURETIME_init(segTree, signInfoArr, node * 2, left, (left + right) / 2);
    auto rightSubtree = MEASURETIME_init(segTree, signInfoArr, node * 2 + 1, (left + right) / 2 + 1, right);
    return segTree[node] = make_pair(min(leftSubtree.first, rightSubtree.first), max(leftSubtree.second, rightSubtree.second));
}
pair<int, int> MEASURETIME_query(vector<pair<int, int>> &segTree, int node, int treeL, int treeR, int targetL, int targetR) {
    pair<int, int> result;
    if (treeR < targetL || targetR < treeL) {
        return make_pair(23456, -1);
    } else if (targetL <= treeL && treeR <= targetR) {
        return segTree[node];
    } else {
        auto leftSubtree = MEASURETIME_query(segTree, node * 2, treeL, (treeL + treeR) / 2, targetL, targetR);
        auto rightSubtree = MEASURETIME_query(segTree, node * 2 + 1, (treeL + treeR) / 2 + 1, treeR, targetL, targetR);
        return make_pair(min(leftSubtree.first, rightSubtree.first), max(leftSubtree.second, rightSubtree.second));
    }
}
vector<int> MEASURETIME_Algo(int signNum, int roadNum, vector<int> signInfoArr, vector<pair<int, int>> roadInfoArr) {
    // make segment Tree, pair.first = min, pair.second = max
    vector<pair<int, int>> segTree(MEASURETIME_getSize(signNum));
    MEASURETIME_init(segTree, signInfoArr, 1, 0, signNum - 1);
    // use segment Tree
    vector<int> difficulties(roadNum);
    for (int i = 0; i < roadNum; i++) {
        auto tmp = MEASURETIME_query(segTree, 1, 0, signNum - 1, roadInfoArr[i].first, roadInfoArr[i].second);
        difficulties[i] = tmp.second - tmp.first;
    }
    return difficulties;
}
void MEASURETIME() {
    /*설명 및 입력
    설명
        길이 N 인 수열 A[] 가 주어집니다.
        수열을 Insertion Sort 하는 과정에서 숫자들을 총 몇 번이나 옮기는지를 계산하는 프로그램을 작성하세요.
    입력
        입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다.
        각 테스트 케이스의 첫 줄에는 원 배열의 길이 N (1 <= N <= 50000) 이 주어집니다.
        그 다음 줄에 N개의 정수로 A의 원소 Ai가 주어집니다. (0 <= Ai < 1,000,000)
    출력
        각 테스트 케이스마다 한 줄에 A를 삽입정렬하는 과정에서 숫자를 옮기는 총 횟수를 출력합니다.
    제한조건
        2초, 256MB
    */
    /*힌트
        입력이 크므로, 빠른 입력을 이용한다.
        아이디어 1:
        책의 아이디어:
    */
    /*
    전략1: tree에 key를 부여해주어서, search tree의 성질을 띄도록한다.
        구현
            2차원 child arr을 만든다. O(n)
            child arr을 이용하여 query를 수행하며, key와 depth를 부여한다. O(n)
            m 경우의 촌수 계산. m*O(lgn)
                최소 공통 조상의 depth를 구하고, 두 사람의 촌수를 계산한다.. O(lgn)
        분석
            time complexity: O(n+mlgn)
            mem complexity: O(n)
        피드백
    책의 전략: A node와 b node를 방문하려면, 항상 최소공통조상(A,B)를 중간에 방문함을 이용하여 segment tree를 만든다.
        구현
            2차원 child arr을 만든다. O(n)
            child arr을 이용하여 query를 수행하며, visitArr과 positionArr, depthArr 을 만든다. O(n)
                visitArr: 방문하는 순서대로 node를 기록, 다시 방문한 것도 모두 기록한다.
                positionArr: node의 visitArr에서의 위치 기록, 마지막 위치로 기록한다.
            visitArr로 segment tree를 만든다. O(n)
            m 경우의 촌수 계산 m*O(lgn)
                segment tree를 이용하여 최소공통조상을 구하고, 두 사람의 촌수를 계산한다.
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
        int peopleNum, relationsNum;
        vector<int> parentsArr;
        vector<pair<int, int>> relationsArr;
        MEASURETIME_Input(peopleNum, relationsNum, parentsArr, relationsArr);
        auto result = MEASURETIME_Algo(peopleNum, relationsNum, parentsArr, relationsArr);
        // cout << "::::";
        for (auto &ele : result) {
            cout << ele << "\n";
        }
    }
}

int main(void) {
    // clock_t start,end;
    // start=clock();
    MEASURETIME();
    // end=clock();;
    // cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}