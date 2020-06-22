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
  
  //입력
  int peopleNum;
  cin>>peopleNum;
  vector<vector<int>> table(peopleNum,vector<int>(peopleNum));
  for(auto& ele1: table){
    for(auto& ele2:ele1){
      cin>>ele2;
    }
  }
  //요소 선언
  vector<int> startTeam(peopleNum/2+1); //[0]에는 현재 배치된 팀원의 수 
  vector<int> linkTeam(peopleNum/2+1);
  int gap=INT32_MAX;
  //함수 실행
  GetLowGap(gap,table,startTeam,linkTeam,0);  //idx번째 선수를 각 팀에 배분. 배분이 끝나면 gap 을 계산하고 기존 gap보다 낮을시 갱신 

  cout<<gap;


  return 0;
}

