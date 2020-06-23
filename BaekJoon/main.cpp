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
  int number;
  cin>>number;
  int input;

  //변수
  vector<int> inputNum(number); //입력을 저장하는 곳
  vector<int> count(number);    //count 저장 
  vector<int> reverseCount(number); //뒤에서부터 시작해서 LIS
  vector<int> bitonicCount(number); // X 기준으로 앞부분은 count, 뒷부분은 reverse의 max를 구하여 합치면 bitonic 
  int tmpcount=0; //비교를 위함 

  //입력 - 수열
  for(int i=0;i<number;i++){
    cin>>input;
    inputNum[i]=input;
    for(int j=0;j<i;j++){
      if(inputNum[j]<input){
        tmpcount=max(tmpcount,count[j]);
      }
    }
    count[i]=tmpcount+1;
    tmpcount=0;
  }

  //reverse
  for(int i=number-1;i>=0;i--){
    for(int j=number-1;j>i;j--){
      if(inputNum[j]<inputNum[i]){
        tmpcount=max(tmpcount,reverseCount[j]);
      }
    }
    reverseCount[i]=tmpcount+1;
    tmpcount=0;
  }

  //bitonic

for(int i=0;i<number;i++){
  bitonicCount[i]=count[i]+reverseCount[i]-1;
}

  //출력
  for(int i=0;i<number;i++){
    tmpcount=max(tmpcount,bitonicCount[i]);
  }

  cout<<tmpcount<<"\n";

  


  return 0;
}

