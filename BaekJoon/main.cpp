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
  int num;  //포도주 잔의 개수
  cin>>num;
  int wine; //와인의 양
  //변수 
  pair<int,int> temp(0,0);
  pair<int,pair<int,int>> num1(0,temp);// num번째 합계
  pair<int,pair<int,int>> numM1(0,temp);// num-1번째 합계 
  pair<int,pair<int,int>> numM2(0,temp);// num-2번째 합계
  pair<int,pair<int,int>> numM3(0,temp);// num-3번째 합계

  for(int i=0;i<num;i++){
    cin>>wine;
    numM3=numM2;
    numM2=numM1;
    numM1=num1;
    num1.first=wine+max(numM1.second.first,numM1.second.second);
    num1.second.first=wine+max(numM2.first,max(numM2.second.first,numM2.second.second));
    num1.second.second=wine+numM3.first;
  }
  int maxs=max(num1.first,num1.second.first);
  maxs=max(maxs,num1.second.second);
  maxs=max(maxs,numM1.first);

  cout<<maxs;


  return 0;
}

