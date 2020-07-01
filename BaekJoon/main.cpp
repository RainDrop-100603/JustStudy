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

  //Math3

  //입력
  int n,m;
  cin>>n>>m;
  
  //변수
  int numOf2(0),numOf5(0);  //2의 개수, 5의 개수
  int from=n-m; //from+1에서 n까지 팩토리얼

  //계산
  for(long long i=2;i<2000000000;i*=2){
    numOf2+=n/i;
    numOf2-=from/i+m/i;
  }
  for(long long i=5;i<2000000000;i*=5){
    numOf5+=n/i;
    numOf5-=from/i+m/i;
  }
  
  

  //출력
  cout<<min(numOf2,numOf5);
 
  
  return 0;
}

