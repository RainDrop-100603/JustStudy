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
  int num;
  cin>>num;
  vector<int> schedule(num);
  for(auto& ele: schedule){
    cin>>ele;
  }

  //변수 
  int totalTime=0;
  //계산
  sort(schedule.begin(),schedule.end());//끝나는 시간 순으로 정렬 
  for(auto& ele:schedule){
    totalTime=totalTime+num*ele;
    num--;
  }
  
  //출력
  cout<<totalTime;

  return 0;
}

