#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>

//#include "GoodFunction.h"

using namespace std;

void BK2293_Memover(){
//input
  int N,K;
  scanf("%d %d",&N,&K);
  vector<int> arr(N);
  for(auto& ele: arr){
    scanf("%d",&ele);
  }
//prepare  
  sort(arr.begin(),arr.end());
  vector<vector<int>> table(K+1,vector<int>(N));  //A(ij)==최댓값이 arr[j]인 i의 경우의 수, 0열에는 1저장
  for(int i=0;i<N;i++){
    table[0][i]=1;
  } 
  int dist,prev;
//calc
  for(int i=1;i<K+1;i++){
    prev=0; //A(ij)=A(i,j-1)+A(i-arr[j],j); ,prev=A(i,j-1);
    for(int j=0;j<N;j++){
      dist=i-arr[j];
      if(dist>=0){
        prev+=table[dist][j];
      }
      table[i][j]=prev;
    }
  }
  printf("%d",table[K][N-1]);
}
void BK2293_2(){  //table에 유효한 값만 저장하자 
//input
  int N,K;
  scanf("%d %d",&N,&K);
  vector<int> arr(N);
  for(auto& ele: arr){
    scanf("%d",&ele);
  }
//prepare  
  sort(arr.begin(),arr.end());
  vector<vector<pair<int,int>>> table(N,vector<pair<int,int>>(0));  // i행은 arr[i]의 유효한 값: pair<num,count>를 저장
  for(int i=0;i<N;i++){                                             // i 행의 pair<num,count> : num 에서 최댓값이 i인 경우의 수는 count
    table[i].push_back(make_pair(0,1));                             // 기존의 A(i,j)는 table[j].find(lowerbound[i]);
  }                                                                 //lower bound는 pair.first 값이다. 이걸 어떻게 찾을 것이냐? map?직접 만들기? 
  int dist,prev;
//calc
  for(int i=1;i<K+1;i++){
    prev=0; //A(ij)=A(i,j-1)+A(i-arr[j],j); ,prev=A(i,j-1);
    for(int j=0;j<N;j++){
      dist=i-arr[j];
      if(dist>=0){
        prev+=table[dist][j];
      }
      table[i][j]=prev;
    }
  }
  printf("%d",table[K][N-1]);
}

int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  BK2293();
  
  return 0;
}