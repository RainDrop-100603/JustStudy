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

int BFS5(int from, int to){
  bool chk[200001];
  int cnt(0);
  list<int> deque;
  deque.push_back(from);
  chk[from]=true;
  while(!deque.empty()){
    int sz=deque.size();
    if(chk[to]){
      break;
    }
    for(int k=0;k<sz;k++){
      auto p=deque.front();
      deque.pop_front();
      if(p<100000){
        if(!chk[p*2]){
          deque.push_back(p*2);
          chk[p*2]=true;
        }
      }
      if(p<100000){
        if(!chk[p+1]){
          deque.push_back(p+1);
          chk[p+1]=true;
        }
      }
      if(p>0){
        if(!chk[p-1]){
          deque.push_back(p-1);
          chk[p-1]=true;
        }
      }
    }
    cnt++;
  }
  return cnt;
}
void BK2206(){
//input
  int N,M;
  cin>>N>>M; //M: 가로, N: 세로
//prepare
//calc
  int result=BFS5(N,M);
//output
  cout<<result;
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  BK1697();
  
  return 0;
}