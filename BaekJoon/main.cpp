#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //DynmaicPrograming

  //입력
  int digit;
  cin>>digit;
  //변수 
  unsigned long long arr[10]={0,1,1,1,1,1,1,1,1,1};  //digit=0일때의 계단수. arr[x]는 x로 끝나는 계단수 의미
  unsigned long long prevArr[10];
  unsigned long long count=0;  //합

  for(int i=1;i<digit;i++){ //1~digit-1 까지
    //prev에 복사
    for(int j=0;j<10;j++){
      prevArr[j]=arr[j];
    }
    //현재
    arr[0]=prevArr[1];
    arr[9]=prevArr[8];
    for(int k=1;k<=8;k++){
      arr[k]=(prevArr[k-1]+prevArr[k+1])%1000000000;
    }
  }

  for(int i=0;i<10;i++){
    count+=arr[i];
  }

  cout<<count%1000000000;

  

  return 0;
}

