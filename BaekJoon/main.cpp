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
    third
      graph를 time 기준으로 정렬
        각 vertex에서 lowest time edge 만을 이용하여 dijkstra
          이 dijkstra는 second에서 한 것과 동일한 dijkstra
          lowest time edge만 넣은 행렬 하나 생성해서 이용
        목적지(N)에 데이터가 갱신되었는지 확인후 다시 dijkstra
        매번 초기화되는것
          graph 원본, lowest time edge만을 저장한 행렬, 행렬이 몇개 저장되었는지 체크하는 cnt(cnt==0->break)
        초기화 되지 않고 누적되는 것
          cost_V행렬
  */
//input
  int N,M,K,A,B,C,D;
  cin>>N>>M>>K; // #vertex, max Cost, #edge
  vector<map<int,pair<int,int>>> graph(N+1); // time,dest,money
  for(int i=0;i<K;i++){
    cin>>A>>B>>C>>D; //from,dest,money,time
    graph[A].insert({D,{B,C}});
  }
//prepare
  vector<map<int,int>> cost_V(N+1);  //first==time, second==money
  priority_queue<plan,vector<plan>,greater<plan>> pq; //time,money, dest
//calc
  while(true){
    //prepare
    int cnt(0);
    vector<pair<int,pair<int,int>>> tmpGraph(N+1);  //lowest edge를 저장한 행렬
    for(int i=1;i<=N;i++){
      if(!graph[i].empty()){
        tmpGraph[i]=*graph[i].begin();
        graph[i].erase(graph[i].begin());
        cnt++;
      }
    }
    if(cnt==0){ 
      cout<<"Poor KCM"<<endl;
      return;
    }
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
        cout<<tmp.money<<endl;
        return;
      }
      if(tmp.money+tmpGraph[tmp.dest].second.second<=M){
        pq.push({tmp.time+tmpGraph[tmp.dest].second.first,tmp.money+tmpGraph[tmp.dest].second.second,tmpGraph[tmp.dest].first});
      }
    }
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