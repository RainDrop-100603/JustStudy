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

int BFS4(vector<vector<vector<int>>>& graph){
  int cnt(-1);
  int N=graph.size();
  int M=graph[0].size();
  int H=graph[0][0].size();
  list<pair<int,pair<int,int>>> deque;
  for(int k=0;k<H;k++){
    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        if(graph[i][j][k]==1){
          deque.push_back({i,{j,k}});
        }
      }
    }
  }
  
  while(!deque.empty()){
    int sz=deque.size();
    for(int k=0;k<sz;k++){
      auto p=deque.front();
      deque.pop_front();
      int i(p.first),j(p.second.first),z(p.second.second);
      // idx 체크
      if(i+1<N){
        if(!graph[i+1][j][z]){
          deque.push_back({i+1,{j,z}});
          graph[i+1][j][z]=1;
        }
      }
      if(i>0){
        if(!graph[i-1][j][z]){
          deque.push_back({i-1,{j,z}});
          graph[i-1][j][z]=1;
        }
      }
      if(j+1<M){
        if(!graph[i][j+1][z]){
          deque.push_back({i,{j+1,z}});
          graph[i][j+1][z]=1;
        }
      }
      if(j>0){
        if(!graph[i][j-1][z]){
          deque.push_back({i,{j-1,z}});
          graph[i][j-1][z]=1;
        }
      }
      if(z>0){
        if(!graph[i][j][z-1]){
          deque.push_back({i,{j,z-1}});
          graph[i][j][z-1]=1;
        }
      }
      if(z+1<H){
        if(!graph[i][j][z+1]){
          deque.push_back({i,{j,z+1}});
          graph[i][j][z+1]=1;
        }
      }
    }
    cnt++;
  }
  for(int k=0;k<H;k++){
    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        if(!graph[i][j][k]){
          cnt=-1;
          i=N;
          k=H;
          break;
        }
      }
    }
  }
  return cnt;
}
void BK7569(){
//input
  int N,M,H;
  cin>>M>>N>>H; //M: 가로, N: 세로, H: 높이
  cin.ignore();
  vector<vector<vector<int>>> graph(N,vector<int>(M,vector<int>(H)));  //graph와 chklist 겸임. true는 갈 수 있음, false는 이미 방문 혹은 갈 수 없음 
  for(int k=0;k<H;k++){
    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        cin>>graph[i][j][H];
      }
    }
  }
  
//prepare
//calc
  int result=BFS4(graph);
//output
  cout<<result;
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  BK7569();
  
  return 0;
}