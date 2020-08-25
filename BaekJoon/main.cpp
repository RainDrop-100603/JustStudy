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

//#include "GoodFunction.h"

using namespace std;
int DFS1753(vector<vector<pair<int,int>>>& graph,int from,int to){
  int N=graph.size(); 
  int M=graph[0].size();
  int cnt(1);
  deque<pair<bool,pair<int,int>>> dq; //벽뚫 가능 여부, x, y
  dq.push_back({true,{0,0}});
  graph[0][0]=-2;     // -3 벽에 방문, 1 벽, 0 미방문, -1 벽뚫고방문, -2 방문불가==그냥 방문 (그냥 방문이 벽뚫고 방문이랑 같거나 빠르다면 그냥이 우선된다.)
  while(!dq.empty()){
    int sz=dq.size();
    if(graph[N-1][M-1]<0){
      break;
    }
    for(int k=0;k<sz;k++){
      auto p=dq.front();
      dq.pop_front();
      int x(p.second.first),y(p.second.second);
      bool brk(p.first);
      if(x>0){visit(graph,dq,x-1,y,brk);}
      if(x<N-1){visit(graph,dq,x+1,y,brk);}
      if(y>0){visit(graph,dq,x,y-1,brk);}
      if(y<M-1){visit(graph,dq,x,y+1,brk);}
    }
    cnt++;
  }
  if(graph[N-1][M-1]>=0){
    cnt=-1;
  }
  return cnt;
}
void BK1753(){
//input
  int V,E,K,u,v,w;
  cin>>V>>E>>K; // V: #vortex, E: #edge, K: start V
  vector<vector<pair<int,int>>> graph(V,vector<pair<int,int>>()); // V[i]'s element =pair : i에서 p.first 로가는 가중치 p.second의 edge
  for(int i=0;i<E;i++){
    cin>>u>>v>>w;
    graph[u].push_back({v,w});
  }
//prepare
//calc
  int result=BFS6(graph);
//output
  cout<<result;
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  BK2206();
  
  return 0;
}