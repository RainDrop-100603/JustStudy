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
  vector<pair<int,int>> schedule(num);
  for(auto& ele: schedule){
    cin>>ele.second>>ele.first; //second=시작시간, first=끝나는시간
  }

  //변수 
  int count=0;  //회의의 개수
  int confEnd=0;  //마지막에 회의가 끝난 시간 

  //계산
  sort(schedule.begin(),schedule.end());//끝나는 시간 순으로 정렬 
  for(auto& ele:schedule){
    if(ele.second>=confEnd){
      confEnd=ele.first;
      count++;
    }
  }
  
  //출력
  cout<<count;

  return 0;
}

