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
  vector<pair<int,int>> arr(N);  //first=rerun cost, second=getMem size
  for(auto& ele:arr){
    scanf("%d",&ele.second);
  }
  for(auto& ele:arr){
    scanf("%d",&ele.first);
  }
//prepare
  sort(arr.begin(),arr.end());
  map<int,int> costMap1;  //map[i]= i번째 원소까지 input한 tree
  map<int,int> costMap2;  //key : cost의 값, //value : 해제되는 memory 값
  costMap1.insert(make_pair(0,0));
  costMap2.insert({0,0});
  bool first; //first면 costMap1==Map[i], costMap2==Map[i-1]
  int ans;
  int cost,memSize;
//calc
  //map 정렬
  for(int i=0;i<N;i++){
    auto nowMap=&costMap1;
    auto prevMap=&costMap2;
    if(!first){
        auto* tmp=nowMap;
        nowMap=prevMap;
        prevMap=tmp;
    }
    for(auto iter=prevMap->begin();iter!=prevMap->end();iter++){
        cost=iter->first+arr[i].first;
        memSize=iter->second+arr[i].second;
        auto prevIter=prevMap->find(cost);
        if(prevIter!=prevMap->end()){
            if(prevIter->second>memSize){
                memSize=prevIter->second;
            }
        }
        auto ret=nowMap->insert({cost,memSize});   //ret.first==해당하는 위치의 iter, ret.second==성공여부
        if(!ret.second){
            ret.first->second=memSize;
        }
    }
  }
  // value 검색
  auto nowMap=&costMap2;
  if(!first){
    nowMap=&costMap2;
  }
  for(auto& ele: *nowMap){
    if(ele.second>=M){
        ans=ele.first;
        break;
    }
  }
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