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


