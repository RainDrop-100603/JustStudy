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
  int num;  //숫자의 개수
  cin>>num;

  //변수
  vector<int> stackV; //스택
  vector<bool> operV; //push=true, pop=false
  stackV.reserve(num);operV.reserve(num);
  int input,push(1);  //input= 입력, 다음에 push할 수
  bool isOK(true);   //수열을 스택으로 출력 가능한지 여부 
  
  //계산
  while(num--){
    cin>>input;
    while(input>=push){
      stackV.push_back(push);
      operV.push_back(true);
      push++;
    } 
    if(input==stackV.back()){
      stackV.pop_back();
      operV.push_back(false);
    }else{
      isOK=false;
    }
    if(!isOK){
      cout<<"NO";
      break;
    }
  }
  //출력
  if(isOK){
    for(auto ele:operV){
      if(ele){
        cout<<'+'<<"\n";
      }else{
        cout<<'-'<<"\n";
      }
    }
  }

  
  return 0;
}

