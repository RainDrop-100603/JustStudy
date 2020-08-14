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
  map<int,int> costMap;  //map[i]= i번째 원소까지 input한 tree
  vector<pair<int,int>> tmpStack; //map[i+1]로 넘어가기 전에 잠시 저장하는 곳
  costMap.insert(make_pair(0,0)); //key=cost, value=memSize
  int ans;
  int cost,memSize;
//calc
  //map 정렬
  for(int i=0;i<N;i++){
    for(auto iter=costMap.begin();iter!=costMap.end();iter++){
      cost=iter->first+arr[i].first;
      memSize=iter->second+arr[i].second;
      tmpStack.push_back({cost,memSize});
    }
    for(auto& ele:tmpStack){
      auto ret=costMap.insert(ele);
      if(!ret.second){
        if(ret.first->second<ele.second){
          ret.first->second=ele.second;
        }
      }
    }  
  }
  // value 검색
  for(auto& ele: costMap){
    if(ele.second>=M){
      ans=ele.first;
      break;
    }
  }
//output
  // for(auto& ele:costMap){
  //   printf("%d %d\n",ele.first,ele.second);
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