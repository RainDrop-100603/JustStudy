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
struct plan{
  int time;
  int money;
  int dest;
  bool operator>(const plan& a) const{
    return time>a.time;
  }
  int cmpLess(const pair<const int,int>& a) const{ //1=less, -1=big, 0=not anyone
    if(money<=a.second&&time<=a.first){
      return 1;
    }else if(money>a.second&&time>a.first){
      return -1;
    }else{
      return 0;
    }
  }
};
void BK10217(){  // Dijkstra
  /*
  Dijkstra Algorithm
    first_memOver: 대부분의 정보를 모두 저장해버렸기 때문 -> 일정수준 이전 정보는 삭제해버리는 DP 이용 필요
      lowest time이 목표
      lowest time dijkstra 
        if timeover: backtracking?
      DP table(cost_V)에 여러 data를 저장하자
        갱신이 아닌 누적 저장을 이용
          새로운 값이 들어오면 기존의 모든 값과 비교 
            money와 time이 모두 기존값보다 낮거나 같다 -> 해당 기존값 삭제 후 저장
            의외의 경우는 새로운 값도 저장 
        새로운 자료형 정의
          time과 money를 동시에 비교하여 가장 낮은 값을 priority queue에 저장
    second_memOver: 여전히 많은 정보가 stack과 table에 저장된다.
      오직 time을 기준으로만 비교 -> 가장 먼저 목적지 도착하면 출력(cost는 stack 입력 전에 확인하므로)
  */
//input
  int N,M,K,A,B,C,D;
  cin>>N>>M>>K; // #vertex, max Cost, #edge
  vector<vector<pair<int,pair<int,int>>>> graph(N+1); // dest, time, money
  for(int i=0;i<K;i++){
    cin>>A>>B>>C>>D; //from,to,money,time
    graph[A].push_back({B,{D,C}});
  }
//prepare
  vector<map<int,int>> cost_V(N+1);  //first==time, second==money
  priority_queue<plan,vector<plan>,greater<plan>> pq; //time,money, dest
//calc
  pq.push({0,0,1});
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    bool isContinue(false);
    for(auto& ele:cost_V[tmp.dest]){
      int flag=tmp.cmpLess(ele);
      if(flag==1){
        cost_V[tmp.dest].erase(ele.first);
      }else if(flag==-1){
        isContinue=true;
        break;
      }
    }
    if(isContinue){
      continue;
    }
    cost_V[tmp.dest].insert({tmp.time,tmp.money}); //갱신
    if(tmp.dest==N){
      break;
    }
    for(auto& ele:graph[tmp.dest]){
      if(tmp.money+ele.second.second<=M){
        pq.push({tmp.time+ele.second.first,tmp.money+ele.second.second,ele.first});
      }
    }
  }
//output
  if(!cost_V[N].empty()){
    cout<<cost_V[N].begin()->first<<endl;
  }else{
    cout<<"Poor KCM"<<endl;
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