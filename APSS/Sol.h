#include <iostream>
#include <vector>

using namespace std;

//Boggle, 런타임 에러 발생 Mem over?
void BoggleRandInput(vector<char>& probTable, vector<string>& wordArr);
void BoggleInput(vector<char>& probTable, vector<string>& wordArr);
vector<int> BoggleAlgo(vector<char>& probTable, vector<string>& wordArr);
void BoggleGame();

//picnic, 조합은 순서가 중요하지 않은데 중복을 어떻게 제거할 것인가 
void PicnicInput(vector<vector<bool>>& friendTable);
int PicnicAlgo(vector<vector<bool>>& friendTable,vector<bool>& toBePush);
void Picnic();

//BoardCover
void BoardCoverInput(vector<vector<bool>>& boardTable);
bool BoradCoverNoAns(vector<vector<bool>>& boardTable);
int BoardCoverAlgo(vector<vector<bool>>& boardTable);
void BoardCover();

//ClockSync
void ClockSyncInput(vector<int>& clockArr);
int ClockSyncAlgo(vector<int>& clockArr,vector<vector<int>>& switchArr,int nowSwitch);
void ClockSync();

