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

// @* subtree, tree에 대한 조건/결과는 subtree에도 동일하게 적용됨을 유의하자
void FORTRESS_Input(int& fortressNum, vector<int>& fortressXpos, vector<int>& fortressYpos, vector<int>& fortressRadius) {
    cin >> fortressNum;
    fortressXpos.resize(fortressNum);
    fortressYpos.resize(fortressNum);
    fortressRadius.resize(fortressNum);
    for (int i = 0; i < fortressNum; i++) {
        cin >> fortressXpos[i] >> fortressYpos[i] >> fortressRadius[i];
    }
}
bool FORTRESS_isSubtree(vector<int>& fortressXpos, vector<int>& fortressYpos, vector<int>& fortressRadius, int root, int now) {
    int rx(fortressXpos[root]), ry(fortressYpos[root]), rr(fortressRadius[root]);
    int nx(fortressXpos[now]), ny(fortressYpos[now]);
    double distance = sqrt(pow(rx - nx, 2) + pow(ry - ny, 2));
    if (distance < rr) {
        return true;
    } else {
        return false;
    }
}
pair<int, int> FORTRESS_getHeights(vector<int>& fortressXpos, vector<int>& fortressYpos, vector<int>& fortressRadius, vector<int>& tree) {
    // pair.first = subtree의 height, pair.second = subtree내부에서 가장 많이 fortress를 넘어야 하는 횟수
    //기저
    pair<int, int> results(0, 0);
    if (tree.size() == 1) {
        return results;
    }
    // subtree 구분하기
    vector<vector<int>> subtrees;
    for (int idx = 1; idx < tree.size(); idx++) {
        bool inserted(false);
        //각 subtree에 포함되는지 확인
        for (auto& subtree : subtrees) {
            int root = subtree.front();
            if (FORTRESS_isSubtree(fortressXpos, fortressYpos, fortressRadius, root, tree[idx])) {
                subtree.push_back(tree[idx]);
                inserted = true;
                break;
            }
        }
        //어느 subtree에도 포함되지 않는다면, 새로운 subtree(child)이다.
        if (!inserted) {
            subtrees.push_back(vector<int>(1, tree[idx]));
        }
    }
    //재귀하기
    vector<int> heights;
    for (auto& subtree : subtrees) {
        auto tmp = FORTRESS_getHeights(fortressXpos, fortressYpos, fortressRadius, subtree);
        heights.push_back(tmp.first + 1);
        results.second = max(results.second, tmp.second);
    }
    // 가장 큰 height 계산
    sort(heights.begin(), heights.end(), greater<int>());
    results.first = heights.front();
    // subtree내부에서 가장 많은 move 계산
    int inFortressMove = heights.front();
    if (heights.size() > 1) {
        inFortressMove += heights[1];
    }
    results.second = max(results.second, inFortressMove);
    return results;
}
int FORTRESS_Algo(int fortressNum, vector<int> fortressXpos, vector<int> fortressYpos, vector<int> fortressRadius) {
    vector<int> tree(fortressNum);
    for (int i = 0; i < fortressNum; i++) {
        tree[i] = i;
    }
    //항상 큰 성벽이 작은 성벽을 포함하므로, 내림차순 정렬을 해준다.
    sort(tree.begin(), tree.end(), [&fortressRadius](int a, int b) -> bool { return fortressRadius[a] > fortressRadius[b]; });
    auto results = FORTRESS_getHeights(fortressXpos, fortressYpos, fortressRadius, tree);
    return results.second;
}
void FORTRESS() {
    /*설명 및 입력
    설명
        성벽들의 정보가 주어질 때 가장 성벽을 많이 넘어야 하는 두 지점 간을 이동하기 위해 몇 번이나 성벽을 넘어야 하는지 계산하는 프로그램을 작성하세요.
        왕래는 성벽 내에서만 이루어집니다.
    입력
        입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 100) 가 주어집니다.
        각 테스트 케이스의 첫 줄에는 성벽의 수 N (1 <= N <= 100) 이 주어집니다.
        그 후 N 줄에는 각 3개의 정수로 각 성벽의 위치와 크기에 대한 정보 xi , yi , ri 가 주어집니다.
            (0 <= xi, yi <= 1000,1 <= ri <= 1000,0 <= i<N) 이 때 i 번 성벽은 (xi, yi) 를 중심으로 하는 반지름 ri 인 원형으로 설치되어 있습니다.
        편의상 모든 성벽의 두께는 0이라고 가정하며, 입력에 주어지는 성벽들은 서로 겹치거나 닿지 않습니다.
        입력에 주어지는 첫 번째 성벽은 외벽이며, 외벽은 입력에 주어지는 모든 다른 성벽을 포함합니다.
    출력
        각 테스트 케이스마다 한 줄에 두 지점 간 이동을 위해 최대 몇 번이나 성벽을 넘어야 하는지를 출력하세요.
    제한조건
        1초, 64MB
    */
    /*힌트
        각 child를 root로하는 subtree의 원소를 알 수 있다면, 문제를 재귀적으로 풀어나갈 수 있다.
            만약 성벽이 기존의 child에 포함되거나/포함한다면, 기존 child와 같은 subtree에 존재한다.
            만약 성벽이 기존의 child중 어느것에도 포함되지 않는다면, 이것은 새로운 child, 즉 새로운 subtree를 생성한다.
        성벽은 겹치지 않으므로, 한 subtree의 root는 반지름이 가장 큰 것임을 알 수 있다.
        재귀적 풀이: subtree의 모든 child의 height를 반환하면 된다.
        성벽은 겹치지 않으므로, 큰 성벽이 작은 성벽을 포함한다. 즉 parent의 radius는 항상 child의 rad보다 크다.
            성벽의 둘레를 기준으로 내림차순 정렬을 하면, 편하계 계산할 수 있다.
        한 subtree내부에서 움직이는것이 가장 큰 움직임일 수도 있다.
    */
    /*전략
    전략1
        아이디어: tree, 재귀
            root를 구한다 -> O(1)
            subtrees를 구분하는 2차원 배열을 만든다.
                subtrees[i] = i 번째 child를 root로 가지는 subtree의 원소들
            성벽을 기존의 children과 비교한다 -> O(n^2)
                기존의 child를 포함하거나/포함된다면, subtrees[i].push_back(now);
                기존의 child와 관계가 없다면, subtrees.push_back(vector<int>(now));
            heights를 나타내는 배열을 만든다.
            각 children에 대해 재귀하여 subtree들의 height를 구한다. -> n times * O(n^2)
                heights[i] = max(child_subtree_heights)+1
            return heights
            마지막으로 반환된 값을 가지고, 가장 큰 값과 그다음 큰 값을 더하면 된다.
        분석
            time complexity: O(n^3)
            mem complexity: O(N)
        피드백
    */
    // Sol
    int testCase;
    cin >> testCase;
    //전역변수
    cout << fixed;
    cout.precision(10);
    //각 테스트케이스
    while (testCase--) {
        int fortressNum;
        vector<int> fortressXpos, fortressYpos, fortressRadius;
        FORTRESS_Input(fortressNum, fortressXpos, fortressYpos, fortressRadius);
        auto result = FORTRESS_Algo(fortressNum, fortressXpos, fortressYpos, fortressRadius);
        // cout << "::::";
        cout << result << endl;
    }
}

int main(void) {
    //   clock_t start,end;
    //   start=clock();
    FORTRESS();
    //   end=clock();;
    //   cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}
