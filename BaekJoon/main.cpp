#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

//#include "GoodFunction.h"

using namespace std;

void BK12015(){ //기저에 깔린 법칙
/*
Longest Increasing Subsequence: LIS
무엇을 key로 정할 것인가. key :left, right로 비교할 것
  LIS의 길이를 key로 한다 가정하자
    이분 탐색에는 lgn*operTime이 소요된다.
    operTime은 nlgn이하여야 한다.
      nlgn시간으로 배열에서 key길이의 IS가 있는지 탐색할 수 있는가?
      key길이의 IS가 있는지 알고싶다면 어떻게 해야 하는가
        key가 LIS의 길이보다 작다면, 모든 경우를 비교하지 않아도 된다.
        key가 LIS의 길이보다 크거나 같다면, 배열의 LIS를 구해야만 key보다 크거나 같은 IS의 존재유무를 판별할 수 있다.
          그러나 배열에서 LIS를 구한다면 그 자체로 답이 된다.
          즉, key를 LIS의 길이로 하는것은 유용하지 않다.
            만약, 배열에서 key길이의 IS를 구하는 것이 n Time에 가능하다면 유용할지도(LIS인지는 판별 불가하지만 key길이의 IS를 구할 수 있는 Algo가 있을까?)
*/
//input
  int N,K;
  scanf("%d %d",&N,&K);
//prepare  
//calc
  int left(1),right(K),mid,sum;  
  while(left<=right){
    mid=(left+right)/2;
    sum=0;
    for(int i=1;i<=N;i++){
      sum+=min(mid/i,N);
    }
    if(sum<K){ 
      left=mid+1;
    }else{
      right=mid-1;
    }
  }
  
  printf("%d",right+1);
}
int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  BK12015();

  return 0;
}