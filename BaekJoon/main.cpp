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
  int fibonacciN;
  cin>>fibonacciN;
  vector<char> fN_1;
  fN_1.push_back(1); 
  vector<char> fN_2;
  fN_2.push_back(0);
  int fnSize=1;   //매번 vector.size하기에는 귀찮으니
  int upbeat=0;// 계산시 올라가는 수
  int temp; // fN-2를 저장하기위해 임시적으로 저장
  int tmpsum;

  //계산
  while(fibonacciN>1){
    for(int i=0;i<fnSize;i++){
    tmpsum=fN_1[i]+fN_2[i]+upbeat;
    temp=fN_1[i];
    fN_1[i]=tmpsum%10;
    fN_2[i]=temp;
    upbeat=tmpsum/10;
    }
    if(upbeat==1){
      fN_1.push_back(1);
      fN_2.push_back(0);
      fnSize++;
      upbeat=0;
    }
    fibonacciN--;
  }
  

  //출력
  for(int i=fnSize-1;i>=0;i--){
    cout<<static_cast<int>(fN_1[i]);
  }

  return 0;
}

