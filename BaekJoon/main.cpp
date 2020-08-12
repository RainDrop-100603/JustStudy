#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>

//#include "GoodFunction.h"

using namespace std;
struct Signal_1520{
  bool right,left,up,down;
  Signal_1520(){}
};
void BK1520(){
//input
  int row,col;
  scanf("%d %d",&row,&col);
  vector<vector<Signal_1520>> table(row,vector<Signal_1520>(col)); //input value
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      scanf("%d",&table[i][j]);
    }
  }
//prepare
  vector<vector<int>> movTable(row,vector<int>(col)); // A(ij)의 값이 1101이면, 3시방향 빼고 이동 가능하다는 뜻(9630)
  int current,right,down;
  //1차 정렬
  for(int i=0;i<row-1;i++){   //끝부분은 경계를 벗어나기 때문에 따로 해준다.
    right=table[i][0];
    for(int j=0;j<col-1;j++){
      current=right;
      right=table[i][j+1];
      down=table[i+1][j];
      if(current>right){
        movTable[i][j+1]+=1000;
      }else if(current<right){
        movTable[i][j]+=10;
      }
      if(current>down){
        movTable[i+1][j]+=1;
      }else if(current<down){
        movTable[i][j]+=100;
      }
    }
    current=right;
    down=table[i][col-1];
    if(current>down){
      movTable[i+1][col-1]+=1;
    }else if(current<down){
      movTable[i][col-1]+=100;
    }
  }
  right=table[row-1][0];
  for(int j=0;j<col-1;j++){
    current=right;
    right=table[row-1][j+1];
    if(current>right){
        movTable[row-1][j+1]+=1000;
      }else if(current<right){
        movTable[row-1][j]+=10;
      }
  }
  //2차 정렬
  current=movTable[0][0];
  if((current/10)%10==1){
    movTable[0][1]=0;
  }else if((current/100)%10==1){
    movTable[1][0]=0;
  }
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      if(i+j==0){
        continue;
      }
      current=movTable[i][j];
      if(current==0){
        movTable[i][j+1]=0;
        movTable[i+1][j]=0;
      }
    }
  }
//calc
  
//output
//   printf("\n\n");
//   for(auto& ele:table){
//     for(auto& ele2:ele){
//       printf("%d ",ele2);
//     }
//     printf("\n");
//   }
  printf("%d\n",table[0][N-1]);
}

int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
//   int N;
//   scanf("%d",&N);
//   while(N--){
    BK11049();
//  }
  
  return 0;
}