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

// suffix arr, stack
void HABIT_Input(string& speech, int& isHabit) { cin >> isHabit >> speech; }
struct HABIT_Comparator {  // suffixArr에서의 정렬에 사용한다. 각 접미사가 t만큼 비교되어 있을 때, 2t만큼 비교한다.
    const vector<int>& group;
    int t;
    HABIT_Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
    bool operator()(int a, int b) {
        if (group[a] != group[b]) {
            return group[a] < group[b];
        }
        return group[a + t] < group[b + t];
    }
};
vector<int> HABIT_suffixArr(const string& str) {
    int strLen = str.length();
    // group[i] = order, str[i:] 의 order
    vector<int> group(strLen + 1);  // comparator 연산시 group[strLen]까지 접근한다.
    group[strLen] = -1;             //문자열 a와 a+b는 사전순으로 a가 더 앞에 온다.
    for (int i = 0; i < strLen; i++) {
        // ASCII CODE 자체가 order라고 봐도 무방하다.
        group[i] = str[i];
    }
    // perm[order]=i, str[i:]의 order
    vector<int> perm(strLen);
    for (int i = 0; i < strLen; i++) {
        perm[i] = i;
    }
    //정렬
    int t = 1;
    while (t < strLen) {
        // 각 접미사의 2t만큼의 접두사를 비교하여 정렬한다.
        HABIT_Comparator cmp2T(group, t);
        sort(perm.begin(), perm.end(), cmp2T);
        t *= 2;
        if (t >= strLen) {
            break;
        }
        // group 갱신
        vector<int> tmpGroup(strLen);
        int prev = perm[0];
        tmpGroup[prev] = 0;
        for (int i = 1; i < strLen; i++) {
            int now = perm[i];
            if (cmp2T(prev, now)) {
                tmpGroup[now] = tmpGroup[prev] + 1;
            } else {
                tmpGroup[now] = tmpGroup[prev];
            }
            prev = now;
        }
        group = tmpGroup;
    }
    return perm;
}
int HABIT_strOverlap(const string& str, int begin1, int begin2) {
    int len = 0;
    while (len + begin1 < int(str.length()) && len + begin2 < int(str.length()) && str[begin1] == str[begin2]) {
        len++;
        begin1++;
        begin2++;
    }
    return len;
}
int HABIT_stackPop(vector<int>& stack, vector<int>& overlap, int isHabit, int nowIdx) {
    int now = overlap[nowIdx];
    int last = overlap[stack.back()];
    int maxHabit = 0;
    while (now <= last) {
        stack.pop_back();
        if (nowIdx - stack.back() >= isHabit) {
            maxHabit = max(maxHabit, last);
        }
        last = overlap[stack.back()];
    }
    return maxHabit;
}
int HABIT_Algo(string speech, int isHabit) {
    if (isHabit == 1) {
        return speech.length();
    }
    int maxHabit = 0;
    // get suffix arr
    vector<int> suffixArr = HABIT_suffixArr(speech);
    int suffixArrLen = suffixArr.size();
    // use stack
    vector<int> stack;                            // idx
    vector<int> overlap(suffixArrLen + 1);        // value[idx]
    overlap[0] = -2, overlap[suffixArrLen] = -1;  // set left wall and right wall
    stack.push_back(0);                           // push left wall
    for (int i = 1; i < suffixArrLen; i++) {
        overlap[i] = HABIT_strOverlap(speech, suffixArr[i-1], suffixArr[i]));
        maxHabit = max(maxHabit, HABIT_stackPop(stack, overlap, isHabit, i));
        stack.push_back(i);
    }
    maxHabit = max(maxHabit, HABIT_stackPop(stack, overlap, isHabit, suffixArrLen));  // push right wall
    return maxHabit;
}
void HABIT() {
    /*설명 및 입력
    설명
        정박사가 지금까지 했던 발표들과 강의들에서 했던 말을 모두 음성 인식을 통해 대본으로 만들었습니다.
        이 때 대본 중 K 번 이상 등장하는 부분 문자열을 "말버릇" 이라고 합시다.
        대본이 주어질 때 가장 긴 말버릇의 길이를 찾는 프로그램을 작성하세요.
    입력
        입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다.
        각 테스트 케이스는 두 줄로 주어지며, 첫 줄에는 K (1 <= K <= 1000) 가, 두 번째 줄에는 정박사의 발표 대본이 주어집니다.
        대본은 공백 없이 알파벳 소문자로만 구성된 문자열이며 길이는 1 이상이고 4000 을 넘지 않습니다.
    출력
        각 테스트 케이스마다 K 번 이상 등장하는 부분 문자열의 최대 길이를 출력합니다.
        어떤 부분 문자열도 K 번 이상 등장하지 않는다면 0 을 출력합니다.
    제한조건
        1초, 64MB
    */
    /*힌트
         suffix arr의 접두사를 이용하여, 모든 부분문자열을 구할 수 있다.
            이때 중복등장하는 접두사들은, 접두사들의 suffix가 모두 이웃한다는 점을 이용할 수 있다.
         이웃하는 suffix가 겹치는 정도를 모두 구하고, stack을 통해 K번 이상 등장한 문자열들의 길이를 구할 수 있다.
            algospot - fence를 생각하자. 같은 원리이다.
    */
    /*전략
    전략1
        아이디어: suffix arr, stack
            suffix arr을 구한다. -> n (lgn)^2
            suffix arr을 순회하며 -> n * O(n)
                이웃하는 suffix arr의 겹치는 길이를 구한다. -> O(n)
                stack을 이용하여 각 부분문자열의 최대길이를 구하자. -> O(1)
        분석
            time complexity: O(n^2)
            mem complexity: O(N)
        피드백
            substr을 구하지 않도록 개선 -> ver2
    */
    // Sol
    int testCase;
    cin >> testCase;
    //전역변수
    cout << fixed;
    cout.precision(10);
    //각 테스트케이스
    while (testCase--) {
        string speech;
        int isHabit;
        HABIT_Input(speech, isHabit);
        auto result = HABIT_Algo(speech, isHabit);
        // cout << "::::";
        cout << result << endl;
    }
}

int main(void) {
    //   clock_t start,end;
    //   start=clock();
    HABIT();
    //   end=clock();;
    //   cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}
