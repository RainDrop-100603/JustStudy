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

int BFS2(vector<vector<bool>>& graph, pair<int,int> p){
  int cnt(0);
  int N=graph.size();
  int M=graph[0].size();
  list<pair<int,int>> deque;
  deque.push_back(p);
  graph[p.first][p.second]=false;  //deque에 들어간다 -> 방문 
  while(!deque.empty()){
    int sz=deque.size();
    for(int k=0;k<sz;k++){
      p=deque.front();
      deque.pop_front();
      int i(p.first),j(p.second);
      if(i==N-1&&j==M-1){
        deque.clear();
        break;
      }
      // idx 체크
      if(i+1<N){
        if(graph[i+1][j]){
          deque.push_back({i+1,j});
          graph[i+1][j]=false;
        }
      }
      if(i>0){
        if(graph[i-1][j]){
          deque.push_back({i-1,j});
          graph[i-1][j]=false;
        }
      }
      if(j+1<M){
        if(graph[i][j+1]){
          deque.push_back({i,j+1});
          graph[i][j+1]=false;
        }
      }
      if(j>0){
        if(graph[i][j-1]){
          deque.push_back({i,j-1});
          graph[i][j-1]=false;
        }
      }
    }
    cnt++;
  }
  return cnt;
}
void BK2178(){
//input
  int N,M;
  cin>>N>>M; //M: 가로, N: 세로, 
  cin.ignore();
  vector<vector<bool>> graph(N,vector<bool>(M));  //graph와 chklist 겸임. true는 갈 수 있음, false는 이미 방문 혹은 갈 수 없음 
  for(int i=0;i<N;i++){
    string s;
    getline(cin,s);
    for(int j=0;j<M;j++){
      graph[i][j]=s[j]-'0';
    }
  }
//prepare
//calc
  int result=BFS2(graph,{0,0});
//output
  cout<<result;
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  BK2178();
  
  return 0;
}