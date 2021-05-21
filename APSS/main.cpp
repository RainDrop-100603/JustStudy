//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <queue>
#include <ctime>

using namespace std;

// /* combination, Constraint Satisfaction Problem, 두가지 버전 비교해보기
void DARPA_Input(vector<vector<int>>& board, vector<vector<int>>& hint){
  int boardSize,hintSize;
  cin>>boardSize;
  board=vector<vector<int>>(boardSize,vector<int>(boardSize));
  for(auto& row:board){
    for(auto& ele:row){
      cin>>ele;
    }
  }
  cin>>hintSize;
  for(int i=0;i<hintSize;i++){
    vector<int> tmp(4);
    for(auto& ele:tmp){
      cin>>ele;
    }
    hint.push_back(tmp);
  }
}
void DARPA_preTreat(vector<vector<int>>& board,vector<vector<int>>& hint){
  //board: -1: 하얀색, 0: 검은색 or 힌트 
  for(auto& row:board){
    for(auto& ele:row){
      if(ele){ //white
        ele=-1;
      }
    }
  }
  //hint: yAxis, xAxis, direction(0:h, 1:v), clue, bitmask_canInput, 남은 공간 (remain)
  //hint update(bitmask추가), x와 y좌표가 0부터 시작하도록 수정, 남은 공간 추가
  for(auto& ele: hint){
    ele[0]--;
    ele[1]--;
    ele.push_back((1<<10)-2);  //hint 끝에 넣을 수 있는 원소 추가(bitmask), default=111,111,111,0
    int remain(0),yAxis(ele[0]),xAxis(ele[1]);
    if(ele[2]==0){  //horizontal
      for(xAxis=ele[1]+1;xAxis<board.size();xAxis++){
        if(board[yAxis][xAxis]==-1){
          remain++;
        }else{
          break;
        }
      }
    }else{  //vertical
      for(yAxis=ele[0]+1;yAxis<board.size();yAxis++){
        if(board[yAxis][xAxis]==-1){
          remain++;
        }else{
          break;
        }
      }
    }
    ele.push_back(remain);
  }
}
vector<vector<int>> DARPA_Algo(vector<vector<int>> board,vector<vector<int>> hint){
  //전처리
    //hint: yAxis, xAxis, direction(0:h, 1:v), clue, bitmask_canInput, 남은 공간 (remain)
    //board: -1: 하얀색, 0: 검은색 or 힌트
  DARPA_preTreat(board,hint);
    //hint_remain_arr: hint를 remain기준으로 정렬
  vector<vector<int>> hint_remain_arr(10);
  for(int idx=0;idx<hint.size();idx++){
    hint_remain_arr[(hint[idx][5])].push_back(idx);
  }
    //board_hint: table[i][j]=(i,j)에 해당하는 hint:pair(horizontal,vertical)
  vector<vector<pair<int,int>>> board_hint(board.size(),vector<pair<int,int>>(board.size()));
  for(int yAxis=0;yAxis<board.size();yAxis++){
    for(int xAxis=0;xAxis<board.size();xAxis++){
      if(board[yAxis][xAxis]==-1){
        board_hint[yAxis][xAxis]=DARPA_hintChk(board,hint,xAxis,yAxis);
      }
    }
  }
  //Algo
  DARPA_func(board,hint,hint_remain_arr,board_hint);
  //return
  return board;
}
void DARPA(){
  //DARPA
  /*설명 및 입력
  설명
    DARPA Grand Challenge 는 운전자 없는 차들을 컴퓨터 인공지능으로 조작해 누가 먼저 결승점에 도달하느냐를 가지고 겨루는 인공지능 대회입니다. 
      2004년 DARPA Grand Challenge 의 과제는 사막을 가로지르는 240km 도로를 완주하는 것이었습니다.
    우리는 이 경기를 N 개의 카메라로 중계하려고 합니다. 이 도로에는 카메라를 설치할 수 있는 곳이 M 군데 있습니다. 
      여기에 카메라를 배치하여, 가장 가까운 두 카메라 간의 간격을 최대화하고 싶습니다. 이와 같은 배치를 찾아내는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C (<= 50) 이 주어집니다. 
    각 테스트 케이스의 첫 줄에는 카메라의 개수 N (<= 100) 과 설치 가능한 중계소의 수 M (N <= M <= 200) 이 주어집니다. 
    그 다음 줄에는 M 개의 실수로, 카메라를 설치 가능한 곳의 위치가 오름 차순으로 주어집니다. 
    각 위치는 시작점에서부터의 거리로, 240 이하의 실수이며 소숫점 둘째 자리까지 주어질 수 있습니다.
  출력
    각 테스트 케이스마다 가장 가까운 두 카메라 간의 최대 간격을 소수점 셋째 자리에서 반올림해 출력합니다.
  제한조건
    20초, 64MB
  */
  /*힌트
    결정 문제
      접근방법
        결정문제: 거리가 x이상일 때, y이상의 카메라를 설치할 수 있는가?
        거리 x는 이분법을 이용하여 구함 -> 두 카메라포인트간 간격이 매우 작을경우 문제 발생
          발생할 수 있는 문제는, 최소/최대 위치를 실제 카메라간 거리로 정하면 된다.
          이로인해 최소==최대가 되면, 함수를 종결시킨다.
    가능한 카메라의 위치는 정해져 있다 -> 각 카메라포인트간 거리를 모두 특정 행렬에 저장한다.
      이분법에서 거리를 정할 때, 이 값을 이용한다.
  */
  /*전략
  전략1
    Decision Problem
    접근방법
      카메라포인트간의 거리를 모두 구해 "배열1"에 정렬한다.
      재귀 결정: 거리의 최소/최댓값이 주어질 때, y개 이상의 카메라를 설치할 수 있는가?
        조건: (최소+최대)/2인 "x"에 대해, y개 카메라 이상을 설치할 수 있는가
          참: 최소="배열1"의 값중 "x"이하의 최댓값, 으로 바꾸고 재귀 
          거짓: 최대="배열1"의 값 중 "x"이상의 최솟값, 으로 바꾸고 재귀 
        기저: 최솟값 == 최댓값이라면, 해당 값을 반환
          만약 답을 찾지 못한 경우, -1을 반환
    시간부터 추가바람 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    시간:
      O(9^(N^2)) & optimize 
    크기:
      O(N^2), N:게임판의 크기 
    보완 & 참고
      validChk를 보면, 더 자세한 heuristic(validChk2)이 단순한 heuristic보다 수행시간이 더 긴 것을 확인할 수 있다.
      책의 방식을 참고하여 더 최적화도 가능하다.
        대체로 책의 방식이 더 직관적이고 구현이 간단한 듯 하다.
      제약 충족 문제(Constraint Satisfaction Problem), 종만북 1 436p 참고
  전략2
    나의방식(전략1)과 종만북을 참고하여 개선한 버전 
    남은 공간, bitmask사용법이 다소 바뀌었다.
    2000ms -> 72ms로 감소 
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<vector<int>> board,hint;
    DARPA_Input(board,hint);
    auto result=DARPA_Algo2(board,hint);
    for(auto& row:result){
      for(auto& ele:row){
        cout<<ele<<" ";
      }cout<<"\n";
    }
  }
}

int main(void){
   //clock_t start,end;
   //start=clock();
  DARPA();
   //end=clock();;
   //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}