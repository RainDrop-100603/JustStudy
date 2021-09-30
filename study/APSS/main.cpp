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

// @* tree, preorder, inorder, postorder, 적절한 재귀를 통해, tree를 구현하지 않고도 문제를 풀어냈다.
void FORTRESS_Input(int& fortressNum, vector<int>& fortressXpos, vector<int>& fortressYpos, vector<int>& fortressRadius) {
    cin >> fortressNum;
    fortressXpos.resize(fortressNum);
    for (auto& ele : fortressXpos) {
        cin >> ele;
    }
    fortressYpos.resize(fortressNum);
    for (auto& ele : fortressYpos) {
        cin >> ele;
    }
    fortressRadius.resize(fortressNum);
    for (auto& ele : fortressRadius) {
        cin >> ele;
    }
}
int FORTRESS_isSubtree(vector<int>& fortressXpos, vector<int>& fortressYpos, vector<int>& fortressRadius, int root, int idx) {
    int rx(fortressXpos[root]), ry(fortressYpos[root]), rr(fortressRadius[root]);
    int nx(fortressXpos[idx]), ny(fortressYpos[idx]), nr(fortressRadius[idx]);
    double distance = sqrt(pow(rx - nx, 2) + pow(ry - ny, 2));
    //포함하는가, 포함되는가를 따진다.
    int contain = 1;
    if (nr > rr) {
        rr = nr;
        contain = -1;
    }
    //계산
    if (distance < rr) {
        return contain;
    } else {
        return 0;
    }
}
vector<int> FORTRESS_getHeights(vector<int>& fortressXpos, vector<int>& fortressYpos, vector<int>& fortressRadius, vector<int>& tree) {
    //기저
    if (tree.size() == 0) {
        return vector<int>(1, -1);
    }
    // subtree 구분하기
    int rootIdx = tree[0];
    vector<vector<int>> subtrees;
    for (int idx = 1; idx < subtrees.size(); idx++) {
        bool inserted(false);
        //각 subtree에 포함되는지 확인
        for (auto& subtree : subtrees) {
            int root = subtree.front();
            int is_subtree = FORTRESS_isSubtree(fortressXpos, fortressYpos, fortressRadius, root, idx);
            if (is_subtree == 1) {
                subtree.push_back(idx);
                inserted = true;
                break;
            } else if (is_subtree == -1) {
                subtree.insert(subtree.begin(), idx);
                inserted = true;
                break;
            }
        }
        //어느 subtree에도 포함되지 않는다면, 새로운 subtree(child)이다.
        if (!inserted) {
            subtrees.push_back(vector<int>(1, idx));
        }
    }
    //재귀하기
    vector<int> heights;
    for (auto& subtree : subtrees) {
        auto height = FORTRESS_getHeights(fortressXpos, fortressYpos, fortressRadius, subtree);
        heights.push_back(height[0] + 1);
    }
    sort(heights.begin(), heights.end(), greater<>());
    return heights;
}
int FORTRESS_Algo(int fortressNum, vector<int> fortressXpos, vector<int> fortressYpos, vector<int> fortressRadius) {
    vector<int> subtree(fortressNum);
    for (int i = 0; i < fortressNum; i++) {
        subtree[i] = i;
    }
    auto heights = FORTRESS_getHeights(fortressXpos, fortressYpos, fortressRadius, subtree);
    if (heights.size() == 1) {
        return heights[0] + 1;  //외벽 밖으로 나갈 수 있다.
    } else {
        return heights[0] + heights[1];
    }
}
void FORTRESS() {
    /*설명 및 입력
    설명
        성벽들의 정보가 주어질 때 가장 성벽을 많이 넘어야 하는 두 지점 간을 이동하기 위해 몇 번이나 성벽을 넘어야 하는지 계산하는 프로그램을 작성하세요.
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
