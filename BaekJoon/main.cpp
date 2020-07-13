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
  int N,M,K;
  cin>>N>>M;
  vector<vector<int>> matrix1(N,vector<int>(M));
  for(auto& ele: matrix1){
    for(auto& ele2: ele){
      cin>>ele2;
    }
  }
  cin>>M>>K;
  vector<vector<int>> matrix2(M,vector<int>(K));
  for(auto& ele: matrix2){
    for(auto& ele2: ele){
      cin>>ele2;
    }
  }
  
  //변수
  vector<vector<int>> matrix3(N,vector<int>(K));

  //계산
  for(int i=0;i<N;i++){
    for(int j=0;j<K;j++){
      for(int k=0;k<M;k++){
        matrix3[i][j]+=matrix1[i][k]*matrix2[k][j];
      }
    }
  }

  //출력
  for(auto& ele: matrix3){
    for(auto& ele2: ele){
      cout<<ele2<<' ';
    }
    cout<<'\n';
  }
  
 
  return 0;
}