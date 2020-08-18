#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
#include <list>

//#include "GoodFunction.h"

using namespace std;
void DFS(map<int,vector<int>>& graph, map<int,bool>& chk, int from){ 
  auto iter=chk.find(from);
  if(iter->second){
    return;
  }
  printf("%d ",from);
  iter->second=true;
  for(auto& ele:graph.find(from)->second){
    DFS(graph,chk,ele);
  }
  // while(!graph.fin.empty()){
  //   DFS(graph,chk,graph[from].front());
  //   graph[from].pop_front();
  // }
}
void BFS(map<int,vector<int>>& graph, map<int,bool>& chk, int from){
  list<int> deque;
  deque.push_back(from);
  chk.find(from)->second=true;
  while(!deque.empty()){
    from=deque.front();
    deque.pop_front();
    printf("%d ",from);
    for(auto& ele2:graph.find(from)->second){
      if(!chk.find(ele2)->second){
        deque.push_back(ele2);
        chk[ele2]=true;
      }
    }
  }
}
void BK1260(){
//input
  int N,M,V,key,value;  //팰린드롬: 앞뒤를 뒤집어도 똑같은 문자열 
  scanf("%d %d %d",&N,&M,&V); //N: #node,M: #edge, V: start node
  map<int,vector<int>> graph;   //graph[i] 의 ele: i node와 연결된 node의 list
  map<int,bool> chk;  //chklist
  for(int i=0;i<M;i++){
    scanf("%d %d",&key,&value);
    auto ans=graph.insert(make_pair(key,vector<int>()));
    ans.first->second.push_back(value);
    if(ans.second){
      chk.insert(make_pair(key,false));
    }
  }
//prepare
  for(auto& ele:graph){
    sort(ele.second.begin(),ele.second.end());
  }
//calc
  DFS(graph,chk,V);
  printf("\n");
  for(auto& ele:chk){
    ele.second=false;
  }
  BFS(graph,chk,V);

//output
  // for(auto& ele:pO){
  //   printf("%d ",ele);
  // }printf("\n");
  // for(auto& ele:pE){
  //   printf("%d ",ele);
  // }printf("\n");

}
int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
//   int N;
//   scanf("%d",&N);
//   while(N--){
    BK1260();
//  }
  
  return 0;
}