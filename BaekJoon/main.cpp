#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;

void chkM(int tmpM,vector<int>& numbers){
  int A0=numbers[0];
  for(int i=2;i<numbers.size();i++){
    if(numbers[i]%tmpM!=A0%tmpM){
      return;
    }
  }
  cout<<tmpM<<"\n";
}

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
  sort(numbers.begin(),numbers.end());    //A0 ~ AN-1
  int min0=numbers[0];   //A0
  int min1=numbers[1];   //A1
  int tmpM; //A0과 A1에서 M으로 인정되는 수

  //계산
  //[2,A0]
    for(int i=2;i<=min0;i++){
      if(min0%i==min1%i){
        chkM(i,numbers);
      }
    }
  //(A0,A1) 1개, M=A1-A0  
    tmpM=min1-min0;
    chkM(tmpM,numbers);
  //[A1,00] 없다
  
  //출력

  return 0;
}

