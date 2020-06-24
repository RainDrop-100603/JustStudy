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
  string str1;
  string str2;
  cin>>str1>>str2;

  //변수
  int len1=str1.length();
  int len2=str2.length();
  vector<vector<int>> table(len1,vector<int>(len2));

  //table 초기값 
  if(str1[0]==str2[0]){
    table[0][0]=1;
  }else{
    table[0][0]=0;
  }
  for(int i=1;i<len1;i++){
    if(str1[i]==str2[0]){
      table[i][0]=1;
    }else{
      table[i][0]=table[i-1][0];
    }
  }
  for(int i=1;i<len2;i++){
    if(str2[i]==str1[0]){
      table[0][i]=1;
    }else{
      table[0][i]=table[0][i-1];
    }
  }

  //table 채우기
  for(int i=1;i<len1;i++){
    for(int j=1;j<len2;j++){
      if(str1[i]==str2[j]){
        table[i][j]=table[i-1][j-1]+1;
      }else{
        table[i][j]=max(table[i][j-1],table[i-1][j]);
      }
    }
  }
  cout<<table[len1-1][len2-1];
  return 0;
}

