#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

//#include "GoodFunction.h"

using namespace std;

void BK1300_H(){ //기저에 깔린 법칙
/*
  K번째 수는 K보다 작거나 같다.
    배열의 어떤 원소 A(i,j)를 생각하자.
      배열에는 최소 i*j-1개의 A(i,j)보다 작은 수와, 1개의 A(i,j)가 있다.
      또한 행이 i+1이상인, 열이 j+1이상인 위치에서 A(i,j)보다 작은 수가 존재할 수 있다.
        즉 아래와 같은 식이 도출된다
          A(i,j)<=A(i,j)보다 작거나 같은 수의 개수
        다시 말하면
          A(i,j)번째 수 <= A(i,j) , (등호는 i==j==N일 경우에만 성립하는건 아니다. 1번째 1 2번째2, 더 있을수도?)
          K번째 수는 K보다 작거나 같다.
  min(K/i,N)은, i행에서 K보다 작은 수의 개수이다.
    어떤 수 K를 행 i로 나눈다고 생각하자.
      행 i에서, 숫자의 최대값은 i*N 이다.
      행 i에서, i*j보다 작거나 같은 수의 개수는 j개 이다.
        즉 min(K/i,N)은 ,i행에서 K보다 작은 수의 개수이다.
  K는 행렬에서 sum+1번째 수보다 크거나 같고, sum+2번째 수보다 작다
    sum=0,for(i=1~N){sum+=min(K/i),N}은 행렬에서 K보다 작은 수의 개수이다.  
    K는 행렬의 있는 숫자가 아니라 임의의 숫자다. 즉 sum+1 번재 숫자보다 클 수 있다.
      그러나 sum+2번째 숫자보다 크거나 같다면 K의 순서는 sum+2가 되므로,K는 sum+2보다 작다.
  K-a에 대하여, 이분탐색을 통하여 a=0일때 sum+1을 만족하는 K를 찾는다.
    K-3이 여전히 sum+1번째 숫자보다 크거나 같다면, K-3은 K보다 sum+1에 더 가까워진 것이다.
    K는 조건을 만족하는데 K-1을 만족하지 못한다면, 그때의 K가 sum+1번째 수라고 할 수 있다. 
  sum+1=K가 되도록 해서 구하자
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
  BK1300_H();

  return 0;
}