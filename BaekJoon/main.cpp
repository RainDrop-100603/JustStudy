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
        구현에서 에러떠서 포기 
    fourth  - 인터넷 참고_memOver
      DP table : A[i][j]=K  : i에 j cost로 도달하는데 걸린 시간 

  */
//input
  int N,M,K,A,B,C,D;
  cin>>N>>M>>K; // #vertex, max Cost, #edge
  vector<vector<pair<int,pair<int,int>>>> graph(N+1); // dest, money, time
  for(int i=0;i<K;i++){
    cin>>A>>B>>C>>D; //from,dest,money,time
    graph[A].push_back({B,{C,D}}); //dest,money,time
  }
//prepare
  int INF=10000*1000+1;  //current max time+1, #edge*time+1
  vector<vector<int>> cost_V(N+1,vector<int>(M+1,INF));  //cost[i][j]=k : 1 to i with cost:j time:k
  priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int>>,greater<pair<pair<int,int>,int>>> pq; //money,time,dest
//calc
  pq.push({{0,0},1});
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    int cost(tmp.first.first),time(tmp.first.second),from_V(tmp.second);
    cost_V[from_V][cost]=time; //갱신
    for(auto& ele:graph[from_V]){
      int newCost(cost+ele.second.first),newDest(ele.first),newTime(time+ele.second.second);
      if(newCost<=M&&cost_V[newDest][newCost]>newTime){
        pq.push({{newCost,newTime},newDest});
      }
    }
  }
//output
  int minTime(INF);
  for(auto& ele:cost_V[N]){
    minTime=min(minTime,ele);
  }
  if(minTime==INF){
    cout<<"Poor KCM"<<endl;
  }else{
    cout<<minTime<<endl;
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