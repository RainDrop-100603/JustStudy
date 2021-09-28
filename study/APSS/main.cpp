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

// KMP search 변형문제, circular shift
void HABIT_Input(string& speech, int& isHabit) { cin >> speech >> isHabit; }
vector<int> HABIT_suffixArr(const string& str) {}
int HABIT_strOverlap(const string& str1, const string& str2) {
    int len = 0;
    while (len < str1.length() && len < str2.length() && str1[len] == str2[len]) {
        len++;
    }
    return len;
}
int HABIT_stackPop(vector<pair<int, int>>& stack, int idx, int now) {}
int HABIT_Algo(string speech, int isHabit) {
    int result = 0;
    // get suffix arr
    vector<int> suffixArr = HABIT_suffixArr(speech);
    int suffixArrLen = suffixArr.size();
    // use stack
    vector<pair<int, int>> stack;  // idx, value
    stack.push_back(make_pair(0, 0));
    string nowstr = speech.substr(suffixArr[0]);
    for (int i = 1; i < suffixArrLen; i++) {
        string prevstr = nowstr;
        nowstr = speech.substr(suffixArr[i]);
        int last = stack.back().second;
        int now = HABIT_strOverlap(nowstr, prevstr);
        if (now <= last) {
            result = max(result, HABIT_stackPop(stack, i, now));
        }
        stack.push_back(make_pair(i, now));
    }
    result = max(result, HABIT_stackPop(stack, suffixArrLen, -1));
    return result;
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
            time complexity: O(n(lgn)^2)
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
        string speech;
        int isHabit;
        HABIT_Input(speech, isHabit);
        auto result = HABIT_Algo(speech, isHabit);
        // cout<<"::::";
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
