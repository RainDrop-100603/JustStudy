#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

// #include "GoodFunction.h"

using namespace std;

void MatrixCopy(vector<vector<int>>& m1,vector<vector<int>>& m2){
  int x=m1.size();
  for(int i=0;i<x;i++){
    for(int j=0;j<x;j++){
      m1[i][j]=m2[i][j];
    }
  }
}

void MatrixClear(vector<vector<int>>& m1){
  int x=m1.size();
  for(int i=0;i<x;i++){
    for(int j=0;j<x;j++){
      m1[i][j]=0;
    }
  }
}

void MatrixMulMod(vector<vector<int>>& m1,vector<vector<int>>& m2,vector<vector<int>>& m3, int modValue){
  int x=m1.size();
  for(int i=0;i<x;i++){
    for(int j=0;j<x;j++){
      for(int k=0;k<x;k++){
        m1[i][j]+=m2[i][k]*m3[k][j];
      }
      m1[i][j]%=modValue;
    }
  }
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  long long N;
  cin>>N;
  int modValue=1000000;

  //변수
  vector<vector<int>> matrix2(N,vector<int>(N));  //임시저장소
  vector<vector<int>> result(N,vector<int>(N));   //결과

  //계산

  //초기값
  
  
  //출력
  
  
 
  return 0;
}