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
  long long N,B;
  cin>>N>>B;
  vector<vector<int>> matrix(N,vector<int>(N));
  for(auto& ele: matrix){
    for(auto& ele2: ele){
      cin>>ele2;
    }
  }
  int modValue=1000;

  //변수
  vector<vector<int>> matrix2(N,vector<int>(N));  //임시저장소
  vector<vector<int>> result(N,vector<int>(N));   //결과
  vector<int> flag; //B=2^x1+2^x2+ ... 의 합이다. x1, x2, x3 ... 순서로 저장된 스택. x1>x2
  int tmp;
  while(B!=0){
    tmp=log2(B);
    flag.push_back(tmp);
    B-=pow(2,tmp);   //10^-15만큼 오차범위라 사용 가능. B의 범위가 더 커지면 바꾸자           
  }
  tmp=0;

  //계산
  //초기값
  for(int i=0;i<N;i++){
    result[i][i]=1;
  }

  while(!flag.empty()){
    if(tmp==flag.back()){
      MatrixMulMod(matrix2,matrix,result,modValue);
      MatrixCopy(result,matrix2);
      MatrixClear(matrix2);     
      flag.pop_back();
    }
    tmp++;
    MatrixMulMod(matrix2,matrix,matrix,modValue);
    MatrixCopy(matrix,matrix2);
    MatrixClear(matrix2);
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