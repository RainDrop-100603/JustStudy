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
void BK10942_timeover(){
//input
  int N,Q;  //팰린드롬: 앞뒤를 뒤집어도 똑같은 문자열 
  scanf("%d",&N); //N== size of arr
  vector<int> arr(N);  
  for(auto& ele:arr){
    scanf("%d",&ele);
  }
  scanf("%d",&Q); //N== #Question
//prepare
  int from,to,ans;  //(from-1)~(to-1)
  vector<vector<pair<int,bool>>> p(N);  //palindrome, p(n)의 원소는, 펠린드롬까지의 거리와 짝/홀을 나타낸다.
  if(arr[0]==arr[1]){
    p[1].push_back({0,true}); //true는 짝수펠린드롬. {i,false}의 반대편=n-2i,true(짝)=n-2i+1, 짝수의 경우 i는 왼쪽 기준
  }
//calc
  //팬릴드롬 행렬 생성
  for(int i=2;i<N;i++){
    auto& prev=p[i-1];
    auto& now=p[i];
    if(arr[i]==arr[i-1]){
      p[i].push_back({0,true});
    }
    if(arr[i]==arr[i-2]){
      p[i].push_back({1,false});
    }
    for(auto& ele:prev){
      if(ele.second){ //짝수
        if(arr[i-ele.first*2-1]==arr[i]){
          now.push_back({ele.first+1,ele.second});
        }
      }else{  //홀수
        if(arr[i-ele.first*2-2]==arr[i]){
          now.push_back({ele.first+1,ele.second});
        }
      }
    }
  }

//output
  // int idx=0;
  // for(auto& ele:p){
  //   printf("%d: ",idx++);
  //   for(auto& ele2:ele){
  //     printf("(%d, %d) ",ele2.first,ele2.second);
  //   }
  //   printf("\n");
  // }
  for(int i=0;i<Q;i++){
    scanf("%d %d",&from,&to);
    ans=0;
    from--;to--;
    int d=to-from;
    if(d%2==0){
      d/=2;
      for(auto& ele:p[to]){
        if(!ele.second&&ele.first==d){
          ans=1;
          break;
        }
      }
    }else{
      d=d/2+1;
      for(auto& ele:p[to]){
        if(ele.second&&ele.first==d){
          ans=1;
          break;
        }
      }
    }
    
    if(from==to){
      ans=1;
    }
    printf("%d\n",ans);
  }

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
    BK10942_timeover();
//  }
  
  return 0;
}