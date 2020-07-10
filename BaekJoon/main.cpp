#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

// #include "GoodFunction.h"

using namespace std;

void Divide(vector<vector<int>>& table, pair<int,int> p, int size, int& white, int& blue){
  int x(p.first),y(p.second);
  bool oneColor=true; //모두 색이 같은 색종이인가
  int color=table[x][y]; //1=blue, 0=white
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      if(table[x+i][y+j]!=color){
        oneColor=false;
        i=size; //바깥 루프조건 탈출
        break;  //안쪽 루프 탈출 
      }
    }
  }
  if(oneColor){
    if(color){
      blue++;
    }else{
      white++;
    }
    return;
  }
  Divide(table,make_pair(x,y),size/2,white,blue);
  Divide(table,make_pair(x+size/2,y),size/2,white,blue);
  Divide(table,make_pair(x,y+size/2),size/2,white,blue);
  Divide(table,make_pair(x+size/2,y+size/2),size/2,white,blue);
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
  int blue(0),white(0);
  
  //계산
  Divide(table,make_pair(0,0),N,white,blue);
  
  //출력
  cout<<white<<endl<<blue;
  
 
  return 0;
}