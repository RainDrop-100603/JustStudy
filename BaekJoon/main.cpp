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
  int K,N;
  cin>>N>>K;
  int modValue=1000000007;
  
  //변수
  vector<vector<int>> table(2,vector<int>(K+1));
  bool first=true;  //fist면 첫번째     
  table[0][0]=1;    //0C0 초기값, 값이 바뀔일어 없다
  table[1][0]=1;    //1C0 초기값, 값이 바뀔일이 없다
  //계산
  for(int i=1;i<=K;i++){
    first=!first;   //바꾸기
    if(first){
      table[0][i]=1;
      for(int j=1;j<i;j++){
        table[0][j]=(table[1][j-1]+table[1][j])%modValue;
      }
    }else{
      table[1][i]=1;
      for(int j=1;j<i;j++){
        table[1][j]=(table[0][j-1]+table[0][j])%modValue;
      }
    }
  }
  
  
  //출력
  if(first){
    cout<<table[0][K];
  }else{
    cout<<table[1][K];
  }
  
 
  return 0;
}