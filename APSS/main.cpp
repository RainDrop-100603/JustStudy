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

// combination, 답이 맞는지부터 확인, 시간조건을 맞추기 위해 최적화 하나씩 추가하면서 확인(한번에 추가 x) 
void ALLERGY_Input(vector<vector<char>>& board, vector<vector<char>>& block){
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
int ALLERGY_func(vector<vector<char>>& board, const vector<vector<vector<char>>>& block_arr, int& tmp_max,pair<int,int> heuristic1,int prev_value,int now_idx){
  int board_row(board.size()),board_col(board[0].size());
  int row(now_idx/board_col),col(now_idx%board_col);
  int block_row(block_arr[0].size()),block_col(block_arr[0][0].size());
  if(row+min(block_row,block_col)>board_row){
    return 0;
  }
  int result=0;
  //최적화, tmp_max와 prev_value를 비교한다.
  //heuristic 1, 남은 공간보다 필요한 공간이 더 많거나 같다면, 탐색을 중단한다. first=block에 필요한개수, second=board에 남은 빈 공간의 개수 
  if((tmp_max-prev_value)*heuristic1.first>=heuristic1.second){
    return 0;
  }
  //탐색
  //block을 놓는 경우
  for(const auto& block:block_arr){
    if(ALLERGY_board_can_input(board,block,row,col)){
      ALLERGY_board_input(board,block,row,col);
      //heuristic1
      auto next_heuristic=make_pair(heuristic1.first,heuristic1.second-heuristic1.first);
      if(block[0][0]==0){
        next_heuristic.second--;
      }
      //recursive
      result=max(result,1+ALLERGY_func(board,block_arr,tmp_max,next_heuristic,prev_value+1,now_idx+1));
      ALLERGY_board_output(board,block,row,col);
    }
  }
  //block을 놓지않는 경우
    //heuristic1
  if(board[row][col]==0){
     heuristic1.second--;
  }
  result=max(result,ALLERGY_func(board,block_arr,tmp_max,heuristic1,prev_value,now_idx+1));
  //반환 전에 최대값 갱신 
  tmp_max=max(tmp_max,prev_value+result);
  return result;
}
int ALLERGY_Algo(vector<vector<char>> board, vector<vector<char>> block){
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
  //초기블록과 회전한 블록들
  auto block_arr=ALLERGY_BlockArr(block);
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
  int tmp_max=0;
  return ALLERGY_func(board,block_arr,tmp_max,heuristic1,0,0);
}
void ALLERGY(){
  //ALLERGY
  /*설명 및 입력
  설명
    집들이에 n 명의 친구를 초대하려고 합니다. 
    할 줄 아는 m 가지의 음식 중 무엇을 대접해야 할까를 고민하는데, 친구들은 각각 알러지 때문에 못 먹는 음식들이 있어서 아무 음식이나 해서는 안 됩니다.
    친구들의 정보가 주어질 때 최소한 만들어야 하는 요리의 가지수를 계산하는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 T (T <= 50 ) 가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 친구의 수 n (1 <= n <= 50) 과 할 줄 아는 음식의 수 m (1 <= m <= 50) 이 주어집니다. 
    다음 줄에는 n 개의 문자열로 각 친구의 이름이 주어집니다. 친구의 이름은 10 자 이하의 알파벳 소문자로만 구성된 문자열입니다. 
    그 후 m 줄에 하나씩 각 음식에 대한 정보가 주어집니다. 
    각 음식에 대한 정보는 해당 음식을 먹을 수 있는 친구의 수와 각 친구의 이름으로 주어집니다.
    모든 친구는 하나 이상의 음식을 먹을 수 있다고 가정해도 좋습니다.
  출력
    각 테스트 케이스마다 한 줄에 만들어야 할 최소의 음식 수를 출력합니다.
  제한조건
    5초, 64MB
  */
  /*힌트
    조합 풀이법을 사용하자
      완전탐색을 구현한 후 하나씩 최적화를 진행한다.
    완전탐색
      음식을 순서대로 고르면서, 모든 친구가 포함되었는지 확인한다.
    최적화
      최대 50개 이므로 bitmask 사용 가능
      친구목록: 음식을 먹을 수 있는 친구의 목록을 뜻함
      많은 인원이 먹을 수 있는 음식대로 내림차순 정렬
      포함관계에 있는 음식(친구목록) 삭제
      음식을 선택할 때, 이미 선택된 음식들의 친구목록에 포함된다면 생략 
        음식을 선택한 후에, 음식 목록을 업데이트 하는 방법도 괜찮다고 보임
      가지치기
        
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
    ALLERGY_Input(board,block);
    auto result=ALLERGY_Algo(board,block);
    cout<<result<<"\n";
  }
}

int main(void){
  // clock_t start,end;
  // start=clock();
  ALLERGY();
  // end=clock();;
  // cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}