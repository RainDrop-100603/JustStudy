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

void FloydWarshall(const vector<map<int,int>>& graph, vector<vector<int>>& cost_V,vector<vector<int>>& prev_V){
  /*
  Floyd-Warshall Algorithm
    DP table 두개를 이용하는 Algorithm
      1. Vertex간 최단거리를 저장하는 table A
      2. 최단거리일 때, 도착 Vertex의 직전 Vertex를 저장하는 table B
      # table의 갱신: 경유하는 vertex가 0개 ~ #vertex 개 일때까지 차례로 DP
        ==모든 vertex를 경유 가능하도록 추가할 때까지
    A(i,j)=i에서 j로 가는 최단거리 cost
    B(i,j)=i에서 j로 가는 최단거리일때, j의 직전 vertex
    DP(x)->DP(x+1)에서 vertex k가 경유지로 추가될 경우, Edge(K,dest)
      A(i,dest)=min(A(i,dest),A(i,k)+Edge(k,dest))
      B(i,dest)=k, iff A(i,dest) is changed
  */
  int num_V(cost_V.size()),INF(INT32_MAX),NIL(-1);  //there is no vertex: -1, so NIL==-1  
  for(int i=0;i<num_V;i++){ //initialize
    for(int j=0;j<num_V;j++){ //default value
      cost_V[i][j]=INF;
      prev_V[i][j]=NIL;
    }
    cost_V[i][i]=0; //vertex i to i == 0
    for(auto& ele: graph[i]){ //default Edge,first==dest, second==cost
      cost_V[i][ele.first]=ele.second;
      prev_V[i][ele.first]=i;
    }
  }
}

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
  int INF=6000*10000+1;   // cost의 최댓값 +1
  vector<long long> cost_V(N+1);  // cost
//calc
  int ans=BellmanFord(graph,cost_V,1,INF);
//output
  if(ans){
    cout<<-1<<"\n";
  }else{
    for(int i=2;i<=N;i++){
      if(cost_V[i]==INF){
        cout<<-1<<"\n";
      }else{
        cout<<cost_V[i]<<"\n";
      }
    }
  }
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  BK11404();
  return 0;
}