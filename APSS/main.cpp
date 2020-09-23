//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;
const int Type[4][3][2]={
  {{0,0},{1,0},{0,1}},
  {{0,0},{1,0},{1,1}},
  {{0,0},{0,1},{1,1}},
  {{0,0},{0,1},{-1,1}}
};
void BoardCoverInput(vector<vector<bool>>& boardTable){
  int height,width;
  cin>>height>>width;
  string tmpS;
  for(int i=0;i<height;i++){
    boardTable.push_back(vector<bool>(width));
    cin>>tmpS;
    for(int j=0;j<width;j++){
      if(tmpS[j]=='#'){
        boardTable[i][j]=false;
      }else{
        boardTable[i][j]=true;
      }
    }
  }
}
bool BoradCoverNoAns(vector<vector<bool>>& boardTable){
  int cnt(0);
  for(auto& ele:boardTable){
    for(auto&& ele2:ele){
      if(ele2){
        cnt++;
      }
    }
  }
  if(cnt%3!=0){
    return true;
  }else{
    return false;
  }
}
int BoardCoverAlgo(vector<vector<bool>>& boardTable){
  /*
  제한시간 2초
  제한메모리 2^16kb=64MB
  전략1
    brute force
      왼쪽 위부터 오른쪽 아래로 가면서 chk 가능, 모양은 4가지 ㄴ, ㄱ, Symmetric ㄴ, Symmetric ㄱ
        중복은 자연히 걸러짐
        타일을 올리면 false로 바꾼다.
        (x,y)기준, (x,y)&(x,y+1)&(x+1,y+1), (x,y)&(x,y+1)&(x-1,y+1), (x,y)&(x+1,y)&(x+1,y+1), (x,y)&(x,y+1)&(x+1,y)
      first position을 찾는다
        기저: 찾지 못하면 first==-1, return 1;
        first 포지션의 4방향을 search
          4모양 모두 불가능 하면 return 0;
          가능하다면 재귀
    time complexity
      4^(width*height/3)<=10^60
    mem complexity
      width*height<=400
   
  */
  //first position
  int height=boardTable.size();
  int width=boardTable[0].size();
  int xpos=-1,ypos=-1;
  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
      if(boardTable[i][j]){
        xpos=j;
        ypos=i;
        i=height;
        break;
      }
    }
  }
  //기저
  if(xpos==-1){
    return 1;
  }
  //Algo
  int result(0);
  bool xp1(xpos+1<width),xm1(xpos>0),yp1(ypos+1<height);
  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      
    }
  }
  if(xp1&&yp1){
    if(boardTable[xpos+1][ypos+1]&&boardTable[xpos][ypos+1]){
      boardTable[xpos][ypos]=boardTable[xpos+1][ypos+1]=boardTable[xpos][ypos+1]=false;
      result+=BoardCoverAlgo(boardTable);
      boardTable[xpos][ypos]=boardTable[xpos+1][ypos+1]=boardTable[xpos][ypos+1]=true;
    }
    if(boardTable[xpos+1][ypos]&&boardTable[xpos+1][ypos+1]){
      boardTable[xpos][ypos]=boardTable[xpos+1][ypos]=boardTable[xpos+1][ypos+1]=false;
      result+=BoardCoverAlgo(boardTable);
      boardTable[xpos][ypos]=boardTable[xpos+1][ypos]=boardTable[xpos+1][ypos+1]=true;
    }
    if(boardTable[xpos+1][ypos]&&boardTable[xpos][ypos+1]){
      boardTable[xpos][ypos]=boardTable[xpos+1][ypos]=boardTable[xpos][ypos+1]=false;
      result+=BoardCoverAlgo(boardTable);
      boardTable[xpos][ypos]=boardTable[xpos+1][ypos]=boardTable[xpos][ypos+1]=true;
    }
  }
  if(xm1&&yp1){
    if(boardTable[xpos-1][ypos+1]&&boardTable[xpos][ypos+1]){
      boardTable[xpos][ypos]=boardTable[xpos-1][ypos+1]=boardTable[xpos][ypos+1]=false;
      result+=BoardCoverAlgo(boardTable);
      boardTable[xpos][ypos]=boardTable[xpos-1][ypos+1]=boardTable[xpos][ypos+1]=true;
    }
  }
  return result;
}

void BoardCover(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    //true=white, false=black;
    vector<vector<bool>> boardTable;
    BoardCoverInput(boardTable);
    if(BoradCoverNoAns(boardTable)){
      cout<<"0\n";
    }else{
      cout<<BoardCoverAlgo(boardTable)<<"\n";
    }
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  BoardCover();

  return 0;
}