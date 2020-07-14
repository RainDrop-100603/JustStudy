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
  long long N;
  cin>>N;

  //변수
  vector<vector<long long>> result=FibonacciMatrix(N/2);
  cout<<result[0][0]<<' '<<result[0][1]<<'\n'<<result[1][0]<<' '<<result[1][1];
  // if(N%2==0){
  //   cout<<result[0][1];
  // }else{
  //   cout<<result[1][1];
  // }

  //계산

  //초기값
  
  
  //출력
  
  
 
  return 0;
}