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
  int coinNum, targetAmount;
  cin>>coinNum>>targetAmount;
  vector<int> coinValue(coinNum);
  for(auto& ele: coinValue){
    cin>>ele;
  }

  //변수 
  int difference=targetAmount;  //차액
  int idx=0;  //coinValue[idx]<=targetAmount<coinValue[idx+1]
  int count=0;  //사용한 동전 개수

  //계산
  while(idx+1<coinNum){                      //target보다는 작은 coin 이어야 한다.
    if(targetAmount<coinValue[idx+1]){
      break;
    }
    idx++;
  }
  while(difference!=0){
    if(coinValue[idx]>difference){
      idx--;
      continue;
    }
    difference-=coinValue[idx];
    count++;
  }

  //출력
  cout<<count;

  return 0;
}

