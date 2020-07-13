#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

// #include "GoodFunction.h"

using namespace std;

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  long long N,B;
  cin>>N>>B;
  vector<vector<long long>> matrix(N,vector<long long>(N));
  for(auto& ele: matrix){
    for(auto& ele2: ele){
      cin>>ele2;
    }
  }
  
  //변수
  vector<vector<long long>> matrix2(N,vector<long long>(N));
  vector<vector<long long>> result(N,vector<long long>(N));

  vector<int> flag; //B=2^x1+2^x2+ ... 의 합이다. x1, x2, x3 ... 순서로 저장된 스택. x1>x2
  int tmp;
  int modValue=1000;
  while(B!=0){
    tmp=log2(B);
    flag.push_back(tmp);
    B-=pow(2,tmp);   //10^-15만큼 오차범위라 사용 가능. B의 범위가 더 커지면 바꾸자           
  }
  tmp=flag.front(); //계산할 때 사용 

  //계산
  if(flag.back()==0){
    flag.pop_back();
    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
        result[i][j]+=matrix[i][j];
        result[i][j]%=modValue;
      }
    }     
  }
  for(int i=1;i<=tmp;i++){
    if(one){
      one=!one;
      for(int j=0;j<N;j++){   
        for(int k=0;k<N;k++){
          for(int x=0;x<N;x++){
            matrix2[j][k]+=matrix[j][x]*matrix[x][k];
            matrix2[j][k]%=modValue;
          }
        }
      }
    }else{
      one=!one;
      for(int j=0;j<N;j++){   
        for(int k=0;k<N;k++){
          for(int x=0;x<N;x++){
            matrix[j][k]+=matrix2[j][x]*matrix2[x][k];
            matrix[j][k]%=modValue;
          }
        }
      }
    }
    if(i==flag.back()){
      flag.pop_back();
      if(one){
        for(int i=0;i<N;i++){
          for(int j=0;j<N;j++){
            result[i][j]+=matrix[i][j];
            result[i][j]%=modValue;
          }
        }
      }else{
        for(int i=0;i<N;i++){
          for(int j=0;j<N;j++){
            result[i][j]+=matrix2[i][j];
            result[i][j]%=modValue;
          }
        }
      }
      
    }
  }

  //출력
  for(auto& ele: result){
    for(auto& ele2: ele){
      cout<<ele2<<' ';
    }
    cout<<'\n';
  }
  
 
  return 0;
}