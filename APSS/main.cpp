//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// 전략 짜는것 완벽했음
void BLOCKGAME_Input(vector<int>& board){
  int tmp;
  cin>>tmp;
  board.resize(tmp);
  for(auto& ele: board){
    cin>>ele;
  }
}
int BLOCKGAME_cache(const vector<int>& board, vector<vector<int>>& DP_cache, int left, int len){
  //기저
  if(len==0){
    return 0;
  }
  //기저 2
  int& result=DP_cache[left][len];
  if(result!=-50001){
    return result;
  }
  //Algo
  if(len>=2){
    result=max(result,-1*BLOCKGAME_cache(board,DP_cache,left+2,len-2)); //왼쪽 두개 삭제
    result=max(result,-1*BLOCKGAME_cache(board,DP_cache,left,len-2)); //오른쪽 두개 삭제
  }
  result=max(result,board[left]-BLOCKGAME_cache(board,DP_cache,left+1,len-1));  //왼쪽 하나 챙기기
  result=max(result,board[left+len-1]-BLOCKGAME_cache(board,DP_cache,left,len-1));  //오른쪽 하나 챙기기
  return result;
}
int BLOCKGAME_Algo(const vector<int>& board){
  //DP생성
  int boardLen=board.size();
  vector<vector<int>> DP_cache(boardLen,vector<int>(boardLen+1,-50001));
  //Algo, 
  return BLOCKGAME_cache(board,DP_cache,0,boardLen);
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
    25칸이므로 bitmask를 사용할 수 있다.
    board를 bijection하는 함수가 필요하다.
    왼쪽위(0,0)부터 오른쪽아래(4,4)로 진행하며, 확장 위치는 각 블록별로 다르게
      2블록은 우측과 아래측
      4블록은 밥먹고와서 체킹 (우선 모든 모습을 생각하자 )
  */
  /*전략
  전략1
    Dynamic Programing
      정답(큰단위)->작은단위 DP
      f=max(for(모든 나의행동){나의 행동 & f(남은 게임판에서 상대의 승리여부)}) , 나의승리=1, 상대의 승리=-1
        행동: 25번 반복, 블록 확인은 2개(2블록)+
        총 연산수(DP_cache크기): bitamsk=2^25 = 2^n
      DP_cache 표현방법
        DP_cache[left][len]=left번째 부터 len길이만큼 이어져 있는 board
        크기=n^2
        default: -50001
    시간:
      O(n^2)
    크기:
      O(n^2)
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<int> board;
    BLOCKGAME_Input(board);
    int result=BLOCKGAME_Algo(board);
    cout<<result<<'\n';
  }
}

int main(void){
  BLOCKGAME();
  return 0;
}