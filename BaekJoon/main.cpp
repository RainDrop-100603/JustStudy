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

  //Greedy

  //입력
  int coinNum, targetAmount;
  cin>>coinNum>>targetAmount;
  vector<int> coinValue(coinNum);
  for(auto& ele: coinValue){
    cin>>ele;
  }

  //변수 
  int difference=targetAmount;  //차액
  int count=0;  //사용한 동전 개수
  int idx=coinNum-1;

  //계산
  while(difference!=0){
    if(coinValue[idx]<=difference){
      difference-=coinValue[idx];
      idx++;
      count++;
    }
    idx--;
  }
  
  //출력
  cout<<count;

  return 0;
}

