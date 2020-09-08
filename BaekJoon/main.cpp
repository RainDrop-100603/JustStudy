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

int table[10001][101];

void BK10217(){  // Dijkstra
//input
  int N,M,K,A,B,C,D;
  cin>>N>>M>>K; // #vertex, max Cost, #edge
  vector<pair<int,pair<int,int>>> graph[N+1]; // dest, money, time
  for(int i=0;i<K;i++){
    cin>>A>>B>>C>>D; //from,dest,money,time
    graph[A].push_back({B,{C,D}}); //dest,money,time
  }
//prepare
  int INF=10000*10000+1;  //#edge*maxCost(or Time)+1;
  for(int i=0;i<M+1;i++){
    fill_n(table[i],N+1,INF);//INF: 경로없음, cost,dest,time
  }
  table[0][1]=0;
  int newCost;
//calc
  for(int i=0;i<M;i++){ //money, M일때는 어차피 더이상 이동 불가능 하여 M-1 까지
    for(int j=1;j<=N;j++){  //dest vertex, 0행은 사용하지 않으므로 생략
      if(table[i][j]!=INF){
        for(auto& ele:graph[j]){
          newCost=ele.second.first+i;
          if(newCost<=M){
            table[newCost][ele.first]=min(table[newCost][ele.first],table[i][j]+ele.second.second); //기존 시간과, 새롭게 추가된 시간중 작은값
          }
        }
      }
    }
  }
//output
  int result=INF;
  for(int i=0;i<=M;i++){
    result=min(result,table[i][N]);
  }
  if(result==INF){
    cout<<"Poor KCM\n";
  }else{
    cout<<result<<"\n";
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