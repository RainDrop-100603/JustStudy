#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Boggle, BruteForce, 런타임 에러 발생 Mem over?
void BoggleRandInput(vector<char>& probTable, vector<string>& wordArr);
void BoggleInput(vector<char>& probTable, vector<string>& wordArr);
vector<int> BoggleAlgo(vector<char>& probTable, vector<string>& wordArr);
void BoggleGame();

//picnic, BruteForce, 조합에서의 중복 제거 방법 
void PicnicInput(vector<vector<bool>>& friendTable);
int PicnicAlgo(vector<vector<bool>>& friendTable,vector<bool>& toBePush);
void Picnic();

//BoardCover, BruteForce, timeComplexity보다 더 빨리 동작하는 경우
void BoardCoverInput(vector<vector<bool>>& boardTable);
bool BoradCoverNoAns(vector<vector<bool>>& boardTable);
int BoardCoverAlgo(vector<vector<bool>>& boardTable);
void BoardCover();

//ClockSync, BruteForce, 횟수가 제한되어 있을경우, 조합
void ClockSyncInput(vector<int>& clockArr);
int ClockSyncAlgo(vector<int>& clockArr,vector<vector<int>>& switchArr,int nowSwitch);
void ClockSync();

//QuadTree, Divide&Conquer, iterator을 활용하여 전달인자 간소화 
void QuadTreeInput(string& treeData);
string QuadTreeAlgo(string::iterator& iter);
void QuadTree();

//Fence, Divide&Conquer, Bk6549, stack(19장), line sweeping(15장), 상호배타적 집합(25장)
void FenceInput(vector<int>& fenceData);
int FenceAlgo(vector<int>& fenceData,int left, int right);
void Fence();

//fanMeeting, Divide&conquer, bitmask, 미완성 
// void FanmeetingInput(longNum& member,longNum& fan);
// int FanmeetingAlgo(longNum& member, longNum& fan);
// void Fanmeeting();

//WildCard, DP, Sol을 한번에 생성하려하지말고 천천히하자: 완전탐색 -> 겹치는부분 DP
void WildcardInput(string& wildcard,vector<string>& fileArr);
bool Wildcard_match(string& wildcard,string& file, int w_idx,int f_idx,vector<vector<char>>& DP);
bool Wildcard_match2(string& wildcard,string& file, int w_idx,int f_idx,vector<vector<char>>& DP);  //match에서 develop
vector<string> WildcardAlgo(string& wildcard,vector<string>& fileArr);
void Wildcard();

//JLIS, DP, 최적화가 아닌 메모제이션
void JoinedLISInput(vector<int>& arrA,vector<int>& arrB);
bool joinedLIS_Afirst(vector<int>& arrA,vector<int>& arrB,int idxA,int idxB);
int JoinedLISAlgo_1(vector<int>& arrA,vector<int>& arrB);
int JoinedLISAlgo_3(vector<int>& arrA,vector<int>& arrB);
int JoinedLISAlgo_2(vector<int>& arrA,vector<int>& arrB,int idxA, int idxB,vector<vector<int>>& DP);
void JoinedLIS();

//PI 외우기, DP 최적화
void PImem_Input(string& s);
int PImem_hard(string& numbers,int start,int len);
int PImem_Algo(string& numbers, vector<int>& DP, int start);
void PImem();

//Quantization, DP 최적화, 간단한 처리를 통해 DP를 사용 가능하게 만들었다. 부분합의 이용
void Quantization_Input(vector<int>& number,int& quantRange);
void Quantization_DP_A(vector<int>& number, vector<vector<int>>& DP_A);
void Quantization_DP_A_2(vector<int>& number, vector<vector<int>>& DP_A);
int Quantization_DP_B(vector<int>& number, vector<vector<int>>& DP_A,vector<vector<int>>& DP_B,int start,int depth);
int Quantization_Algo(vector<int>& number,int quantRange);
void Quantization();



