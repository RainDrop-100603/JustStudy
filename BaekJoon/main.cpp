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
void BK1753(){
//input
  int V,E,K,u,v,w;
  cin>>V>>E>>K; // V: #vortex, E: #edge, K: start V
  vector<map<int,int>> graph(V+1,map<int,int>()); // V[i]'s element =pair : i에서 p.first 로가는 가중치 p.second의 edge, 중복 간선은 최저치 빼고 삭제
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
  vector<int> chk(V);  // priority Queue에는 같은 vertex를 중복해서 넣을 수 있다. 이때 chk를 확인하여 이미 경로탐색을 했다면, 다시 경로탐색을 하지 않고 넘어간다.
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq; //first=cost, second=key
//calc
  pq.push({0,K});
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    int cost(tmp.first),key(tmp.second);
    if(chk[key]){
      continue; //이미 했다면 넘어간다.
    }
    chk[key]=cost;
    for(auto& ele: graph[key]){
      pq.push({cost+ele.second,ele.first});
    }
  }
//output
  for(int i=1;i<=V;i++){
    if(i==K){
      cout<<chk[i]<<"\n";
    }else if(!chk[i]){
      cout<<"INF\n";
    }else{
      cout<<chk[i]<<"\n";
    }
  }
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  BK1753();
  
  return 0;
}