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

//#include "GoodFunction.h"

using namespace std;
void visit(vector<vector<int>>& graph, deque<pair<bool,pair<int,int>>>& dq,int X,int Y,bool brk){
  switch(graph[X][Y]){
    case 1:
      if(brk){
        dq.push_back({false,{X,Y}});
        graph[X][Y]=-3;
      }
      break;
    case 0:
      dq.push_back({brk,{X,Y}});
      if(brk){
        graph[X][Y]=-2;
      }else{
        graph[X][Y]=-1;
      }
      break;
    case -1:
      if(brk){
        dq.push_back({true,{X,Y}});
        graph[X][Y]=-2;
      }
      break;
    default:
      break;
  }
}
int BFS6(vector<vector<int>>& graph){
  int N=graph.size(); 
  int M=graph[0].size();
  int cnt(1);
  deque<pair<bool,pair<int,int>>> dq; //벽뚫 가능 여부, x, y
  dq.push_back({true,{0,0}});
  graph[0][0]=-2;     // -3 벽에 방문, 1 벽, 0 미방문, -1 벽뚫고방문, -2 방문불가==그냥 방문 (그냥 방문이 벽뚫고 방문이랑 같거나 빠르다면 그냥이 우선된다.)
  while(!dq.empty()){
    int sz=dq.size();
    if(graph[N-1][M-1]<0){
      break;
    }
    for(int k=0;k<sz;k++){
      auto p=dq.front();
      dq.pop_front();
      int x(p.second.first),y(p.second.second);
      bool brk(p.first);
      if(x>0){visit(graph,dq,x-1,y,brk);}
      if(x<N-1){visit(graph,dq,x+1,y,brk);}
      if(y>0){visit(graph,dq,x,y-1,brk);}
      if(y<M-1){visit(graph,dq,x,y+1,brk);}
    }
    cnt++;
  }
  if(graph[N-1][M-1]>=0){
    cnt=-1;
  }
  return cnt;
}
void BK2206(){
//input
  int N,M;
  cin>>N>>M; //M: 가로, N: 세로
  vector<vector<int>> graph(N,vector<int>(M));
  cin.ignore();
  for(int i=0;i<N;i++){
    string s;
    getline(cin,s);
    for(int j=0;j<M;j++){
      graph[i][j]=s[j]-'0';
    }
  }
//prepare
//calc
  int result=BFS6(graph);
//output
  cout<<result;
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  BK2206();
  
  return 0;
}