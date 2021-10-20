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

// @*@*@* 비교할 key가 없는 tree에 key를 부여하여 search tree처럼 만들기
// query를 할 때, node A를 비교하고 node B를 비교하기전에, 항상 최소공통조상(A,B)를 방문함을 이용하여 segment tree 만들기
void FAMILYTREE_Input(int &peopleNum, int &casesNum, vector<int> &parentsArr, vector<pair<int, int>> &casesArr) {
    cin >> peopleNum >> casesNum;
    parentsArr.resize(peopleNum);
    casesArr.resize(casesNum);
    for (int i = 1; i < peopleNum; i++) {
        scanf("%d", &parentsArr[i]);
    }
    for (auto &ele : casesArr) {
        scanf("%d %d", &ele.first, &ele.second);
    }
}
vector<vector<int>> FAMILYTREE_makeChildArr(vector<int> &parentsArr) {
    int peopleNum = parentsArr.size();
    vector<vector<int>> result(peopleNum);
    for (int i = 1; i < peopleNum; i++) {
        result[parentsArr[i]].push_back(i);
    }
    return result;
}
int FAMILYTREE_giveKeyAndDepth(vector<vector<int>> &childArr, vector<int> &keyArr, vector<int> &depthArr, int node, int key, int depth) {
    for (auto &child : childArr[node]) {
        key = FAMILYTREE_giveKeyAndDepth(childArr, keyArr, depthArr, child, key, depth + 1);
    }
    keyArr[node] = key;
    depthArr[node] = depth;
    return key + 1;
}
int FAMILYTREE_query(vector<vector<int>> &childArr, vector<int> &keyArr, int node, int depth, int person1, int person2) {
    for (auto &child : childArr[node]) {
        // 둘다 child의 자손인 경우, 최소공통조상은 child 혹은 child의 자손이다.
        if (keyArr[person1] <= keyArr[child] && keyArr[person2] <= keyArr[child]) {
            return FAMILYTREE_query(childArr, keyArr, child, depth + 1, person1, person2);
        }
        // 하나만 child의 자손인 경우, 최소 공통조상은 node다
        if (keyArr[person1] <= keyArr[child] || keyArr[person2] <= keyArr[child]) {
            return depth;
        }
    }
    return depth;
}
vector<int> FAMILYTREE_Algo(int peopleNum, int casesNum, vector<int> parentsArr, vector<pair<int, int>> casesArr) {
    // 2차원 child arr을 만든다. O(n)
    auto childArr = FAMILYTREE_makeChildArr(parentsArr);
    // child arr을 이용하여 query를 수행하며, key와 depth를 부여한다. O(n)
    vector<int> keyArr(peopleNum), depthArr(peopleNum);
    FAMILYTREE_giveKeyAndDepth(childArr, keyArr, depthArr, 0, 1, 0);
    // m 경우의 촌수 계산. m*O(lgn)
    vector<int> result(casesNum);
    for (int i = 0; i < casesNum; i++) {
        //같은 사람일 경우
        if (casesArr[i].first == casesArr[i].second) {
            result[i] = 0;
            continue;
        }
        // 최소 공통 조상의 depth를 구하고, 두 사람의 촌수를 계산한다.
        int depth = FAMILYTREE_query(childArr, keyArr, 0, 0, casesArr[i].first, casesArr[i].second);
        result[i] = depthArr[casesArr[i].first] + depthArr[casesArr[i].second] - depth * 2;
    }
    // return
    return result;
}
void FAMILYTREE_algo2ArrSet(vector<vector<int>> &childArr, vector<int> &visitArr, vector<int> &positionArr, vector<int> &depthArr, int node, int depth, int &sequence) {
    visitArr.push_back(node);
    positionArr[node] = sequence;
    sequence++;
    depthArr[node] = depth;
    for (auto &child : childArr[node]) {
        FAMILYTREE_algo2ArrSet(childArr, visitArr, positionArr, depthArr, child, depth + 1, sequence);
    }
}
vector<int> FAMILYTREE_Algo2(int peopleNum, int casesNum, vector<int> parentsArr, vector<pair<int, int>> casesArr) {
    // 2차원 child arr을 만든다. O(n)
    auto childArr = FAMILYTREE_makeChildArr(parentsArr);
    // child arr을 이용하여 query를 수행하며, visitArr과 positionArr, depthArr 을 만든다. O(n)
    //     visitArr: 방문하는 순서대로 node를 기록, 다시 방문한 것도 모두 기록한다.
    //     positionArr: node의 visitArr에서의 위치 기록, 마지막 위치로 기록한다.
    vector<int> visitArr, positionArr(peopleNum), depthArr(peopleNum);
    int visitArrSize = 0;
    FAMILYTREE_algo2ArrSet(childArr, visitArr, positionArr, depthArr, 0, 0, visitArrSize);
    // visitArr로 segment tree를 만든다. O(n)
    vector<int> segTree(pow(2, 1 + ceil(log(visitArrSize) / log(2))));
    segTree[0] = 123456;
    FAMILYTREE_segTreeInit(segTree, visitArr, 1, 0, visitArrSize - 1);
    // m 경우의 촌수 계산 m*O(lgn)
    //     segment tree를 이용하여 최소공통조상을 구하고, 두 사람의 촌수를 계산한다.
}
void FAMILYTREE() {
    /*설명 및 입력
    설명
        어떤 가문의 족보가 시조부터 시작해 쭉 주어질 때, 두 사람의 촌수를 계산하는 프로그램을 작성하세요.
    입력
        입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다.
            각 테스트 케이스는 한 가문의 족보와 촌수를 계산할 사람들의 쌍들로 구성됩니다.
        각 테스트 케이스의 첫 줄에는 족보에 포함된 사람의 수 N (1 <= N <= 100,000) 과 촌수를 계산할 두 사람의 수 Q (1 <= Q <= 10,000) 가 주어집니다.
                이 때 족보에 포함된 사람들은 0번부터 N-1 번까지 번호가 매겨져 있으며, 0번은 항상 이 가문의 시조입니다.
            테스트 케이스의 두 번째 줄에는 N-1 개의 정수로 1번부터 N-1 번까지 각 사람의 아버지의 번호가 주어집니다.
            그 다음 Q 줄에 각 2개의 정수로 두 사람의 번호 a, b 가 주어집니다. (0 <= a,b < N)
        족보에는 시조의 후손이 아닌 사람은 주어지지 않으며, 자기 자신의 조상이 되는 등의 모순된 입력 또한 주어지지 않습니다.
    출력
        각 사람의 쌍마다 한 줄에 두 사람의 촌수를 출력합니다.
    제한조건
        2초, 256MB
    */
    /*힌트
        입력이 크므로, 빠른 입력을 이용한다.
        아이디어 1: tree에 key를 부여해주어서, search tree의 성질을 띄도록한다.
            query를 하려면 비교를 할 것이 필요하다.
            subtree는 항상 root보다 작은 key를 갖도록 각 node에 key를 부여해준다.
                left subtree < rightsubtree < root 순서
            tree를 문제에서 주어지는대로 생성하고, key를 부여하고, query를 하면 문제를 풀 수 있다.
            tree를 만들지 않고 arr로만 수행하면 속도가 더 빠를 것이다.
                child 를 나타내는 2차원배열을 생성한다.
        책의 아이디어: A node와 b node를 방문하려면, 항상 최소공통조상(A,B)를 중간에 방문함을 이용하여 segment tree를 만든다.

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
        int peopleNum, casesNum;
        vector<int> parentsArr;
        vector<pair<int, int>> casesArr;
        FAMILYTREE_Input(peopleNum, casesNum, parentsArr, casesArr);
        auto result = FAMILYTREE_Algo(peopleNum, casesNum, parentsArr, casesArr);
        // cout << "::::";
        for (auto &ele : result) {
            cout << ele << "\n";
        }
    }
}

int main(void) {
    // clock_t start,end;
    // start=clock();
    FAMILYTREE();
    // end=clock();;
    // cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}
