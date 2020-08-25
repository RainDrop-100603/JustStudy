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
int Dijkstra(vector<map<int,int>>& graph,int from,int to){
  int V=graph.size(); // #vertex
  vector<int> cost(V);
  int result;
  map<int,int> tree;  
  multimap
  tree.insert({from,0});

  while(!tree.empty()){
    int now=dq.
  }
 

  return result;
}
void BK1753(){
//input
  int V,E,K,u,v,w;
  cin>>V>>E>>K; // V: #vortex, E: #edge, K: start V
  vector<map<int,int>> graph(V,map<int,int>()); // V[i]'s element =pair : i에서 p.first 로가는 가중치 p.second의 edge, 중복 간선은 최저치 빼고 삭제
  for(int i=0;i<E;i++){
    cin>>u>>v>>w;
    auto ans=graph[u].insert({v,w});
    if(!ans.second){
      if(ans.first->second>w){
        ans.first->second=w;
      }
    }
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