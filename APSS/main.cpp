//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// 연산자 확인, pseudo-code 잘 짜기 
void NUMBERGAME_Input(vector<int>& board){
  int tmp;
  cin>>tmp;
  board.resize(tmp);
  for(auto& ele: board){
    cin>>ele;
  }
}
int NUMBERGAME_cache(const vector<int>& board, vector<vector<int>>& DP_cache, int left, int len){
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
    result=max(result,-1*NUMBERGAME_cache(board,DP_cache,left+2,len-2)); //왼쪽 두개 삭제
    result=max(result,-1*NUMBERGAME_cache(board,DP_cache,left,len-2)); //오른쪽 두개 삭제
  }
  result=max(result,board[left]-NUMBERGAME_cache(board,DP_cache,left+1,len-1));  //왼쪽 하나 챙기기
  result=max(result,board[left+len-1]-NUMBERGAME_cache(board,DP_cache,left,len-1));  //오른쪽 하나 챙기기
  return result;
}
int NUMBERGAME_Algo(const vector<int>& board){
  //DP생성
  int boardLen=board.size();
  vector<vector<int>> DP_cache(boardLen,vector<int>(boardLen+1,-50001));
  //Algo, 
  return NUMBERGAME_cache(board,DP_cache,0,boardLen);
}
void NUMBERGAME(){
  //NUMBERGAME
  /*설명 및 입력
  설명
    n개의 정수를 일렬로 늘어놓은 게임판을 가지고 현우와 서하가 게임을 합니다. 게임은 현우부터 시작해서 번갈아가며 진행하며, 각 참가자는 자기 차례마다 두 가지 일 중 하나를 할 수 있습니다.
      게임판의 왼쪽 끝에 있는 숫자나 오른쪽 끝에 있는 숫자 중 하나를 택해 가져갑니다. 가져간 숫자는 게임판에서 지워집니다.
      게임판에 두 개 이상의 숫자가 있을 경우, 왼쪽 끝에서 2개, 혹은 오른쪽 끝에서 2개를 지웁니다.
    게임은 모든 숫자가 다 없어졌을 때 끝나며, 각 사람의 점수는 자신이 가져간 숫자들의 합입니다. 
    두 사람 모두 최선을 다할 때, 두 사람의 최종 점수 차이는 얼마일까요?
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 이 주어집니다. 
    각 테스트 케이스의 첫 줄에는 게임판의 길이 n (1 <= n <= 50) 이 주어지며, 그 다음 줄에 n 개의 정수로 게임판의 숫자들이 순서대로 주어집니다. 
    각 숫자는 -1,000 에서 1,000 사이의 정수입니다.
  출력
    각 테스트 케이스마다 한 줄로, 두 사람이 최선을 다했을 때 현우가 서하보다 몇 점 더 얻을 수 있는지를 출력합니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    대칭게임이므로, 두 사용자가 DP_cache를 공유한다.
    f=for(모든행동){행동으로 얻은 점수 - f(남은 게임판에서의 상대의 최적 행동)}
    DP_default: -1000*50-1=-50001
  */
  /*전략
  전략1
    Dynamic Programing
      정답(큰단위)->작은단위 DP
      f=for(모든행동){행동으로 얻은 점수 - f(남은 게임판에서의 상대의 최적 행동)}  이용
        행동: 2*2종류
        총 연산수(DP_cache크기): sum(1개가 있을 위치 ~ 연속된 n개가 있을 위치) == sum(n~1)= n^2
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
    NUMBERGAME_Input(board);
    int result=NUMBERGAME_Algo(board);
    cout<<result<<'\n';
  }
}

int main(void){
  NUMBERGAME();
  return 0;
}