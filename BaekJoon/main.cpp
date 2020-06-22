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
  
  //다른색의 코스트가 같을때를 정해줘야 한다. RG->A RB->B GB->C RGB->D

  //입력
  int caseNum;
  cin>>caseNum;
  //변수
  int cost[3]={0};
  int sum[3]={0};
  char color[3]={'R','G','B'};  //RGB 색상 
  for(int j=0;j<3;j++){         //초기값 지정 
      cin>>sum[j];
  }

  for(int i=0;i<caseNum-1;i++){
    for(int j=0;j<3;j++){
      cin>>cost[j];
    }
    for(int j=0;j<3;j++){
      switch(color[j]){
        case 'R':
          if(cost[1]>cost[2]){
            sum[j]+=cost[2];
            color[j]='B';
          }else{
            sum[j]+=cost[1];
            color[j]='G';
          }
          break;
        case 'G':
          if(cost[0]>cost[2]){
            sum[j]+=cost[2];
            color[j]='B';
          }else{
            sum[j]+=cost[0];
            color[j]='R';
          }
          break;
        case 'B':
          if(cost[0]>cost[1]){
            sum[j]+=cost[1];
            color[j]='G';
          }else{
            sum[j]+=cost[0];
            color[j]='R';
          }
          break;
      }
    }
  }
  int lowest=sum[0];
    if(lowest>sum[1]){
      lowest=sum[1];
    }
    if(lowest>sum[2]){
      lowest=sum[2];
    }
    cout<<lowest;

  return 0;
}

