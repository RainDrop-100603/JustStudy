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
  int K,N;
  cin>>N>>K;
  int modValue=1000000007;
  
  //변수
  long long A(1),B(1);
  long long Breverse;
  long long result; //int 형 곱셈이므로 long long으로 커버 

  //계산
  for(int i=0;i<K;i++){
    A=A*(N-i)%modValue;
    B=B*(i+1)%modValue;
  }
  Breverse=EuclidAlgo(modValue,B).second;
  result=A*Breverse%modValue;
  if(result<0){
    result+=modValue;
  }
  //출력
  cout<<result;
  
 
  return 0;
}