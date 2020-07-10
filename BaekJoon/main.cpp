#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

// #include "GoodFunction.h"

using namespace std;

void Divide2(vector<vector<char>>& table, pair<int,int> p, int size){

  int x(p.first),y(p.second);
  bool oneBit=true; //모두 색이 같은 색인가
  int bit=table[x][y]; //1=blue, 0=white
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      if(table[x+i][y+j]!=bit){
        oneBit=false;
        i=size; //바깥 루프조건 탈출
        break;  //안쪽 루프 탈출 
      }
    }
  }
  if(oneBit){
    if(bit=='1'){
      cout<<1;
    }else{
      cout<<0;
    }
    return;
  }else{
    cout<<'(';  //새로운 divide가 생길때 마다 괄호가 추가된다.
    Divide2(table,make_pair(x,y),size/2);
    Divide2(table,make_pair(x,y+size/2),size/2);
    Divide2(table,make_pair(x+size/2,y),size/2);
    Divide2(table,make_pair(x+size/2,y+size/2),size/2);
  }


  cout<<')';  //divide 완료 시 닫기
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  int N;
  cin>>N;
  vector<vector<char>> table(N,vector<char>(N)); //N*N 배열
  for(auto& ele:table){
    for(auto& ele2:ele){
      cin>>ele2;
    }
  }
  
  //변수
  
  //계산
  Divide2(table,make_pair(0,0),N);
  
  //출력
 
  return 0;
}