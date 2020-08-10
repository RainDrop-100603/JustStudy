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
bool cmpPairX(const pair<int,int>& p1,const pair<int,int>& p2){
  return p1.first<p2.first;
}
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
void BK2293_Memover2(){  //table에 유효한 값만 저장하자 
//input
  int N,K;
  scanf("%d %d",&N,&K);
  vector<int> arr(N);
  for(auto& ele: arr){
    scanf("%d",&ele);
  }
//prepare  
  sort(arr.begin(),arr.end());
  vector<vector<pair<int,int>>> table(N,vector<pair<int,int>>(1,make_pair(0,1)));  // i행은 arr[i]의 유효한 값: pair<num,count>를 저장
  //for(int i=0;i<N;i++){                                             // i 행의 pair<num,count> : num 에서 최댓값이 i인 경우의 수는 count
  //   table[i].push_back(make_pair(0,1));                             // 기존의 A(i,j)는 lowerbound(table[j].begin(),table[j].end(),i)->second;
  // }                                                                 
  int dist,prev;
//calc
  for(int i=1;i<K+1;i++){
    prev=0; //A(ij)=A(i,j-1)+A(i-arr[j],j); ,prev=A(i,j-1);
    for(int j=0;j<N;j++){
      dist=i-arr[j];
      if(dist>=0){
        prev+=lower_bound(table[j].begin(),table[j].end(),make_pair(dist,0),cmpPairX)->second;
      }
      if(table[j].back().second==prev){
        table[j].back().first++;
      }else{
        table[j].push_back(make_pair(i,prev));
      }
    }
  }
  printf("%d",table[N-1].back().second);
}
void BK2293_3(){
//input
  int N,K;
  scanf("%d %d",&N,&K);
  vector<int> arr(N);
  for(auto& ele: arr){
    scanf("%d",&ele);
  }
//prepare  
  sort(arr.begin(),arr.end());
  vector<vector<int>> table(2,vector<int>(K+1));  //A(ij)==최댓값이 arr[i]인 j의 경우의 수, 0열에는 1저장
  for(int i=0;i<2;i++){
    table[i][0]=1;
  } 
  int from,prev;
  bool first(true); //배열을 절약해 두개만 사용한다. ture면 1행을 이용해 0행에 저장
//calc
  for(int i=0;i<N;i++){
    for(int j=1;j<K+1;j++){ //A(ij)=A(i-1,j)+A(i,j-arr[i]); ,prev=A(i-1,j);
      from=j-arr[i];
      if(first){
        prev=table[1][j];
        if(from>=0){
          prev+=table[0][from];
        }
        table[0][j]=prev;
      }else{
        prev=table[0][j];
        if(from>=0){
          prev+=table[1][from];
        }
        table[1][j]=prev;
      }
    }
    !first;
  }
  if(!first){
    printf("%d",table[0][K]);
  }else{
    printf("%d",table[1][K]);
  }
  
}

int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  BK2293_3();
  
  return 0;
}