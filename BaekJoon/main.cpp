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

void BK11657(){  // 
  /*
    1. s에서 출발해 모든 vertex까지의 최단경로를 찾는다.
    2. 이때 g->h 혹은 h->g로 갈 때, pass를 true로
    #priority Queue에서 cost는 같은데 경로가 다른 경우가 있다. 이때 g~h을 pass한 경로를 우선한다.
  */
//input
  int n,m,t,s,g,h,a,b,d,x;
  cin>>n>>m>>t>>s>>g>>h; // #교차로(vertex), #도로(edge), #목적지 후보, 출발지, g~h 사이의 도로 경유
  vector<map<int,int>> graph(n+1); // V[i]'s element =pair : i 와 p.first사이의 가중치 p.second의 양방향 경로, 중복 간선은 최저치 빼고 삭제
  set<int> dest; //목적지 후보를 저장한 vector
  for(int i=0;i<m;i++){
    cin>>a>>b>>d;
    graph[a].insert({b,d});
    graph[b].insert({a,d}); //양방향
  }
  for(int i=0;i<t;i++){
    cin>>x;
    dest.insert(x);
  }
//prepare
  vector<pair<int,bool>> chk(n+1,{-1,false});  // first== cost, second== 도로 경유 여부
  priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq; //first=cost, second.first=경유, second.second=key
//calc
  pq.push({0,{0,s}}); //second.first: 0은 미통과, -1은 통과
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    int cost(tmp.first),key(tmp.second.second),pass(tmp.second.first);
    if(chk[key].first!=-1){
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