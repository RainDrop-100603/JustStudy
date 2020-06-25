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
  vector<int> number(num);
  int tmp,max;

  cin>>number[0];
  max=number[0];
  for(int i=1;i<num;i++){
    cin>>tmp;
    if(tmp+number[i-1]>0&&number[i-1]>0){
      number[i]=number[i-1]+tmp;
    }else{
      number[i]=tmp;
    }
    if(number[i]>max){
      max=number[i];
    }
  }
  
  
  cout<<max;

  return 0;
}

