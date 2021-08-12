#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;
// @*: 풀었으나 참고해볼만한 문제, @*@*: 어렵게 풀었던 문제, @*@*@*: 책이나 다른 해답을 참고한 문제 

// 비트마스크, combination의 이용, time complexity 구하는 것 유의 
void GRADUATION_Input(int& classNum,int& classTarget,int& semesterNum,int& classLimit,vector<int>& preClass,vector<int>& semesterInfo);
vector<int> GRADUATION_getCombination(int option,int bitmaskLen, int select);
int GRADUATION_func1(int classNum,int classTarget,int semesterNum,int classLimit,vector<int>& preClass,vector<int>& semesterInfo,int classTaken,int semesterCount,int thisSemester);
string GRADUATION_Algo(int classNum,int classTarget,int semesterNum,int classLimit,vector<int> preClass,vector<int> semesterInfo);
void GRADUATION();