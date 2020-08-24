#ifndef __JUSTSOL_H__
#define __JUSTSOL_H__


#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <list>

using namespace std;

#include "GoodFunction.h"

//just Sol
vector<vector<int>> Remainder_nCr(int n, int M); //nCn까지 구할 수 있는 파스칼 삼각형, 각 원소에 mod_M(%M)을 취했다. nCr이 엄청나게 커질경우, mod는 파스칼 삼각형으로 구해야 한다. 나눗셈이 있을경우 mod에 대한 결합법칙은 성립하지 않기때문.
bool ChkDuplicate(int x, int depth, int* num); //num의 depth-1번째 까지 수에서, x와 겹치는 것이 있는지 확인
void PrintAllCombi(int n, int r, int depth, int* num); //nCr 조합, depth번째 수, 수를 저장하는 num, digit=0: 가장 앞에 수(167:digit 0 -> 1);
void PrintAllCombi2(int n, int r, int depth, int* num, int start); //N과 M(2) 문제 
void PrintAllCombi3(int n, int r, int depth, int* num); //N과 M(3) 문제 
void PrintAllCombi4(int n, int r, int depth, int* num, int start); //N과 M(4) 문제
int N_Queen(int N,vector<bool>& colQueen,vector<bool>& lineRDQueen,vector<bool>& lineLDQueen, int row); //N_Queen문제, count는 N번째 Queen을 말함 
bool Sdoku(int sdoku[9][9],vector<pair<int,int>>& empty,int filledNum,int emptySize); //filledNum은 채워진 개수, emptySize까지 가면 true, 아니면 false 반환 
void GetMaxMin(vector<int>& arrayV,int* AddSubMulDiv,int& max,int& min,int idx,int sum); //idx번째까지의 결과(sum)와 idx+1번째 수를 계산. idx=arrayV.len()이면 max min 체크
void GetLowGap(int& gap,vector<vector<int>>& table,vector<int>& startTeam,vector<int>& linkTeam,int idx); //idx번째 선수를 각 팀에 배분. 배분이 끝나면 gap 을 계산하고 기존 gap보다 낮을시 갱신 

// 자료형 class 구현
//Queue
//PriorityQueue
//LinkedList
//LinkedList2
//D_LinkedList
//QueueLinkedList
//DequeLinkedList
//DequeLL2
//RoundQueue_LL

//정답오류, 원인?
void BK6549(vector<vector<long long>>& v, int start, int end);  //[start,end)
//정답은 맞다, 원본 데이터를 건드리면서 길이도 매번 측정했기 때문에 시간이 오래 걸린다.
long long popFunc(vector<int>& v); //key보다 큰 값을 key로 다듬으며, tmpMax 반환 
void BK6549_Stack(int times);
//정답. Stack, 원본데이터는 그대로 두고, 추가된 stack에 간략하게 정보를 저장한다.
long long PopFunc2(vector<int>& v,vector<int>& stack, int idx);
void BK6549_Stack2(long long times);
//정답. SegmentTree, 각 node는 범위 내의 min 값을 저장 
int BK6549_ST_init(vector<int>& a, vector<int>& tree, int node, int start, int end); //[start,end] 범위 ST,node는 min값의 key 
vector<int> BK6549_SegmentTree(vector<int>& a); //arr a를 segment Tree로 
int BK6549_ST_min(vector<int> &a, vector<int> &tree, int node, int start, int end, int left, int right);  //[left,right]의 min 의 key
long long BK6549_ST_MaxSum(vector<int> &a, vector<int> &tree, int start, int end, int left, int right); //[left,right]의 max value
void printTree(vector<int> &tree);// Tree 인쇄, 디버그용  
void BK6549_ST(long long times);

//Line Sweep
struct Point{
  int x,y;
  Point(){}
  Point(int x, int y):x(x),y(y){}
  bool operator< (const Point& p) const{if(y==p.y){return x<p.x;}else{return y<p.y;}}
};
bool cmpX(const Point& p1, const Point& p2);
int dist2(const Point& p1, const Point& p2);
void BK2261_3_H_LineSweeping(); //scanf를 사용하므로 유의 

//이분탐색
void BK1920();
void BK10816_1();
void BK10816_2();
void BK1654();  //unsigned int가 왜 사용되었는지 chk
void BK2805();
void BK2110();
void BK1300_H(); //기저에 깔린 법칙
void BK12015_H(); //기저에 깔린 법칙

//우선순위 큐
void BK11279();
void PrintIter(map<int,int>::iterator& iter,map<int,int>& tree);
void BK11286();
void BK1655();

//동적 계획법 2
bool cmpPairX(const pair<int,int>& p1,const pair<int,int>& p2);
void BK2293_Memover();
void BK2293_Memover2();  //table에 유효한 값만 저장하자 
void BK2293_3();
void BK11066();
void BK11049();
int DFS(vector<vector<int>>& table, vector<vector<int>>& movTable, int i, int j,int row,int col);
void BK1520_H_DFS();
void BK7579_v2();
void BK10942();

//DFS & BFS
void DFS(vector<vector<int>>& graph, vector<bool>& chk, int from);
void BFS(vector<vector<int>>& graph, vector<bool>& chk, int from);
void BK1260(); //DFS, BFS 기초
void BK2606();
int BFS(vector<vector<bool>>& graph, pair<int,int> p);
void BK2667();
void BK1012();
int BFS2(vector<vector<bool>>& graph, pair<int,int> p); //depth 체크 기능 추가
void BK2178();
int BFS3(vector<vector<int>>& graph);
void BK7576();


#endif