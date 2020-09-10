#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
#include <list>
#include <deque>
#include <queue>

//#include "GoodFunction.h"

using namespace std;

int graph[16][16];
int DP[16][1<<16];  //current, visited
int N, END;  //#vertex, 모든경로 방문: (1<<N)-1

int TSP(int current,int visited){
  if(visited==END){return;}
  for(int i=1;i<N;i++){
    if(visited&(1<<i)||graph[current][i]==0){
      continue;
    }
    int& tmp=DP[i][visited+(1<<i)];
    if(tmp==0){
      tmp=DP[current][visited]+graph[current][i];
    }else{
      tmp=min(tmp,DP[current][visited]+graph[current][i]);
    }
    TSP(i,visited+(1<<i));
  }
}
void BK2098(){  // Traveling Salesman Problem (TSP)
  /*
  전역변수 영역

  문제
    첫째 줄에 도시의 수 N이 주어진다. (2 ≤ N ≤ 16) 다음 N개의 줄에는 비용 행렬이 주어진다. 각 행렬의 성분은 1,000,000 이하의 양의 정수이며, 갈 수 없는 경우는 0이 주어진다. 
    W[i][j]는 도시 i에서 j로 가기 위한 비용을 나타낸다.
    항상 순회할 수 있는 경우만 입력으로 주어진다.
  Priority Queue에 cost, 경로를 저장 -> 최대 15!*int*2 필요->mem over
  DP를 통해 원점에서 시작하여 끝 경로까지
    visited==END -> return;
    for(int i=0;i<N;i++); if(visited&(1<<i));
      graph[current][i]==0 -> continue;
      graph[current][i]!=0 -> DP[i][visited+(1<<i)]=min(this,DP[current][visited]+graph[current][i]); TSP(i,visited+(1<<i));
  */
//input
  int prev(0),now,len,cnt;
  cin>>N; // #연산
  cin.get();
  string s;
  for(int i=0;i<N;i++){
    cnt=0;
    prev=0;
    getline(cin,s);
    len=s.length();
    for(int j=0;j<len;j++){
      if(s[j]==' '){
        now=j;
        graph[i][cnt]=stoi(s.substr(prev,now-prev));
        cnt++;prev=now;
      }
    }
    graph[i][cnt]=stoi(s.substr(prev,len-prev));
  }
//prepare
  END=(1<<N)-1;
//calc
  TSP(0,1<<0);
//output
  int answer=INT32_MAX;
  for(int i=1;i<N;i++){
    if(graph[i][0]!=0&&DP[i][END]+graph[i][0]!=0){
      answer=min(answer,DP[i][END]+graph[i][0]);
    }
  }
  cout<<answer<<endl;
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  BK2098();
  return 0;
}