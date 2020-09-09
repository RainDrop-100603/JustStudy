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

void FloydWarshall(const vector<map<int,int>>& graph, vector<vector<int>>& cost_V,vector<vector<int>>& prev_V){ //음수 가중치도 허용한다, DP 이용
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
  int num_V(cost_V.size()),INF(INT32_MAX),NIL(-1);  //there is no "-1" vertex, so NIL==-1 
  //initialize
  for(int i=0;i<num_V;i++){ 
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
  //Dynamic Programing
  for(int mid=0;mid<num_V;mid++){
    for(int dest=0;dest<num_V;dest++){
      for(int from=0;from<num_V;from++){
        if(cost_V[mid][dest]!=INF&&cost_V[from][mid]!=INF&&cost_V[from][mid]+cost_V[mid][dest]<cost_V[from][dest]){
           cost_V[from][dest]=cost_V[from][mid]+cost_V[mid][dest];
           prev_V[from][dest]=mid;
         }
      }
    }
  }
}

void BK1956(){  // Dijkstra
  /*
  문제조건
    첫째 줄에 V와 E가 빈칸을 사이에 두고 주어진다. (2<=V<=400, 0<=E<=V*(V-1)) 다음 E개의 줄에는 각각 세 개의 정수 a, b, c가 주어진다.
     a번 마을에서 b번 마을로 가는 거리가 c인 도로가 있다는 의미이다. (a->b임에 주의) 거리는 10,000 이하의 자연수이다.
    자료형: 최대크기= #edge*maxTime(or cost)=400*400*10,000=1,600,000,000: int
    시작점으로 돌아오는 cycle을 찾아라 
  first
    Dijkstra 반복
    BellmanFord 사용시 이득 없음
    FloydWarshall : 쓸만한듯
      vertex간 거리를 저장하는 table에서, A(ij)+A(ji): j=1~#edge == i로 돌아오는 모든 사이클 

    

  */
//input
  int V,E,a,b,c;
  cin>>V>>E; // #vertex, #edge
  vector<map<int,int>> graph(V+1); // dest, money, time
  for(int i=0;i<E;i++){
    cin>>a>>b>>c; //from,dest,cost
    auto ans=graph[a].insert({b,c}); //dest,money,time
    if(!ans.second&&ans.first->second>c){
      ans.first->second=c;
    }
  }
//prepare
  vector<vector<int>> cost_V(V+1,vector<int>(V+1));
  vector<vector<int>> prev_V(V+1,vector<int>(V+1));
//calc
  FloydWarshall(graph,cost_V,prev_V);
//output
  int result=INF;
  for(int i=0;i<=M;i++){
    result=min(result,table[i][N]);
  }
  if(result==INF){
    cout<<"Poor KCM\n";
  }else{
    cout<<result<<"\n";
  }
  
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  int T;
  cin>>T;
  while(T--){
    BK10217();
  }
  return 0;
}