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

void Dijkstra(const vector<map<int,int>>& graph, vector<int>& cost_V, int start){
  /*
  Dijkstra Algorithm
    음수 cost 경로 불가능
    가장 cost가 낮은 vertex기준으로 다른 vertex를 갱신한다
      priority queue를 이용 
        cost뿐 아니라 다른 우선순위가 있을 경우에도 이용 가능{priority1,priority2,...priorityN,dest_vertex}
      vertex의 기본값은 -1로하여, -1인 경우 갱신되지 않은 것으로 감안한다.
    priority queue가 빌 때까지 실행하면 모든 vertex가 갱신된다.
      start가 맨 처음 pq에 들어간다.
      이후 가장 낮은 값의 vertex를 기준으로 갱신한다.
        음의 경로가 존재하지 않으므로, 가장낮은 값은 절대 변하지 않기 때문 
  */
  int num_V=cost_V.size();  //even if range 1~N, its OK, because there is no edge from vertex 0
  fill_n(cost_V,num_V,-1); //cost 초기화
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;  //second==starting point vertex, first== vertex's cost
  pq.push({0,start});
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    int cost(tmp.first),from_V(tmp.second);
    if(cost_V[from_V]!=-1){ //there is minimum already
      continue;
    }
    cost_V[from_V]=cost; //갱신
    for(auto& ele:graph[from_V]){
      pq.push({cost+ele.second,ele.first});
    }
  }
}
int BellmanFord(const vector<map<int,int>>& graph, vector<int>& cost_V, int start, int INF){  //0 return = Ok, 1 return = minus cycle
  /*
  Bellman-Ford Algorithm
    음수 cost 경로 가능
    모든 edge를 chk하여 vertex를 갱신한다. 
      갱신되지 않은 vertex에서 출발하는 edge는 감안하지 않는다.
      vertex의 기본값은 INF로 하여, INF값인 경우 갱신되지 않은 것으로 감안한다.
    #vertex -1 번 실행하면 최단거리를 찾을 수 있게 된다.
      시작 vertex는 갱신되어 있다. 
      edge chk 마다 최소 한개의 vertex가 갱신된다.
      즉  #vertex-1 번이면 반드시 모든 vertex가 갱신된다.
    #vertex 번째 실행에서 바뀌는 값이 있다면, 음의 사이클이 있는 것으로 간주한다.
      양의 사이클이 존재할 경우에는, 기존값 보다 커지기 때문에 "갱신" 이 일어나지 않는다.
    #vertex 번째 실행에서 갱신이 일어난 모든 vertex는 -INF로 간주한다.
      이때 vertex에서는 cycle 내부가 아닌 바깥으로만 이동하며 갱신이 가능하다.
        즉 cycle을 판별할 수 있어야 한다.
    ***음의 cycle 판별 추가바람
  */
  int num_V=cost_V.size();  //even if range 1~N, its OK, because there is no edge from vertex 0
  fill_n(cost_V,num_V,INF); //cost 초기화, INF==possible max Cost +1
  cost_V[start]=0;          //start==0
  vector<bool> active(num_V);//active vertex
  active[start]=true;
  for(int i=1;i<num_V;i++){ // #vertex -1 loop
    for(int j=0;j<num_V;j++){
      if(active[j]){
        int cost=cost_V[j]; //starting point cost
        for(auto& ele:graph[j]){  //first=dest, second= cost
          if(cost+ele.second<cost_V[ele.first]){
            cost_V[ele.first]=cost+ele.second;
          }
        }
      }
    }
    for(int j=0;j<num_V;j++){
      if(cost_V[j]<INF){
        active[j]=true;
      }
    }
  }
  vector<int> copy(cost_V);
  for(int j=0;j<num_V;j++){
    int cost=copy[j]; //starting point cost
    for(auto& ele:graph[j]){  //first=dest, second= cost
      if(cost+ele.second<copy[ele.first]){
        copy[ele.first]=cost+ele.second;
      }
    }  
  }
  for(int i=0;i<num_V;i++){
    if(copy[i]!=cost_V[i]){
      return 1;
    }
  }
  return 0;
}

void BK11657(){  // Bellman-Ford Algorithm, 음수 가중치도 허용한다, Edge 중심
  /*
  Bellman-Ford Algorithm
    모든 edge를 chk하여 vertex를 갱신한다. 
      갱신되지 않은 vertex에서 출발하는 edge는 감안하지 않는다.
      vertex의 기본값은 INF로 하여, INF값인 경우 갱신되지 않은 것으로 감안한다.
    #vertex -1 번 실행하면 최단거리를 찾을 수 있게 된다.
      시작 vertex는 갱신되어 있다. 
      edge chk 마다 최소 한개의 vertex가 갱신된다.
      즉  #vertex-1 번이면 반드시 모든 vertex가 갱신된다.
    #vertex 번째 실행에서 바뀌는 값이 있다면, 음의 사이클이 있는 것으로 간주한다.
      양의 사이클이 존재할 경우에는, 기존값 보다 커지기 때문에 "갱신" 이 일어나지 않는다.
    #vertex 번째 실행에서 갱신이 일어난 모든 vertex는 -INF로 간주한다.
      이때 vertex에서는 cycle 내부가 아닌 바깥으로만 이동하며 갱신이 가능하다.
        즉 cycle을 판별할 수 있어야 한다.
    ***음의 cycle 판별 추가바람

    문제에서는 음의 cycle이 발생할 경우 -1을 출력하므로 문제되지 않는다.
    V-1번 bellman-Ford실행후, V번째 실행을 한번 더 하여 변화가 있으면 -1, 없으면 출력
    출력시 INF는 -1로 출력

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
  vector<int> chk(N+1,INF);  // first== cost
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq; //first=cost, second=key
  
//calc
  pq.push({0,1});
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    int cost(tmp.first),key(tmp.second);
    if(chk[key]<cost){
      continue; //이미 했다면 넘어간다.
    }
    chk[key].first=cost;chk[key].second=pass;
    if(key==g){
      for(auto& ele: graph[key]){
        if(ele.first==h){
          pq.push({cost+ele.second,{-1,ele.first}});
        }else{
          pq.push({cost+ele.second,{pass,ele.first}});
        }
      }
    }else if(key==h){
      for(auto& ele: graph[key]){
        if(ele.first==g){
          pq.push({cost+ele.second,{-1,ele.first}});
        }else{
          pq.push({cost+ele.second,{pass,ele.first}});
        }
      }
    }else{
      for(auto& ele: graph[key]){
        pq.push({cost+ele.second,{pass,ele.first}});
      }
    }
  }
//output
  for(auto& ele: dest){
    if(chk[ele].second){
      cout<<ele<<" ";
    }
  }
  cout<<endl;
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  int T;
  cin>>T;
  while(T--){
    BK11657();
  }
  return 0;
}