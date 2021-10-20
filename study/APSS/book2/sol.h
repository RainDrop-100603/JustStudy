#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "classes.h"

using namespace std;
// @*: 풀었으나 참고해볼만한 문제, @*@*: 어렵게 풀었던 문제, @*@*@*: 책이나 다른 해답을 참고한 문제

// 비트마스크, combination의 이용, time complexity 구하는 것 유의
void GRADUATION_Input(int& classNum, int& classTarget, int& semesterNum, int& classLimit, vector<int>& preClass, vector<int>& semesterInfo);
vector<int> GRADUATION_getCombination(int option, int bitmaskLen, int select);
int GRADUATION_func1(int classNum, int classTarget, int semesterNum, int classLimit, vector<int>& preClass, vector<int>& semesterInfo, int classTaken, int semesterCount, int thisSemester);
string GRADUATION_Algo(int classNum, int classTarget, int semesterNum, int classLimit, vector<int> preClass, vector<int> semesterInfo);
void GRADUATION();

// @* 부분 합, greedy, 간단한 작업을 통해 mod k==0일 경우에도 동일하게 작동하도록 했다, scanf > cin > getline + substr
//  시간에 대한 테스트 수행:
//    greedy2==greedy2_opti(4.0s, O(n))>dp(4.6s, O(n))>>greedy(12.3s, O(nlgn))
//    참조형이나 벡터의 초기화값(-1이냐 -2냐 등등)은 시간에 사실상 영향을 끼치지 않았으며, 알고리즘의 효율성이 더 큰 영향을 끼쳤다.
void CHRISTMAS_Input(int& childrenNum, int& boxNum, vector<int>& boxInfo);
void CHRISTMAS_Input2(int& childrenNum, int& boxNum, vector<int>& boxInfo);
void CHRISTMAS_Input3(int& childrenNum, int& boxNum, vector<int>& boxInfo);
void CHRISTMAS_randInput(int& childrenNum, int& boxNum, vector<int>& boxInfo, int childFix, int boxFix);
int CHRISTMAS_GREEDY(vector<int>& pSum, vector<vector<int>>& modValueIdx, int childrenNum);
int CHRISTMAS_GREEDY2(vector<int>& pSum, int childreNum);
int CHRISTMAS_GREEDY2_opti(vector<int>& pSum, int childreNum);
int CHRISTMAS_DP(vector<int>& pSum, int childrenNum);
pair<int, int> CHRISTMAS_Algo(int childrenNum, int boxNum, vector<int> boxInfo);
void CHRISTMAS();

// @* 원형 연결리스트 혹은 큐 혹은 배열, 배열이 큐보다 훨씬 빠른데 이유가 무엇일까
//    가설1: 배열의 재할당의 경우 캐시를 이용하여 한번에 빠르게 옮길 수 있지만, 큐의 이동은 하나씩만 이루어져 최적화가 어렵다.
void JOSEPHUS_Input(int& num, int& move);
pair<int, int> JOSEPHUS_Algo(int num, int move);
void JOSEPHUS();

// stack을 이용한 간단한 문제
void BRACKETS2_Input(string& inputStr);
string BRACKETS2_Algo(string& inputStr);
void BRACKETS2();

// queue를 이용한 간단한 문제, unsigend int를 이용한 mod 처리
void ITES_Input(int& target, int& length);
int ITES_Algo(int target, int length);
void ITES();

// KMP search 변형문제, circular shift
void JAEHASAFE_Input(vector<string>& config);
vector<int> JAEHASAFE_getFailure(const string& str);
int JAEHASAFE_KmpSearch(const string& base, const string& target);
int JAEHASAFE_Algo(const vector<string>& config);
void JAEHASAFE();

// @* suffix arr, 사용법에 대해 참고해볼 것이 많다. 람다함수를 이용하여 구조체를 이용하지 않고 구현했다.
void HABIT_Input(string& speech, int& isHabit);
vector<int> HABIT_suffixArr(const string& str);
int HABIT_commonprefix(const string& str, int begin1, int begin2);
int HABIT_Algo(string speech, int isHabit);
void HABIT();

// @* tree, preorder, inorder, postorder, 적절한 재귀를 통해, tree를 구현하지 않고도 문제를 풀어냈다.
void TRAVERSAL_Input(int& nodeNum, vector<int>& preorderTraversal, vector<int>& inorderTraversal);
vector<int> TRAVERSAL_Algo(int nodeNum, vector<int> preorderTraversal, vector<int> inorderTraversal);
void TRAVERSAL();

// @* subtree, tree에 대한 조건/결과는 subtree에도 동일하게 적용됨을 유의하자
void FORTRESS_Input(int& fortressNum, vector<int>& fortressXpos, vector<int>& fortressYpos, vector<int>& fortressRadius);
bool FORTRESS_isSubtree(vector<int>& fortressXpos, vector<int>& fortressYpos, vector<int>& fortressRadius, int root, int now);
pair<int, int> FORTRESS_getHeights(vector<int>& fortressXpos, vector<int>& fortressYpos, vector<int>& fortressRadius, vector<int>& tree);
int FORTRESS_Algo(int fortressNum, vector<int> fortressXpos, vector<int> fortressYpos, vector<int> fortressRadius);
void FORTRESS();

// @*@*@* binary search tree(map), 시각화를 통해 문제해결의 힌트를 얻을 수 있다.
void NERD2_Input(int& applicantsNum, vector<int>& arg1Arr, vector<int>& arg2Arr);
int NERD2_Algo(int applicantsNum, vector<int> arg1Arr, vector<int> arg2Arr);
void NERD2();

// @*@*@* treap, sort-de_sort의 관계와 같이, 순차적으로 수행된 어떤작업은, 반대로 수행함으로서 원래 상태로 되돌릴 수 있다.
// treap을 이용할때, return값 조심
void INSERTION_Input(int& size, vector<int>& shifted);
vector<int> INSERTION_Algo(int size, vector<int> shifted);
void INSERTION();

// priority queue 를 통한 heap 구현
void RUNNINGMEDIAN_Input(int& seqLen, int& seqArg1, int& seqArg2);
int RUNNINGMEDIAN_Algo(int seqLen, int seqArg1, int seqArg2);
void RUNNINGMEDIAN();