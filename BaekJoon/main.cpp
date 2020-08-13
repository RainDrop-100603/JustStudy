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
  bool empty(){
    return !(right||left||up||down);
  }
  void SetZero(){
    right=false;
    left=false;
    up=false;
    down=false;
  }
  Signal_1520(){}
};
void RightChk(int current,int right,Signal_1520* cp,Signal_1520* rp){
  if(current>right){
    rp->left=true;
  }else if(current<right){
    cp->right=true;
  }
}
void DownChk(int current,int down,Signal_1520* cp,Signal_1520* dp){
  if(current>down){
    dp->up=true;
  }else if(current<down){
    cp->down=true;
  }
}
int lookAround(vector<vector<Signal_1520>>& table,int i, int j){
  int sum=0;
  Signal_1520* obj=&table[i][j];
  if(i+j==0){
    return 1;
  }else if(obj->empty()){
    return 0;
  }
  if(obj->right){
    sum+=lookAround(table,i,j+1);
  }
  if(obj->left){
    sum+=lookAround(table,i,j-1);
  }
  if(obj->up){
    sum+=lookAround(table,i-1,j);
  }
  if(obj->down){
    sum+=lookAround(table,i+1,j);
  }
  return sum;
}
void BK1520_Memover(){
//input
  int row,col;
  scanf("%d %d",&row,&col);
  vector<vector<int>> table(row,vector<int>(col)); //input value
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      scanf("%d",&table[i][j]);
    }
  }
//prepare
  vector<vector<Signal_1520>> movTable(row,vector<Signal_1520>(col)); // A(ij)의 값이 1101이면, 3시방향 빼고 이동 가능하다는 뜻(9630)
  int current,right,down;
  Signal_1520* cSig;  //current Signal
  //1차 정렬
  for(int i=0;i<row;i++){   //끝부분은 경계를 벗어나기 때문에 따로 해준다.
    right=table[i][0];
    for(int j=0;j<col;j++){
      current=right;
      if(i==row-1&&j==col-1){
        continue;
      }else if(i==row-1){
        right=table[i][j+1];
        RightChk(current,right,&movTable[i][j],&movTable[i][j+1]);
      }else if(j==col-1){
        down=table[i+1][j];
        DownChk(current,down,&movTable[i][j],&movTable[i+1][j]);
      }else{
        right=table[i][j+1];
        down=table[i+1][j];
        RightChk(current,right,&movTable[i][j],&movTable[i][j+1]);
        DownChk(current,down,&movTable[i][j],&movTable[i+1][j]);
      }
    }
  }
  //2차 정렬
  for(int i=0;i<row;i++){   //끝부분은 경계를 벗어나기 때문에 따로 해준다.
    for(int j=0;j<col;j++){
      cSig=&movTable[i][j];
      if(i+j==0){
        if(cSig->right){
          movTable[0][1].SetZero();
        }
        if(cSig->down){
          movTable[1][0].SetZero();
        }
      }else if(i==row-1&&j==col-1){
        continue;
      }else if(i==row-1){
        if(cSig->empty()){
          movTable[i][j+1].left=false;
        }
      }else if(j==col-1){
        if(cSig->empty()){
          movTable[i+1][j].up=false;
        }
      }else{
        if(cSig->empty()){
          movTable[i][j+1].left=false;
          movTable[i+1][j].up=false;
        }
      }
    }
  }
  //목적지가 막혀있으면 막다른 지점
//calc
  int sum;
  sum=lookAround(movTable,row-1,col-1);
//output
  printf("%d\n",sum);
}
void RightChk2(int current,int right,int& cp,int& rp){
  if(current>right){
    rp+=1000;
  }else if(current<right){
    cp+=10;
  }
}
void DownChk2(int current,int down,int& cp,int& dp){
  if(current>down){
    dp+=1;
  }else if(current<down){
    cp+=100;
  }
}
int lookAround2(vector<vector<int>>& table,int i, int j){
  int sum=0;
  int obj=table[i][j];
  if(i+j==0){
    return 1;
  }else if(obj==0){
    return 0;
  }
  if((obj/10)%10){
    sum+=lookAround2(table,i,j+1);
  }
  if(obj/1000){
    sum+=lookAround2(table,i,j-1);
  }
  if(obj%10){
    sum+=lookAround2(table,i-1,j);
  }
  if((obj/100)%10){
    sum+=lookAround2(table,i+1,j);
  }
  return sum;
}
void BK1520_Timeover(){
//input
  int row,col;
  scanf("%d %d",&row,&col);
  vector<vector<int>> table(row,vector<int>(col)); //input value
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      scanf("%d",&table[i][j]);
    }
  }
