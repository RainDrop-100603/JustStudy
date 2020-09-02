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

void BK11657(){  // Bellman-Ford Algorithm, 음수 가중치도 허용한다, Edge 중심
  /*
  Bellman-Ford Algorithm

  문제에서는 음의 cycle이 발생할 경우 -1을 출력하므로 문제되지 않는다.
  V-1번 bellman-Ford실행후, V번째 실행을 한번 더 하여 변화가 있으면 -1, 없으면 출력
  출력시 INF는 -1로 출력

  지나온 경로를 다시 지나갈 수 있는가?
    무한으로 시간을 돌리는 경로라 함은 지나온 경로를 다시 지나갈 수 있음을 의미한다.
      중복 제거를 해도 된다.

  Dijkstra를 이용한 해법. 그러나 구현하지 않았다.
    graph문제 이지만, cost가 음수, 0이 가능하다.
    순환하는 고리
      합이 양수: 순환하지 않는다.
      합이 0 : 순환을 최대 한번 할 수 있다.
      합이 음수: 무한히 순환한다. 
        -> pq에 방문한 vertex를 표시하고, 재방문이 확인된다면 합이 음수인 순환하는 고리, 그 중에서도 -INF로 가는 수임을 알 수 있다.
            재방문 cost가 기존 cost보다 크면 방문하지 않기 때문에 INF로 가지는 않는다.
        -INF는 고리 밖에 있는 vertex로 갈 때, 해당 vertex도 -INF로 만든다
        -INF는 고리 내부에 있는 vertex를 재방문 해서는 안된다.
          -> 고리의 vertex를 확인하는 function을 이용해 재방문을 막자
    pq.의 구성
      cost, key, 방문한 vertex를 저장한 set,방문 불가능한 vertex를 저장한 set
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
  BK11657();
  return 0;
}