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
  
  //입력
  int N;
  cin>>N;
  //변수
  pair<int,int> fibBefore(1,0); //바로 전 or 0
  pair<int,int> fib(0,1); //지금 or 1
  pair<int,int> temp;
  //계산
  int i=0;
  int input;
  while(i<N){
    cin>>input;
    fibBefore.first=1;
    fibBefore.second=0;
    fib.first=0;
    fib.second=1;
    while(input>1){
      temp=fib;
      fib.first+=fibBefore.first;
      fib.second+=fibBefore.second;
      fibBefore=temp;
      input--;
    }
    if(input==0){
      cout<<fibBefore.first<<' '<<fibBefore.second;
    }else{
      cout<<fib.first<<' '<<fib.second;
    }
    cout<<"\n";
    i++;
  }
  

  

  return 0;
}

