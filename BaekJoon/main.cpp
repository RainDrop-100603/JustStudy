#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

// #include "GoodFunction.h"

using namespace std;

void Divide(vector<vector<int>>& table, pair<int,int> p, int size, int& one, int& zero, int& mOne){
  int x(p.first),y(p.second);
  bool oneValue=true; //모두 색이 같은 색종이인가
  int value=table[x][y]; //1=blue, 0=white
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      if(table[x+i][y+j]!=value){
        oneValue=false;
        i=size; //바깥 루프조건 탈출
        break;  //안쪽 루프 탈출 
      }
    }
  }
  if(oneValue){
    if(value==1){
      one++;
    }else if(value==0){
      zero++;
    }else{
      mOne++;
    }
    return;
  }
  Divide(table,make_pair(x,y),size/3,one,zero,mOne);Divide(table,make_pair(x,y+size/3),size/3,one,zero,mOne);Divide(table,make_pair(x,y+size*2/3),size/3,one,zero,mOne);
  Divide(table,make_pair(x+size/3,y),size/3,one,zero,mOne);Divide(table,make_pair(x+size/3,y+size/3),size/3,one,zero,mOne);Divide(table,make_pair(x+size/3,y+size*2/3),size/3,one,zero,mOne);
  Divide(table,make_pair(x+size*2/3,y),size/3,one,zero,mOne);Divide(table,make_pair(x+size*2/3,y+size/3),size/3,one,zero,mOne);Divide(table,make_pair(x+size*2/3,y+size*2/3),size/3,one,zero,mOne);
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  int N;
  cin>>N;
  vector<vector<int>> table(N,vector<int>(N)); //N*N 배열
  for(auto& ele:table){
    for(auto& ele2:ele){
      cin>>ele2;
    }
  }
  
  //변수
  int one(0),zero(0),mOne(0);
  
  //계산
  Divide(table,make_pair(0,0),N,one,zero,mOne);
  
  //출력
  cout<<mOne<<endl<<zero<<endl<<one;
  
 
  return 0;
}