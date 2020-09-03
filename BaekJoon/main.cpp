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

void BK11404(){  // Floyd-Warshall Algorithm, 음수 가중치도 허용한다, DP 이용
  /*
  Floyd-Warshall Algorithm
    DP table 두개를 이용하는 Algorithm
      1. Vertex간 최단거리를 저장하는 table
      2. 최단거리일 때, 각 Vertex의 직전 Vertex를 저장하는 table
      # table의 갱신: 경유하는 vertex가 0개 ~ #vertex-1 개 일때까지 차례로 DP
  */
//input
  int N,M,A,B,C;
  cin>>N>>M; // #교차로(vertex), #도로(edge)
  vector<map<int,int>> graph(N+1); // V[i]'s element =pair : i 와 p.first사이의 가중치 p.second의 경로, 중복 간선은 최저치 빼고 삭제
  for(int i=0;i<M;i++){
    cin>>A>>B>>C;
    auto ans= graph[A].insert({B,C});
    if(!ans.second){
      if(ans.first->second>C){
        ans.first->second=C;
      }
    }
  }
//prepare
  int INF=INT32_MAX;
  vector<vector<int>> cost_V(N+1,vector<int>(N+1));  // cost
  vector<vector<int>> prev_V(N+1,vector<int>(N+1));  // prev, prev[i][j]=k means the path is (i, ..., k, j) 
//calc
  FloydWarshall(graph,cost_V,prev_V);
//output
  for(int i=1;i<=N;i++){
    for(int j=1;j<=N;j++){
      if(cost_V[i][j]==INF){
        cout<<0<<' ';
      }else{
        cout<<cost_V[i][j]<<' ';
      }
    }
    cout<<endl;
  }
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  BK11404();
  return 0;
}