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
  int size;
  cin>>size;
  //변수
  vector<int> cost(size);
  vector<int> sum(size);
  vector<int> sumPrev(size);
  int depth=1;  //깊이 1부터 시작

  for(int i=0;i<size;i++){
    for(int j=0;j<depth;j++){
      cin>>cost[j];           //입력 RGB
      sumPrev[j]=sum[j];      //이전 R, G, B까지의 최소값
    }
    
    for(int j=0;j<depth;j++){
      if(j==0){
        sum[j]=cost[j]+sumPrev[j];
      }else if(j==depth-1){
        sum[j]=cost[j]+sumPrev[j-1];
      }else{
        sum[j]=cost[j]+max(sumPrev[j-1],sumPrev[j]);
      }
    }
    depth++;
  }
  
  for(int i=1;i<size;i++){
    sum[0]=max(sum[0],sum[i]);
  }
  cout<<sum[0];

  return 0;
}

