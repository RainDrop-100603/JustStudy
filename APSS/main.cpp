//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// memOver 대비 필요, 특정 조건을 만족하면 바로 ret하게 만들기 
void BLOCKGAME_Input(vector<vector<string>>& board){
  string tmp;
  for(int i=0;i<5;i++){
    cin>>tmp;
    for(int j=0;j<5;j++){
      board[i][j]=tmp[j];
    }
  }
}
char BLOCKGAME_cache(vector<char>& DP_cache, int can_use_bitmask){
  //기저
  if(can_use_bitmask==0){
    return -1;
  }
  //기저 2
  char& result=DP_cache[can_use_bitmask];
  if(result!=-2){
    return result;
  }
  //Algo
  for(int idx=0;idx<25;idx++){
    if((1<<idx)&can_use_bitmask){
      can_use_bitmask-=(1<<idx);
      //오른쪽 끝이 아닐경우, 오른쪽으로 확장 가능
      if((idx%5!=4)&&(1<<(idx+1)&can_use_bitmask)){
        can_use_bitmask-=(1<<(idx+1));
        if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
          result=1;
          return result;
        }
        //오른쪽 윗부분 체크
        if((idx+1-5>0)&&((1<<(idx+1-5))&can_use_bitmask)){
          can_use_bitmask-=(1<<(idx+1-5));
          if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
            result=1;
            return result;
          }
          can_use_bitmask+=(1<<(idx+1-5));
        }
        //오른쪽 아랫부분 체크
        if((idx+1+5<25)&&((1<<(idx+1+5))&can_use_bitmask)){
          can_use_bitmask-=(1<<(idx+1+5));
          if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
            result=1;
            return result;
          }
          can_use_bitmask+=(1<<(idx+1+5));
        }
        //왼쪽 아랫부분 체크
        if((idx+5<25)&&((1<<(idx+5))&can_use_bitmask)){
          can_use_bitmask-=(1<<(idx+5));
          if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
            result=1;
            return result;
          }
          can_use_bitmask+=(1<<(idx+5));
        }
        //왼쪽 윗부분 체크
        if((idx-5>=0)&&((1<<(idx-5))&can_use_bitmask)){
          can_use_bitmask-=(1<<(idx-5));
          if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
            result=1;
            return result;
          }
          can_use_bitmask+=(1<<(idx-5));
        }
        can_use_bitmask+=(1<<(idx+1));
      }
      //맨아래가 아닐경우, 아래로 확장 가능 
      if((idx+5<25)&&((1<<(idx+5))&can_use_bitmask)){
        can_use_bitmask-=(1<<(idx+5));
        if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
          result=1;
          return result;
        }
        can_use_bitmask+=(1<<(idx+5));
      }
      can_use_bitmask+=(1<<idx);
    }
  }
  //결과값 return, 승리한것을 반환하지 못하면 ,패배 했다느 뜻
  result=-1;
  return result;
}
string BLOCKGAME_Algo(vector<vector<string>>& board){
  //DP생성, 비트마스크 생성
  vector<char> DP_cache(1<<25,-2);
  int can_use_bitmask=0;
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      if(board[i][j]=="."){
        can_use_bitmask+=1<<(5*i+j);
      }
    }
  }
  //Algo
  int result=BLOCKGAME_cache(DP_cache,can_use_bitmask);
  if(result==1){
    return string("WINNING");
  }else if(result==-1){
    return string("LOSING");
  }
  return string("ERROR");
}
void BLOCKGAME(){
  //BLOCKGAME
  /*설명 및 입력
  설명
    5×5 크기의 게임판에서 시작해, 둘이 번갈아 가며 블럭을 하나씩 게임판에 내려놓습니다. 
    블럭은 L 모양으로 구성된 3칸짜리 블럭과 2칸짜리 블럭이 있으며, 항상 게임판에 있는 줄에 맞춰 내려놓아야 합니다. 
    블럭들은 서로 겹칠 수 없습니다. 
    각 블록은 자유롭게 뒤집거나 회전해서 올려놓을 수 있습니다. 
    두 사람이 번갈아가며 블록을 올려놓다가 더 올려놓을 수 없게 되면 마지막에 올려놓은 사람이 승리합니다.
    진행 중인 게임판이 주어질 때 이번 차례인 사람이 승리할 수 있는 방법이 있는지를 판단하는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C (C≤50)가 주어집니다. 
    각 테스트 케이스는 다섯 줄에 각 다섯 개의 문자로 구성되며, #는 이미 블록이 놓인 칸, 마침표(.)는 블록이 없는 칸을 의미합니다.
  출력
    각 테스트 케이스마다 한 줄을 출력합니다. 
    이번 차례인 사람이 항상 이길 수 있는 방법이 있다면 WINNING을, 항상 질 수밖에 없다면 LOSING을 출력합니다.
  제한조건
    2초, 64MB
  */
  /*힌트
    대칭게임이므로, 두 사용자가 DP_cache를 공유한다.
    f=max(for(모든 나의행동){나의 행동 & f(남은 게임판에서 상대의 승리여부)}) , 나의승리=1, 상대의 승리=-1
    DP_default: -1
    board를 사용하거나, board를 bitmask로 바꾸어 사용하거나, 둘 중 하나만 하면 된다.
      25칸이므로 bitmask를 사용할 수 있다.
      board를 bijection하는 함수가 필요하다.
    왼쪽위(0,0)부터 오른쪽아래(4,4)로 진행하며, 확장 위치는 각 블록별로 다르게
      2블록은 우측과 아래측
      4블록은 우측 확장후, 위, 아래, 우측위, 우측아래 4방향으로 확장
  */
  /*전략
  전략1
    Dynamic Programing
      정답(큰단위)->작은단위 DP
      f=max(for(모든 나의행동){나의 행동 & f(남은 게임판에서 상대의 승리여부)}) , 나의승리=1, 상대의 승리=-1
        행동: 25번 반복, 블록 확인은 2개(2블록)+4개(3블록) = 6n
        총 연산수(DP_cache크기): bitamsk=2^25 = 2^n
    시간:
      O(2^n * n)
    크기:
      O(2^n)
    sol유의사항
      int로 DP를 만들면 memover가 떠서, char로 바꾸어주었다.
        vector<bitset<1>> 2줄을 이용할 수도 있다.(vector<bool>은 사용하지 않는다) 
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<vector<string>> board(5,vector<string>(5));
    BLOCKGAME_Input(board);
    string result=BLOCKGAME_Algo(board);
    cout<<result<<'\n';
  }
}

int main(void){
  BLOCKGAME();
  return 0;
}