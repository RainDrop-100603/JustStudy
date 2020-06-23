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
  int caseNum;
  cin>>caseNum;
  //변수
  int cost[3]={0};
  int sum[3]={0};
  int sumPrev[3]={0};

  for(int i=0;i<caseNum;i++){
    for(int j=0;j<3;j++){
      cin>>cost[j];           //입력 RGB
      sumPrev[j]=sum[j];      //이전 R, G, B까지의 최소값
    }
    
    if(sumPrev[1]<sumPrev[2]){
      sum[0]=cost[0]+sumPrev[1];
    }else{
      sum[0]=cost[0]+sumPrev[2];
    }
    if(sumPrev[0]<sumPrev[2]){
      sum[1]=cost[1]+sumPrev[0];
    }else{
      sum[1]=cost[1]+sumPrev[2];
    }
    if(sumPrev[0]<sumPrev[1]){
      sum[2]=cost[2]+sumPrev[0];
    }else{
      sum[2]=cost[2]+sumPrev[1];
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

