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
  int num1,num2;
  
  //변수  

  //계산
  cin>>num1>>num2;
  while(num1!=0||num2!=0){
    if(num1%num2==0){
      cout<<"multiple"<<"\n";
    }else if(num2%num1==0){
      cout<<"factor"<<"\n";
    }else{
      cout<<"neither"<<"\n";
    }
    cin>>num1>>num2;
  }

  //출력
 

  return 0;
}

