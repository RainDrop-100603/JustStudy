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
void NERD2_Input(int& NERD2Num, vector<int>& NERD2Xpos, vector<int>& NERD2Ypos, vector<int>& NERD2Radius) {
    cin >> NERD2Num;
    NERD2Xpos.resize(NERD2Num);
    NERD2Ypos.resize(NERD2Num);
    NERD2Radius.resize(NERD2Num);
    for (int i = 0; i < NERD2Num; i++) {
        cin >> NERD2Xpos[i] >> NERD2Ypos[i] >> NERD2Radius[i];
    }
}
bool NERD2_isSubtree(vector<int>& NERD2Xpos, vector<int>& NERD2Ypos, vector<int>& NERD2Radius, int root, int now) {
    int rx(NERD2Xpos[root]), ry(NERD2Ypos[root]), rr(NERD2Radius[root]);
    int nx(NERD2Xpos[now]), ny(NERD2Ypos[now]);
    double distance = sqrt(pow(rx - nx, 2) + pow(ry - ny, 2));
    if (distance < rr) {
        return true;
    } else {
        return false;
    }
}
pair<int, int> NERD2_getHeights(vector<int>& NERD2Xpos, vector<int>& NERD2Ypos, vector<int>& NERD2Radius, vector<int>& tree) {
    // pair.first = subtree의 height, pair.second = subtree내부에서 가장 많이 NERD2를 넘어야 하는 횟수
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
            if (NERD2_isSubtree(NERD2Xpos, NERD2Ypos, NERD2Radius, root, tree[idx])) {
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
        auto tmp = NERD2_getHeights(NERD2Xpos, NERD2Ypos, NERD2Radius, subtree);
        heights.push_back(tmp.first + 1);
        results.second = max(results.second, tmp.second);
    }
    // 가장 큰 height 계산
    sort(heights.begin(), heights.end(), greater<int>());
    results.first = heights.front();
    // subtree내부에서 가장 많은 move 계산
    int inNERD2Move = heights.front();
    if (heights.size() > 1) {
        inNERD2Move += heights[1];
    }
    results.second = max(results.second, inNERD2Move);
    return results;
}
int NERD2_Algo(int NERD2Num, vector<int> NERD2Xpos, vector<int> NERD2Ypos, vector<int> NERD2Radius) {
    vector<int> tree(NERD2Num);
    for (int i = 0; i < NERD2Num; i++) {
        tree[i] = i;
    }
    //항상 큰 성벽이 작은 성벽을 포함하므로, 내림차순 정렬을 해준다.
    sort(tree.begin(), tree.end(), [&NERD2Radius](int a, int b) -> bool { return NERD2Radius[a] > NERD2Radius[b]; });
    auto results = NERD2_getHeights(NERD2Xpos, NERD2Ypos, NERD2Radius, tree);
    return results.second;
}
void NERD2() {
    /*설명 및 입력
    설명
        올해에도 참가 신청을 한 사람 중 진정한 프로그래밍 너드들만을 대회에 참가할 수 있도록 받아 주기로 했습니다.
        종만의 새로운 이론에 따르면, 어떤 사람의 너드 지수는 다음 두 가지 값에 의해 결정됩니다.
            알고스팟 온라인 채점 시스템에서 푼 문제의 수 p
            밤 새면서 지금까지 끓여먹은 라면 그릇 수 q
        이 이론에 따르면 어떤 참가 신청자 a 의 문제 수 pa 와 그릇 수 qa 를 다른 참가 신청자 b 의 문제 수 pb 와 그릇 수 qb 에 각각 비교했을 때,
            pa < pb, qa < qb 라면 참가 신청자 a 는 너드일 가능성이 없습니다.
            조직위는 너드일 가능성이 있는 사람들만을 대회에 받아주기로 했습니다.
        한 사람의 참가 가능 여부는 다른 사람들에 의해 결정되기 때문에, 대회에 참가할 수 있는 사람의 수는 새로운 사람이 참가 신청을 할 때마다 계속 바뀝니다.
        이렇게 각 사람이 참가 신청을 할 때마다 대회에 참가할 수 있는 사람들의 수가 어떻게 변하는지 계산하는 프로그램을 작성하세요.
    입력
        입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다.
        각 테스트 케이스의 첫 줄에는 참가 신청한 사람들의 수 N (1 <= N <= 50000) 이 주어집니다.
        그 후 N 줄에 각 2개의 정수로 각 사람의 문제 수 pi 와 라면 그릇 수 qi 가 참가 신청한 순서대로 주어집니다 (0 <= pi,qi <= 100000) .
        두 사람의 문제 수나 라면 그릇 수가 같은 경우는 없다고 가정해도 좋습니다.
        입력의 양이 많으므로 가능한 빠른 입력 함수를 사용하는 것이 좋습니다..
    출력
        각 사람이 참가 신청을 할 때마다 대회 참가 자격이 되는 사람의 수를 계산한 뒤, 각 테스트 케이스마다 그 합을 출력합니다.
    제한조건
        2초, 64MB
    */
    /*힌트
        너드는, 다른 모든 사람과 비교했을 때, p 혹은 q 가 커야한다는 특징이 있다.
        방법1: p와 q를 각각 tree형태로 저장하고, p와 q 모두 자기보다 큰 사람을 배열에 저장한다.
                idx번째 입력까지의 결과는, 자기보다 큰 사람을 idx번째 까지의 사람만 인정하는것으로 계산하면 된다.
            예상되는 시간: 비교시간(O(n)) * 모든사람(n times) + 트리구성(O(nlgn)) + 너드계산(O(n^2)) = O(n^2)
            문제점: n<=50000이기 때문에 n^2으로는 풀 수 없다.
        사람이 n명이기 때문에, 각각의 사람에 대해 검사하려면 lgn 시간에 검사를 끝내야한다.
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
        int NERD2Num;
        vector<int> NERD2Xpos, NERD2Ypos, NERD2Radius;
        NERD2_Input(NERD2Num, NERD2Xpos, NERD2Ypos, NERD2Radius);
        auto result = NERD2_Algo(NERD2Num, NERD2Xpos, NERD2Ypos, NERD2Radius);
        // cout << "::::";
        cout << result << endl;
    }
}

int main(void) {
    //   clock_t start,end;
    //   start=clock();
    NERD2();
    //   end=clock();;
    //   cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}
