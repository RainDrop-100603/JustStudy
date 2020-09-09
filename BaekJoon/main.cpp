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

#include "GoodFunction.h"

using namespace std;

void BK1956(){  // Dijkstra
  /*
  문제조건
    첫째 줄에 V와 E가 빈칸을 사이에 두고 주어진다. (2<=V<=400, 0<=E<=V*(V-1)) 다음 E개의 줄에는 각각 세 개의 정수 a, b, c가 주어진다.
     a번 마을에서 b번 마을로 가는 거리가 c인 도로가 있다는 의미이다. (a->b임에 주의) 거리는 10,000 이하의 자연수이다.
    자료형: 최대크기= #edge*maxTime(or cost)=400*400*10,000=1,600,000,000: int
    시작점으로 돌아오는 cycle을 찾아라 
  first
    Dijkstra 반복
    BellmanFord 사용시 이득 없음
    FloydWarshall : 쓸만한듯
      vertex간 거리를 저장하는 table에서, A(ij)+A(ji): j=1~#edge == i로 돌아오는 모든 사이클 
      -> 1로 돌아오는 사이클만 보는것이 아님을 고려해야한다.
  */
//input
  int V,E,a,b,c;
  cin>>V>>E; // #vertex, #edge
  vector<map<int,int>> graph(V+1); // dest, money, time
  for(int i=0;i<E;i++){
    cin>>a>>b>>c; //from,dest,cost
    auto ans=graph[a].insert({b,c}); //dest,money,time
    if(!ans.second&&ans.first->second>c){
      ans.first->second=c;
    }
  }
//prepare
  vector<vector<int>> cost_V(V+1,vector<int>(V+1));
  vector<vector<int>> prev_V(V+1,vector<int>(V+1));
//calc
  FloydWarshall(graph,cost_V,prev_V);
//output
  int result=INT32_MAX;
  for(int i=1;i<=V;i++){
    for(int j=i+1;j<=V;j++){
      if(cost_V[i][j]!=INT32_MAX&&cost_V[j][i]!=INT32_MAX){
        result=min(result,cost_V[i][j]+cost_V[j][i]);
      }
    }
  }
  if(result==INT32_MAX){ //if there is one INF, sum is INF or minus
    cout<<-1;
  }else{
    cout<<result;
  }
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  BK1956();
  return 0;
}