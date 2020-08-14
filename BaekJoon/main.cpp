#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>

//#include "GoodFunction.h"

using namespace std;
void BK7579(){
//input
  int N,M;
  scanf("%d %d",&N,&M); //N== # program, M==need size;
  vector<pair<int,int>> cost(N);  //first=rerun cost, second=getMem size
  for(auto& ele:cost){
    scanf("%d",&ele.second);
  }
  for(auto& ele:cost){
    scanf("%d",&ele.first);
  }
//prepare
  sort(cost.begin(),cost.end());
  map<int,int> costMap1;  //map[i]= i번째 원소까지 input한 tree
  map<int,int> costMap2;  //key : cost의 값, //value : 해제되는 memory 값
  costMap1.insert(0,0);
  costMap2.insert(0,0);
  bool first; //first면 costMap1==Map[i], costMap2==Map[i-1]
  int ans;
  int cost,memSize;
//calc
  //map 정렬
  for(int i=0;i<N;i++){
    map<int,int>::iterator iter;
    map<int,int>::iterator prevIter;
    map<int,int>::iterator nowIter;
    if(first){
      for(iter=costMap2.begin();iter!=costMap2.end();iter++){
        cost=iter->first+cost[i].first;
        memSize=iter->second+cost[i].second;
        prevIter=costMap2.find(cost);
        if(prevIter==costMap2.end()){
          costMap1.insert(cost,memSize);
        }else{
          if(memSize>prevIter->second){
            nowIter=costMap1.find(cost);
            if(nowIter==costMap1.end()){
              costMap1.insert(cost,memSize);
            }else{
              nowIter->second=memSize;
            }
          }
        }
      }
    }else{
      // for(iter=costMap1.begin();iter!=costMap1.end();iter++){
      //   cost=iter->first+cost[i].first;
      //   memSize=iter->second+cost[i].second;
      //   prevIter=costMap1.find(cost);
      //   if(prevIter==costMap1.end()){
      //     costMap2.insert(cost,memSize);
      //   }else{
      //     if(memSize>prevIter->second){
      //       nowIter=costMap2.find(cost);
      //       if(nowIter==costMap1.end()){
      //         costMap2.insert(cost,memSize);
      //       }else{
      //         nowIter->second=memSize;
      //       }
      //     }
      //   }
      // }
    }
  }
  //
//output
  // for(auto& ele:movTable){
  //   for(auto& ele2:ele){
  //     printf("%d ",ele2);
  //   }
  //   printf("\n");
  // }
  printf("%d\n",ans);

}
int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
//   int N;
//   scanf("%d",&N);
//   while(N--){
    BK7579();
//  }
  
  return 0;
}