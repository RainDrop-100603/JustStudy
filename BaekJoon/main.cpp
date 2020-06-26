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
  vector<int> numbers(num);
  for(auto& ele:numbers){
    cin>>ele;
  }

  //변수
  sort(numbers.begin(),numbers.end());
  int minNum2=numbers[1];//입력중 두번째로 작은 수
  int tmp;

  //계산
  for(int i=2;i<=minNum2;i++){
    tmp=numbers[0]%i;
    for(auto& ele:numbers){
      if(ele%i!=tmp){
        tmp=-1;
        break;
      }
    }
    if(tmp!=-1){
      cout<<i<<' ';
    }
  }  
  

  //출력

  return 0;
}

