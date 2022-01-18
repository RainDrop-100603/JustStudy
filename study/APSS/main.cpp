// Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <memory.h>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "classes.h"

using namespace std;

void SOLONG_Input(int& dictLen, int& inputLen, vector<string>& dictWord, vector<int>& dictPriority, vector<string>& inputWord) {
    cin >> dictLen >> inputLen;
    dictWord.resize(dictLen);
    dictPriority.resize(dictLen);
    inputWord.resize(inputLen);
    char strBuffer[100];
    for (int i = 0; i < dictLen; i++) {
        scanf("%s %d", strBuffer, &dictPriority[i]);
        dictWord[i] = string(strBuffer);
        // cin >> dictWord[i] >> dictPriority[i];
    }
    for (int i = 0; i < inputLen; i++) {
        scanf("%s", strBuffer);
        inputWord[i] = string(strBuffer);
        // cin >> inputWord[i];
    }
}
int SOLONG_Algo(int dictLen, int inputLen, const vector<string>& dictWord, const vector<int>& dictPriority, const vector<string>& inputWord) {
    // make trie
    SOLONG_TrieNode trieRoot;
    for (int i = 0; i < dictLen; i++) {
        trieRoot.insert(dictWord, dictWord[i], 0, i, dictPriority[i]);
    }
    // autoComplete find
    int ret = 0;
    for (int i = 0; i < inputLen; i++) {
        auto node = trieRoot.find(inputWord[i], 0);
        int wordLen = inputWord[i].length();
        int autoComplete = 20;
        if (node && node->terminal != -1) autoComplete = trieRoot.autoComplete(inputWord[i], 0, node->terminal);
        ret += min(wordLen, autoComplete);
    }
    ret += inputLen - 1;  //단어 사이사이 공백
    // return
    return ret;
}
int SOLONG_Algo2(int dictLen, int inputLen, const vector<string>& dictWord, const vector<int>& dictPriority, const vector<string>& inputWord) {
    // sort dict by priority and lexicographical order
    vector<pair<int, string>> dict2(dictLen);
    for (int i = 0; i < dictLen; i++) {
        dict2[i].first = dictPriority[i] * -1;  // bigger is first
        dict2[i].second = dictWord[i];
    }
    sort(dict2.begin(), dict2.end());
    // make trie
    SOLONG_TrieNode2 trieRoot;
    for (int i = 0; i < dictLen; i++) {
        trieRoot.insert(dict2[i].second, 0, i);
    }
    // autoComplete find
    int ret = 0;
    for (int i = 0; i < inputLen; i++) {
        auto node = trieRoot.find(inputWord[i], 0);
        int wordLen = inputWord[i].length();
        int autoComplete = 20;
        if (node && node->terminal != -1) autoComplete = trieRoot.autoComplete(inputWord[i], 0, node->terminal);
        ret += min(wordLen, autoComplete);
    }
    ret += inputLen - 1;  //단어 사이사이 공백
    // return
    return ret;
}
int SOLONG_Main() {
    int dictLen, inputLen;
    vector<string> dictWord, inputWord;  // 0 is ACK, 1 is DIS
    vector<int> dictPriority;
    SOLONG_Input(dictLen, inputLen, dictWord, dictPriority, inputWord);
    // auto ret= SOLONG_Algo(dictLen, inputLen, dictWord, dictPriority, inputWord);
    auto ret = SOLONG_Algo2(dictLen, inputLen, dictWord, dictPriority, inputWord);
    return ret;
}
void SOLONG_print() {
    /*설명 및 입력
    설명
        이번에 출시한 돌고래용 타블렛의 자동 완성 알고리즘은 사전에 저장된 N개의 단어들을 이용해 자동완성을 수행합니다.
            돌고래가 새 단어를 타이핑하기 시작하면,
            자동 완성 시스템은 지금까지 타이핑한 부분으로 시작하는 사전 내 단어 중 가장 출현 빈도가 높은 것을 자동으로 추천합니다.
            만약 출현 빈도가 가장 높은 것이 여러 개 있다면 사전순으로(돌고래의 사전 역시 알파벳 순을 따릅니다)
            가장 앞에 오는 단어가 추천되지요. 돌고래가 탭 키를 누르면 지금 추천된 단어가 자동으로 입력됩니다.
            자동완성을 할 수 없다면 모두 입력해야 합니다.
        자동완성 예시
            단어(빈도): SO(3) AND(4) ALL(3)
            입력횟수: SO=S+자동(2), AND=A+자동(2), ALL=AL+자동(3), THANKS(6)
        단 이 타블렛에는 이미 입력한 단어를 편집하는 기능이 없기 때문에,
            THANKS를 입력하고 "S"를 지워서 "THANK"를 만들거나
            "THE"를 입력하고 "RE"를 덧붙여서 "THERE"를 입력하는 것은 불가능합니다.
        타블렛의 자동완성 알고리즘이 사용하는 단어들과 각 단어들의 출현 빈도가 주어질 때,
            주어지는 긴 문자열을 입력하기 위해 필요한 최소 타이핑 수를 계산하는 프로그램을 작성하세요.
    입력
        입력의 첫 줄에는 테스트 케이스의 수 C(1<= C <=10)가 주어집니다.
        각 테스트 케이스의 첫 줄에는 사전에 포함된 단어의 수 N (1 <=N <= 10000)과
            입력할 단어의 수 M (1 <= M <= 20000)이 주어집니다.
        그 후 N 줄에는 한 줄에 하나의 문자열과 정수로 사전에 포함된 단어와
            해당 단어의 출현 빈도가 사전 순서와 무관하게 주어집니다.
            같은 단어가 두번 이상 주어지는 일은 없으며, 출현 빈도는 1 과 10만 사이의 정수입니다.
        그 다음 줄에 M개의 단어로 입력할 문자열이 주어집니다. 모든 단어는 알파벳 대문자이며, 길이는 최대 10입니다.
        입력의 양이 많으므로 가능한 빠른 입력 함수를 이용하는 것이 좋습니다.
    출력
        각 테스트 케이스마다 한 줄에 모든 단어들을 입력하기 위해 필요한 최소 타자 수를 출력합니다
    제한조건
        3초, 64MB
    */
    /*힌트
        time complexity 측면
            단어가 1만개, 입력이 2만개므로 상당히 크다.
                입력의 상당한 시간이 걸릴 수 있으므로, O(n^2)미만의 속도가 되어야 할 것이다.
            빠른 문자열 입력
                1. cin과 string을 이용한 무지성 입력
                2. scanf로 입력받기, 공백까지만 입력받으므로 이걸 이용하자
                3. scanf로 입력받으면서 동시에 trie에 넣어버리기
        알고리즘
            trie를 이용한 방법
                complexity 추정
                    mem complexity: 문자의 최대길이는 개수(1만)*길이(10)*child배열의길이와 다른 원소(26+1)*4바이트 = 10.8MB
                    time complexity: 길이가 10이므로 input, find는 10밖에 소모하지 않는다.
                                    입력이 많으므로 1억회라고 가정해도, 각 입력당 1000회 수행할 수 있다.
                설명
                    현재노드에서 자동완성을 한다면 반환할 원소의 terimal과 priority를 저장하도록 하여, 자동완성을 용이하게 한다.
                        각각 autoTerminal, autoPriority로 저장한다.
                방법
                    노드
                        children은 알파벳 대문자에 대해 저장한다.
                        terminal을 0과1이 아닌, 각 원소의 idx로 한다.
                        priority를 저장한다.
                        현재 노드에서 자동완성할 시 반환되는 단어의 terminal을 autoTerminal로, priority를 autoPriority로 저장한다.
                    입력
                        trie의 입력을 수행한다.
                        입력을 수행하면서, priority를 비교하며 terminal과 priority를 갱신한다.
                            갱신: priority>autoPriority인 경우, priority=autoPriority 면서 사전순으로 우선일경우
                    탐색
                        trie의 탐색을 수행한다. 단어가 없으면 NULL반환
                    자동완성 탐색
                        탐색을 수행하며, terminal = autoTerminal이면 , 지나온 node의 갯수 + 1(탭) 반환
                        만약 단어가 없다면 20 반환 (단어의 최대 길이가 10이므로 항상 무시된다)
                complexity 계산
                    mem complexity: 1만 * 10 * 원소의개수(26+3)*4바이트 = 11.6MB
                    time complexity: O(M+N)
                        trie 생성: N*단어의길이(10)*단어비교(10) = O(N), N=단어의 개수
                        자동완성 탐색: M*단어의길이(10) = O(M), M=입력의개수
    */
    /*아이디어 1
        설명:
            힌트-알고리즘-trie를 이용한 방법
            현재노드에서 자동완성을 한다면 반환할 원소의 terimal과 priority를 저장하도록 하여, 자동완성을 용이하게 한다.
                각각 autoTerminal, autoPriority로 저장한다.
        성능:
            time complexity: O(K(M+N)+L), M=입력의 갯수, N=단어의 갯수, K=입력문자의 최대길이, L = 타이핑할 문자열의 전체 길이
            mem complexity: O(N)
        한계:
            c-style로 배열을 선언했는데, vector를 이용하는 방법은 없는가?
        피드백:
            136ms
            재귀할때 return 까먹지 말자
            c-style로 배열을 선언하면 반드시 초기화를 해야한다.
        책의 아이디어:
            단어를 우선순위, 사전순으로 정렬을 해두면, 먼저 입력된 자동완성이 항상 추천됨을 보장한다. -> 152ms
            책의 아이디어는 trie를 구현하는것이 간단하다는 점에 있고,
                나의 아이디어는 다양한 우선순위(정렬로 해결하기힘든경우)에도 적용할 수 있다.
                물론 대부분의 경우는 비교를 먼저해서 정렬하면 되긴 한다. 나의 경우만이 가능한 케이스는 드물 듯
                이 경우 time complexity는 O(KNlgN + KM + L)
    */
    // Sol
    int testCase;
    cin >> testCase;
    while (testCase--) {
        auto ret = SOLONG_Main();
        cout << ret << endl;
    }
}
void SOLONG_test() {
    /* sample_input
7
7 8
ALL 4
AND 3
FISH 8
FOR 6
SO 4
THANKS 9
THE 9
SO LONG AND THANKS FOR ALL THE FISH
7 8
ALL 4
AND 5
FISH 3
FOR 6
SO 8
THANKS 1
THE 2
SO LONG AND THANKS FOR ALL THE FISH
4 4
AAABBBCCCDDD 8
AAABBBCCC 6
AAABBB 4
AAA 2
AAABBBCCCD AAABBBC AAAB AAABBBCCCDDDEEEFFF
3 1
AABCD 4
AAB 4
AA 4
AABCD
3 1
AAC 4
AABB 4
AAAAA 4
AAAAA
4 5
A 1
AB 2
ABC 3
ABCD 4
ABCD ABC AA BCA ABCDF
4 5
A 1
AA 2
AAA 3
AAAA 4
A AA AAA AAAA AAAAA
    */
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);
    int testCase;
    cin >> testCase;
    vector<int> answer = {28, 29, 3, 5, 2, 19, 17};
    for (int i = 0; i < testCase; i++) {
        auto ret = SOLONG_Main();
        if (ret != answer[i]) {
            cout << "testCase " << i << " is failed, answer is " << answer[i] << ", ret is " << ret << endl;
        } else {
            cout << "testCase " << i << " is Success!" << endl;
        }
    }
}

int main(void) {
    // clock_t start,end;
    // start=clock();
    SOLONG_print();
    // SOLONG_test();  // run with F5(debug mode)
    // end=clock();;
    // cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}