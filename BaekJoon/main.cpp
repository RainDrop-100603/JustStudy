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
  int num;
  cin>>num;

  //변수
  bool* primes=GetPrimeArray(num);  
  int num2=num;

  //계산
  for(int i=0;i<num+1;i++){
    if(num2==1){
      break;
    }
    if(primes[i]){
      if(num2%i==0){
        num2/=i;
        cout<<i<<"\n";
        i--;
      }
    }
  }

  //출력

  return 0;
}

