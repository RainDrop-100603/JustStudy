#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

// #include "GoodFunction.h"

using namespace std;


int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  int N, M;
  char color;
  cin>>N>>M;
  //true가 새로 칠해야 하는 색
  bool** tableW=new bool*[N];
  for(int i=0;i<M;i++){
    tableW[i]= new bool[M];
  }
  bool** tableB=new bool*[N];
  for(int i=0;i<M;i++){
    tableB[i]= new bool[M];
  }

  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      cin>>color;
      if((i+j)%2==0){
        if(color=='B'){
          tableW[i][j]=true;
        }else{
          tableB[i][j]=true;
        }
      }else{
        if(color=='B'){
          tableB[i][j]=true;
        }else{
          tableW[i][j]=true;
        }
      }
    }
  }

  int minB;  //B에서의 최솟값
  int sumB;   //B에서 현재 체스판에서의 값
  int leftB=0;    //B의 leftest의 값 
  int leftW=0;
  int minW;
  int sumW;

  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(tableB[i][j]){
        leftB++;
      }
      if(tableW[i][j]){
        leftW++;
      }
    }
  }
  minB=leftB;
  minW=leftW;

  for(int i=0;i<N-8;i++){
    sumB=leftB;
    sumW=leftW;
    for(int j=1;j<M-8;j++){
      for(int k=0;k<8;k++){
        if(tableB[k][j+7]){
          sumB--;
        }
        if(tableB[k][j+7]){
          sumB++;
        }
        if(tableW[k][j+7]){
          sumW--;
        }
        if(tableW[k][j+7]){
          sumW++;
        }
      }
      if(sumB<minB){
        minB=sumB;
      }
      if(sumW<minW){
        minW=sumW;
      }
    }
    //leftB를 한칸 올려야한다.
  }


  for(int i=0;i<M;i++){
    delete[] tableW[i];
  }
  delete[] tableW;
  for(int i=0;i<M;i++){
    delete[] tableB[i];
  }
  delete[] tableB;
  return 0;
}

