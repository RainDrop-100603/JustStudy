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

int BFS3(vector<vector<int>>& graph){
  int cnt(-1);
  int N=graph.size();
  int M=graph[0].size();
  list<pair<int,int>> deque;\
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(graph[i][j]==1){
        deque.push_back({i,j});
      }
    }
  }
  while(!deque.empty()){
    int sz=deque.size();
    for(int k=0;k<sz;k++){
      auto p=deque.front();
      deque.pop_front();
      int i(p.first),j(p.second);
      // idx 체크
      if(i+1<N){
        if(!graph[i+1][j]){
          deque.push_back({i+1,j});
          graph[i+1][j]=1;
        }
      }
      if(i>0){
        if(!graph[i-1][j]){
          deque.push_back({i-1,j});
          graph[i-1][j]=1;
        }
      }
      if(j+1<M){
        if(!graph[i][j+1]){
          deque.push_back({i,j+1});
          graph[i][j+1]=1;
        }
      }
      if(j>0){
        if(!graph[i][j-1]){
          deque.push_back({i,j-1});
          graph[i][j-1]=1;
        }
      }
    }
    cnt++;
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(!graph[i][j]){
        cnt=-1;
        i=N;
        break;
      }
    }
  }
  return cnt;
}
void BK7576(){
//input
  int N,M;
  cin>>M>>N; //M: 가로, N: 세로, 
  cin.ignore();
  vector<vector<int>> graph(N,vector<int>(M));  //graph와 chklist 겸임. true는 갈 수 있음, false는 이미 방문 혹은 갈 수 없음 
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      cin>>graph[i][j];
    }
  }
//prepare
//calc
  int result=BFS3(graph);
//output
  cout<<result;
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  BK7576();
  
  return 0;
}