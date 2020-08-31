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

void BK1504(){  //Dijkstra, 1과 N이 거쳐야 하는 경로 두 경로중 하나일 때를 고려 
  /*
    시작 정점(1)에서 마지막 정점(V)으로 이동, 양방향 경로, 목표지점 두곳 반드시 통과
    각 vertex의 원소는 4개, 목표지점을 00개, 01개, 10개, 11개를 통과한 것을 원소로 하자 : level 이라 명명
    Dijkstra Algo 이용시, 각 3개에 대해 모두 적용 
  */
//input
  int V,E,u,v,w,obj1,obj2;
  cin>>V>>E; // V: #vortex, E: #edge
  vector<map<int,int>> graph(V+1); // V[i]'s element =pair : i 와 p.first사이의 가중치 p.second의 양방향 경로, 중복 간선은 최저치 빼고 삭제
  for(int i=0;i<E;i++){
    cin>>u>>v>>w;
    auto ans=graph[u].insert({v,w});
    auto ans2=graph[v].insert({u,w}); //양방향
    if(!ans.second){
      if(ans.first->second>w){
        ans.first->second=w;
        ans2.first->second=w;
      }
    }
  }
  cin>>obj1>>obj2;  //목표지점
//prepare
  vector<vector<int>> chk(V+1,vector<int>(4,-1));  // priority Queue에는 같은 vertex를 중복해서 넣을 수 있다. 이때 chk를 확인하여 이미 경로탐색을 했다면, 다시 경로탐색을 하지 않고 넘어간다.
  priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq; //first=cost, second.first=key, second.second= key's level(00 01 10 11)
//calc
  pq.push({0,{1,0}});
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    int cost(tmp.first),key(tmp.second.first),level(tmp.second.second);
    if(chk[key][level]!=-1){
      continue; //이미 했다면 넘어간다.
    }
    if(key==obj1&&(level==0||level==2)){
      level+=1;
    }else if(key==obj2&&(level==0||level==1)){
      level+=2;
    }
    chk[key][level]=cost;
    if(chk[V][3]!=-1){break;}
    for(auto& ele: graph[key]){
      pq.push({cost+ele.second,{ele.first,level}});
    }
  }
  
//output
  cout<<chk[V][3];
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  BK1504();
  
  return 0;
}