// Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

// @* subtree, tree에 대한 조건/결과는 subtree에도 동일하게 적용됨을 유의하자
void NERD2_Input(int& applicantsNum, vector<int>& arg1Arr, vector<int>& arg2Arr) {
    cin >> applicantsNum;
    arg1Arr.resize(applicantsNum);
    arg2Arr.resize(applicantsNum);
    for (int i = 0; i < applicantsNum; i++) {
        cin >> arg1Arr[i] >> arg2Arr[i];
    }
}
int NERD2_Algo(int applicantsNum, vector<int> arg1Arr, vector<int> arg2Arr) {
    // arg1과 arg2를 묶는다.
    vector<pair<int, int>> argsArr(applicantsNum);
    for (int i = 0; i < applicantsNum; i++) {
        argsArr[i].first = arg1Arr[i];
        argsArr[i].second = arg2Arr[i];
    }
    // arg1에 대해 내림차순 정렬한다.
    sort(argsArr.begin(), argsArr.end(), greater<pair<int, int>>());
    // tree(set) 에 대하여 input을 해주고, 매번 nerd참가자의 수를 계산하여 정답을 구한다.
    int result = 0;
    int nerds = 0;
    set<int> tree;
    for (auto& ele : argsArr) {
        tree.insert(ele.second);
        if (ele.second == *tree.rbegin()) {
            nerds++;
        }
        result += nerds;
        cout << ":::" << nerds << endl;
    }
    return result;
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
        방법2: 각각의 사람마다 두가지 값을 시간내에 계산하는것은 불가능하다. 즉, 하나의 값은 미리 계산해놔야 한다는 것이다.
            p에대해 내림차순 정렬하고, 순서대로 q값을 tree input한다.
            앞서 tree에 들어간 값들은 모두 now보다 p가 크므로, now는 q가 제일커야, tree에서 제일 커야 nerd가 될 수 있다.
            정렬시간(nlgn) + tree생성 시간(nlgn) = O(nlgn) 으로 해결이 가능하다.
            문제점: 참가자가 지원한 순서대로 심사되어야 한다.
    /*전략
    전략1
        아이디어: tree, pre-sorting
            Arr을 p에대해 내림차순 정렬한다.
            idx=0부터 시작해서, q값을 tree에 input한다.
                q값이 tree에서 가장 큰 값이라면, 해당 참가자는
                그렇지 않다면, nerd 참가자 수는 그대로이다.
            매 input마다 nerd참가자수를 결과값에 더한다.
        분석
            time complexity: O(nlgn)
            mem complexity: O(n)
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
        int applicantsNum;
        vector<int> arg1Arr, arg2Arr;
        NERD2_Input(applicantsNum, arg1Arr, arg2Arr);
        auto result = NERD2_Algo(applicantsNum, arg1Arr, arg2Arr);
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
