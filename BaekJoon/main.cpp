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
  int num;
  cin>>num;
  //변수 
  vector<int> arr(num+1);
  int num3=INT32_MAX; //3으로 나눈거
  int num2=INT32_MAX; //2으로 나눈거
  int num1=INT32_MAX; //1뺀거
  
  
  for(int i=num-1;i>0;i--){
    num3=INT32_MAX;
    num2=INT32_MAX;
    num1=INT32_MAX;
    if(i*3<=num){
      num3=arr[i*3]+1;
    }
    if(i*2<=num){
      num2=arr[i*2]+1;
    }
    if(i+1<=num){
      num1=arr[i+1]+1;
    }
    arr[i]=min(min(num3,num2),num1);
  }
  cout<<arr[1];
 

  return 0;
}

