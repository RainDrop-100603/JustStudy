#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;

int main(){
  // cin.tie(NULL);
  // cin.sync_with_stdio(false);

  //Greedy

  //입력
  string str1;
  cin>>str1;
  
  //변수  
  bool minusCount=false;  //minus가 한번이라도 나오면 그 뒤는 전부 마이너스로 치환 가능 
  // string::size_type idxFrom;  // 숫자가 문자열로 변환되어 있기 때문에 범위를 알아야한다.
  char tmp;
  int sum=stoi(str1);


  //계산
  for(int i=0;i<str1.length();i++){
    tmp=str1[i];
    if(tmp=='-'||tmp=='+'){
      if(minusCount){
        sum-=stoi(str1.substr(i+1));
      }else if(tmp=='-'){
        minusCount=true;
        sum-=stoi(str1.substr(i+1));
      }else{
        sum+=stoi(str1.substr(i+1));
      }     
    }
  }

  //출력
  cout<<sum;

  return 0;
}