//prepare
  vector<vector<int>> movTable(row,vector<int>(col)); // A(ij)의 값이 1101이면, 3시방향 빼고 이동 가능하다는 뜻(9630)
  int current,right,down;
  int cSig;  //current Signal
  //1차 정렬
  for(int i=0;i<row;i++){   //끝부분은 경계를 벗어나기 때문에 따로 해준다.
    right=table[i][0];
    for(int j=0;j<col;j++){
      current=right;
      if(i==row-1&&j==col-1){
        continue;
      }else if(i==row-1){
        right=table[i][j+1];
        RightChk2(current,right,movTable[i][j],movTable[i][j+1]);
      }else if(j==col-1){
        down=table[i+1][j];
        DownChk2(current,down,movTable[i][j],movTable[i+1][j]);
      }else{
        right=table[i][j+1];
        down=table[i+1][j];
        RightChk2(current,right,movTable[i][j],movTable[i][j+1]);
        DownChk2(current,down,movTable[i][j],movTable[i+1][j]);
      }
    }
  }
  //2차 정렬
  for(int i=0;i<row;i++){   //끝부분은 경계를 벗어나기 때문에 따로 해준다.
    for(int j=0;j<col;j++){
      cSig=movTable[i][j];
      if(i+j==0){
        if((cSig/10)%10){
          movTable[0][1]=0;
        }
        if((cSig/100)%10){
          movTable[1][0]=0;
        }
      }else if(i==row-1&&j==col-1){
        continue;
      }else if(i==row-1){
        if(cSig==0){
          movTable[i][j+1]%=1000;
          //movTable[i][j+1].left=false;
        }
      }else if(j==col-1){
        if(cSig==0){
          movTable[i+1][j]=(movTable[i+1][j]/10)*10;
          //movTable[i+1][j].up=false;
        }
      }else{
        if(cSig==0){
          movTable[i][j+1]%=1000;
          movTable[i+1][j]=(movTable[i+1][j]/10)*10;
          // movTable[i][j+1].left=false;
          // movTable[i+1][j].up=false;
        }
      }
    }
  }
  //목적지가 막혀있으면 막다른 지점
//calc
  int sum;
  sum=lookAround2(movTable,row-1,col-1);
//output
  for(auto& ele:movTable){
    for(auto& ele2:ele){
      printf("%d ",ele2);
    }
    printf("\n");
  }
  //printf("%d\n",sum);
}
int DFS(vector<vector<int>>& table, vector<vector<int>>& movTable, int i, int j,int row,int col){
  int now=movTable[i][j];
  if(now>-1){  //0이상이면 이미 탐색을 마친 것
    return now;
  }
  int sum=0;
  int value=table[i][j];
  if(i+1<row){
    if(table[i+1][j]<value){
      sum+=DFS(table,movTable,i+1,j,row,col);
    }
  }
  if(i-1>=0){
    if(table[i-1][j]<value){
      sum+=DFS(table,movTable,i-1,j,row,col);
    }
  }
  if(j+1<col){
    if(table[i][j+1]<value){
      sum+=DFS(table,movTable,i,j+1,row,col);
    }
  }
  if(j-1>=0){
    if(table[i][j-1]<value){
      sum+=DFS(table,movTable,i,j-1,row,col);
    }
  }
  movTable[i][j]=sum;
  return sum;
}
void BK1520_H_DFS(){
//input
  int row,col;
  scanf("%d %d",&row,&col);
  vector<vector<int>> table(row,vector<int>(col)); //input value
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      scanf("%d",&table[i][j]);
    }
  }
//prepare
  vector<vector<int>> movTable(row,vector<int>(col)); // -1은 미방문, 양수일 경우 방문횟수
  for(auto& ele:movTable){
    for(auto& ele2:ele){
      ele2=-1;
    }
  }
  movTable[row-1][col-1]=1;
//calc
  DFS(table,movTable,0,0,row,col);
//output
  // for(auto& ele:movTable){
  //   for(auto& ele2:ele){
  //     printf("%d ",ele2);
  //   }
  //   printf("\n");
  // }
  printf("%d\n",movTable[0][0]);

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
    BK1520_H_DFS();
//  }
  
  return 0;
}