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

//https://www.youtube.com/watch?v=x7STjpcKZP8 
//사회복무요원 교육 

// greedy, atan2 함수, 원에서의 각도를 이용할땐, 2pi마다 반복되는것을 고려하고 정규화, 자료형 잘 확인하기  
void BOARDCOVER2_Input(vector<vector<char>>& board, vector<vector<char>>& block){
  int height,width,row,column;
  cin>>height>>width>>row>>column;
  board=vector<vector<char>>(height,vector<char>(width));
  block=vector<vector<char>>(row,vector<char>(column));
  for(auto& eleRow:board){
    for(auto& eleCol:eleRow){
      cin>>eleCol;
    }
  }
  for(auto& eleRow:block){
    for(auto& eleCol:eleRow){
      cin>>eleCol;
    }
  }
}
vector<vector<char>> BOARDCOVER2_block_LRreverse(const vector<vector<char>>& block){
  vector<vector<char>> tmp;
  for(auto ele:block){
    reverse(ele.begin(),ele.end());
    tmp.push_back(ele);
  }
  return tmp;
}
vector<vector<char>> BOARDCOVER2_block_UDreverse(const vector<vector<char>>& block){
  vector<vector<char>> tmp;
  for(auto iter=block.rbegin();iter!=block.rend();iter++){
    tmp.push_back(*iter);
  }
  return tmp;
}
vector<vector<char>> BOARDCOVER2_block_turn(const vector<vector<char>>& block){
  vector<vector<char>> block_turn(block[0].size(),vector<char>(block.size()));
  for(int row=0;row<block_turn.size();row++){
    for(int col=0;col<block_turn[0].size();col++){
      block_turn[row][col]=block[col][row];
    }
  }
  return block_turn;
}
void BOARDCOVER2_BlockArr_input(vector<vector<vector<char>>>& block_arr, const vector<vector<char>>& block){
  bool canInput(true);
  for(auto& ele: block_arr){
    //row나 col의 길이가 다르면 생략
    if(block.size()!=ele.size()||block[0].size()!=ele[0].size()){
      continue;
    }
    //중복체크
    canInput=false;
    for(int row=0;row<ele.size();row++){
      for(int col=0;col<ele[0].size();col++){
        if(block[row][col]!=ele[row][col]){
          canInput=true;
          row=ele.size(); //두개의 for문을 탈출하기 위함
          break;
        }
      }
    }
    if(!canInput) break;
  }
  if(canInput){
    block_arr.push_back(block);
  }
}
vector<vector<vector<char>>> BOARDCOVER2_BlockArr(const vector<vector<char>>& block){
  vector<vector<vector<char>>> block_arr,result;
  block_arr.push_back(block);
  BOARDCOVER2_BlockArr_input(block_arr,BOARDCOVER2_block_turn(block));
  for(const auto& ele:block_arr){
    BOARDCOVER2_BlockArr_input(result,ele);
    BOARDCOVER2_BlockArr_input(result,BOARDCOVER2_block_LRreverse(ele));
    BOARDCOVER2_BlockArr_input(result,BOARDCOVER2_block_UDreverse(ele));
    BOARDCOVER2_BlockArr_input(result,BOARDCOVER2_block_LRreverse(BOARDCOVER2_block_UDreverse(ele)));
  }
  return result;
}
bool BOARDCOVER2_board_can_input(const vector<vector<char>>& board, const vector<vector<char>>& block,int row,int col){
  //block이 벗어날 때 
  if(row+block.size()>board.size()||col+block[0].size()>board[0].size()){
    return false;
  }
  //중복체크
  for(int i=0;i<block.size();i++){
    for(int j=0;j<block[0].size();j++){
      if(board[row+i][col+j]&block[i][j]){
        return false;
      }
    }
  }
  return true;
}
void BOARDCOVER2_board_input(vector<vector<char>>& board, const vector<vector<char>>& block,int row,int col){
  for(int i=0;i<block.size();i++){
    for(int j=0;j<block[0].size();j++){
      board[row+i][col+j]+=block[i][j];
    }
  }
}
void BOARDCOVER2_board_output(vector<vector<char>>& board, const vector<vector<char>>& block,int row,int col){
  for(int i=0;i<block.size();i++){
    for(int j=0;j<block[0].size();j++){
      board[row+i][col+j]-=block[i][j];
    }
  }
}
int BOARDCOVER2_func(vector<vector<char>>& board, const vector<vector<vector<char>>>& block_arr, int& tmp_max,pair<int,int> heuristic1,vector<vector<int>>& heuristic2,int prev_value,int now_idx){
  int board_row(board.size()),board_col(board[0].size());
  int row(now_idx/board_col),col(now_idx%board_col);
  int block_row(block_arr[0].size()),block_col(block_arr[0][0].size());
  if(row+min(block_row,block_col)>board_row){
    return 0;
  }
  int result=0;
  //최적화, tmp_max와 prev_value를 비교한다.
  //heuristic 1, 남은 공간보다 필요한 공간이 더 많다면, 탐색을 중단한다.
  if((tmp_max-prev_value)*heuristic1.first>heuristic1.second){
    return 0;
  }
  //heuristic2, cache[idx]이후의 원소들이 초기상태와 같을 때, prev_idx의 최댓값 
  if(heuristic2[row][col]>prev_value){
    return 0;
  }
  //탐색
  //block을 놓는 경우
  bool heu2_update(false);
  for(const auto& block:block_arr){
    if(BOARDCOVER2_board_can_input(board,block,row,col)){
      BOARDCOVER2_board_input(board,block,row,col);
      //heuristic1
      auto next_heuristic=make_pair(heuristic1.first,heuristic1.second-heuristic1.first);
      if(block[0][0]==0){
        next_heuristic.second--;
      }
      //recursive
      result=max(result,1+BOARDCOVER2_func(board,block_arr,tmp_max,next_heuristic,heuristic2,prev_value+1,now_idx+1));
      BOARDCOVER2_board_output(board,block,row,col);
    }
  }
  //block을 놓지않는 경우
    //heuristic1
  if(board[row][col]==0){
     heuristic1.second--;
  }
  result=max(result,BOARDCOVER2_func(board,block_arr,tmp_max,heuristic1,heuristic2,prev_value,now_idx+1));
  //반환 전에 최대값 갱신 
  tmp_max=max(tmp_max,prev_value+result);
  return result;
}
int BOARDCOVER2_Algo(vector<vector<char>> board, vector<vector<char>> block){
  //.과 #을 0과 1로 변환
  for(auto& ele: board){
    for(auto& ele2: ele){
      if(ele2=='#'){
        ele2=1;
      }else{
        ele2=0;
      }
    }
  }
  for(auto& ele: block){
    for(auto& ele2: ele){
      if(ele2=='#'){
        ele2=1;
      }else{
        ele2=0;
      }
    }
  }
  //8방향의 블록, 중복제거 
  auto block_arr=BOARDCOVER2_BlockArr(block);
  //함수
    //가지치기
    //heuristic 1, block의 크기와 board에 남은 공간 이용
  int block_size(0),board_remain(0);
  for(auto& row:block){
    for(auto& ele:row){
      if(ele==1){
        block_size++;
      }
    }
  }
  for(auto& row: board){
    for(auto& ele: row){
      if(ele==0){
        board_remain++;
      }
    }
  }
  auto heuristic1=make_pair(block_size,board_remain);
  //   //heuristic2, 현재까지의 경로가 최적인지 
  // vector<vector<int>> heuristic2(board.size(),vector<int>(board[0].size(),0));
  
  int tmp_max=0;
  return BOARDCOVER2_func(board,block_arr,tmp_max,heuristic1,heuristic2,0,0);
}
void BOARDCOVER2(){
  //BOARDCOVER2
  /*설명 및 입력
  설명
    H×W 크기의 게임판과 한 가지 모양의 블록이 여러 개 있습니다. 
    게임판에 가능한 많은 블록을 올려놓고 싶은데, 게임판은 검은 칸과 흰 칸으로 구성된 격자 모양을 하고 있으며 이 중에서 흰 칸에만 블록을 올려놓을 수 있습니다. 
    이때 블록들은 자유롭게 회전해서 놓을 수 있지만, 서로 겹치거나, 격자에 어긋나게 덮거나, 검은 칸을 덮거나, 게임판 밖으로 나가서는 안 됩니다.
    게임판과 블록의 모양이 주어질 때 최대 몇 개의 블록을 올려놓을 수 있는지 판단하는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 T (T≤100)가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 게임판의 크기 H, W (1≤H, W≤10), 그리고 블록의 모양을 나타내는 격자의 크기 R, C (1≤R, C≤10)가 주어집니다. 
    다음 H줄에는 각각 W 글자의 문자열로 게임판의 정보가 주어집니다. 문자열의 각 글자는 게임판의 한 칸을 나타내며, #은 검은 칸, 마침표는 흰 칸을 의미합니다. 
    다음 R줄에는 각 C 글자의 문자열로 블록의 모양이 주어집니다. 이 문자열에서 #은 블록의 일부, 마침표는 빈 칸을 나타냅니다.
    각 게임판에는 최대 50개의 흰 칸이 있으며, 각 블록은 3개 이상 10개 이하의 칸들로 구성됩니다. 
    변을 맞대고 있는 두 변이 서로 연결되어 있다고 할 때, 블록을 구성하는 모든 칸들은 서로 직접적 혹은 간접적으로 연결되어 있습니다.
  출력
    각 테스트 케이스마다 게임판에 놓을 수 있는 최대의 블록 수를 출력합니다.
  제한조건
    2초, 64MB
  */
  /*힌트
    조합 풀이법을 사용하자
      완전탐색을 구현한 후 하나씩 최적화를 진행한다.
    흰 칸의 개수는 최대 50개임을 이용하자(게임판은 최대 100칸)
    완전탐색
      좌상단에서 우하단으로 가면서, 각 위치에서 블록을 놓을 수 있는지 확인한다.
      !!!XXX 이때 블록은 좌우,상하로 뒤집을 수 있으며, 90도를 돌릴 수 있으므로 8가지의 모양을 가진다.
        블록은 회전만 가능하다.
    최적화
      heuristic1: 남은 부분에 대한 가지치기
        블록의 크기 * (현재 최대 블록 - 현재 놓은 블록) > 남은 공간 이면 탐색 중단
      board 자료형 변화: bitset을 이용하면 약간 빨라질수도
      heuristic2: 지나온 부분에 대한 가지치기
        cache[idx]=board에서 idx번째 부터는 초기 상태(아무런 영향 x)라고 할 때, 그 시점에 prev_idx의 최댓값 
          실질적으로 어렵다.
      heuristic3: 남은 부분에 대한 DP 적용
        board가 A*A, block이 B*C일 때, 실제로 따져봐야할 공간은 (A-min(B,C))^2 이다.
        DP를 통해 정해진 구간의 답을 미리 적어두자
        단, 가로의 길이는 고정되어 있음에 유의하자(세로의 길이는 조절)
          고려해야 할 공간은 20칸 이내가 되도록 한다.
        직전에 놓은(특히 바로 윗 행)것들이 영향을 끼치는데, 어떻게 제어할까?
    참고할 점
      최적화를 할 때는, 각각의 최적화를 적용후 조건에 맞는지 실행해보자. 조건에 맞지 않는다면 추가적인 최적화를 진행하면 된다.
  */
  /*전략
  전략1
    combination search
    시간:
      O(N^3) 
    크기:
      O(N)
    보완
      \
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<vector<char>> board,block;
    BOARDCOVER2_Input(board,block);
    auto result=BOARDCOVER2_Algo(board,block);
    cout<<result<<"::::::::::::\n";
  }
}

int main(void){
  clock_t start,end;
  start=clock();
  BOARDCOVER2();
  end=clock();;
  cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}