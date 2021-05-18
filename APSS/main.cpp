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

// combination, set cover, 책에 더 최적화 하는 방법들이 있다.
void KAKURO2_Input(vector<vector<int>>& board, vector<vector<int>>& hint){
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
void KAKURO2_preTreat(vector<vector<int>>& board,vector<vector<int>>& hint){
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
pair<int,int> KAKURO2_hintChk(const vector<vector<int>>& board,const vector<vector<int>>& hint,int xAxis, int yAxis){
  //horizontal hint idx, vertical hint idx
  pair<int,int> result;
  //vertical hint 체크, direction=1
  int xAxis_1(xAxis),yAxis_1(yAxis),key_1(board[yAxis_1][xAxis_1]);
  while(key_1!=0){
    yAxis_1--;
    key_1=board[yAxis_1][xAxis_1];
  }
  for(int i=0;i<hint.size();i++){
    auto& ele=hint[i];
    if(ele[0]==yAxis_1&&ele[1]==xAxis_1&&ele[2]==1){
      result.second=i;  //하단 idx
      break;
    }
  }
  //horizontal hint 체크, direction=0
  int xAxis_2(xAxis),yAxis_2(yAxis),key_2(board[yAxis_2][xAxis_2]);
  while(key_2!=0){
    xAxis_2--;
    key_2=board[yAxis_2][xAxis_2];
  }
  for(int i=0;i<hint.size();i++){
    auto& ele=hint[i];
    if(ele[0]==yAxis_2&&ele[1]==xAxis_2&&ele[2]==0){
      result.first=i;  //우측 idx
    }
  }
  return result;
}
pair<int,int> KAKURO2_findHint(const vector<vector<int>>& board,const vector<vector<int>>& hint,const vector<vector<int>>& hint_remain_arr,const vector<vector<pair<int,int>>> board_hint){
  //pair(hHint,vHint)
  auto result=make_pair(-1,-1);
  //remain이 가장 작은 line 찾기
  int tmp_hint(-1);
  for(int i=1;i<10;i++){
    if(hint_remain_arr[i].size()>0){
      tmp_hint=hint_remain_arr[i].back();
      break;
    }
  }
    //빈공간이 없다면 반환
  if(tmp_hint==-1){
    return result;
  }
    //교차하는 line의 reamin도 가장 작은 것을 선택 
  if(hint[tmp_hint][2]==0){ //horizontal
    result.first=tmp_hint;
    int yAxis(hint[tmp_hint][0]),xAxis(hint[tmp_hint][1]+1),remain_min(100);
    for(xAxis;xAxis<board.size();xAxis++){
      if(board[yAxis][xAxis]==0){
        break;
      }else if(board[yAxis][xAxis]==-1){
        int vHint=board_hint[yAxis][xAxis].second;
        if(hint[vHint][5]<remain_min){
          remain_min=hint[vHint][5];
          result.second=vHint;
        }
      }
    }
  }else{  //vertical
    result.second=tmp_hint;
    int yAxis(hint[tmp_hint][0]+1),xAxis(hint[tmp_hint][1]),remain_min(100);
    for(yAxis;yAxis<board.size();yAxis++){
      if(board[yAxis][xAxis]==0){
        break;
      }else if(board[yAxis][xAxis]==-1){
        int hHint=board_hint[yAxis][xAxis].first;
        if(hint[hHint][5]<remain_min){
          remain_min=hint[hHint][5];
          result.first=hHint;
        }
      }
    }
  }
  //ret
  return result;
}
bool KAKURO2_validChk(const vector<int>& hHint,const vector<int>& vHint,int input){
  //hHint와 vHint에 i를 넣을 수 있는지 체크
  //hint: yAxis, xAxis, direction(0:h, 1:v), clue, bitmask_canInput, 남은 공간 (remain)
  //bitamsk chk
  int v_clue(vHint[3]),v_bitmask(vHint[4]),v_remain(vHint[5]);
  int h_clue(hHint[3]),h_bitmask(hHint[4]),h_remain(hHint[5]);
  if((1<<input)&v_bitmask&h_bitmask==0){
    return false;
  }
  //clue chk, clue와 input 비교
  if(input>v_clue||input>h_clue){
    return false;
  }
  //remain이 1인경우
  if((v_remain==1&&v_remain!=input)||(h_remain==1&&h_remain!=input)){
    return false;
  }
  //남은 bitmask조합으로 clue를 만들 수 있는지 chk, clue,remain,bitmask 모두 사용해야함
  return true;
}
void KAKURO2_set(vector<vector<int>>& board,vector<vector<int>>& hint,vector<vector<int>>& hint_remain_arr,pair<int,int> twoHint,int input,int mode){
  //board를 수정하는 작업, mode 1=input, mode 0=output
  //hint: yAxis, xAxis, direction(0:h, 1:v), clue, bitmask_canInput, 남은 공간 (remain)
  vector<int> &vHint(hint[twoHint.second]),&hHint(hint[twoHint.first]);
  int &v_clue(vHint[3]),&v_bitmask(vHint[4]),&v_remain(vHint[5]);
  int &h_clue(hHint[3]),&h_bitmask(hHint[4]),&h_remain(hHint[5]);
  if(mode==1){
    //hint 변경
    v_clue-=input;h_clue-=input;
    v_bitmask-=(1<<input);h_bitmask-=(1<<input);
    v_remain--;h_remain--;
    //hint_remain_arr 변경
      //horizontal, vertical 삭제
    auto &h_tmp=hint_remain_arr[h_remain+1];
    for(auto iter=h_tmp.begin();iter!=h_tmp.end();iter++){
      if(*iter=twoHint.first){
        h_tmp.erase(iter);
        break;
      }
    }
    auto& v_tmp=hint_remain_arr[v_remain+1];
    for(auto iter=v_tmp.begin();iter!=v_tmp.end();iter++){
      if(*iter=twoHint.first){
        v_tmp.erase(iter);
        break;
      }
    }
      //horizontal, vertical 입력
    hint_remain_arr[h_remain].push_back(twoHint.first);
    hint_remain_arr[v_remain].push_back(twoHint.second);
      //board 변경
    board[hHint[0]][vHint[1]]=input;
  }else{
    //hint 변경
    v_clue+=input;h_clue+=input;
    v_bitmask+=(1<<input);h_bitmask+=(1<<input);
    v_remain++;h_remain++;
    //hint_remain_arr 변경
      //horizontal, vertical 삭제
    auto &h_tmp=hint_remain_arr[h_remain-1];
    for(auto iter=h_tmp.begin();iter!=h_tmp.end();iter++){
      if(*iter=twoHint.first){
        h_tmp.erase(iter);
        break;
      }
    }
    auto& v_tmp=hint_remain_arr[v_remain-1];
    for(auto iter=v_tmp.begin();iter!=v_tmp.end();iter++){
      if(*iter=twoHint.first){
        v_tmp.erase(iter);
        break;
      }
    }
      //horizontal, vertical 입력
    hint_remain_arr[h_remain].push_back(twoHint.first);
    hint_remain_arr[v_remain].push_back(twoHint.second);
      //board 변경
    board[hHint[0]][vHint[1]]=-1;
  }
}
bool KAKURO2_func(vector<vector<int>>& board,vector<vector<int>>& hint,vector<vector<int>>& hint_remain_arr,const vector<vector<pair<int,int>>> board_hint){
  //hint: yAxis, xAxis, direction(0:h, 1:v), clue, bitmask_canInput, 남은 공간 (remain)
  //board: -1: 하얀색, 0: 검은색 or 힌트 
  //remain이 가장 작은 line을 찾고, 해당 line과 교차하는 line중 가장 remain이 작은 것을 선택, 순서는 (h,v), 남은 공간이 없다면 true 반환 
  pair<int,int> twoHint=KAKURO2_findHint(board,hint,hint_remain_arr,board_hint);
  if(twoHint.first==-1){
    return true;
  }
  auto &hHint(hint[twoHint.first]),&vHint(hint[twoHint.second]);
  //숫자 입력
  for(int i=9;i>0;i--){
    if(KAKURO2_validChk(hHint,vHint,i)){
      KAKURO2_set(board,hint,hint_remain_arr,twoHint,i,1);  //i를 넣는 과정
      if(KAKURO2_func(board,hint,hint_remain_arr,board_hint)){
        return true;
      }
      KAKURO2_set(board,hint,hint_remain_arr,twoHint,i,0);  //i를 빼는 과정
    }
  }
  // 적절한 값을 채워넣지 못했다면, 잘못된 것이므로 false 반환 
  return false;
}
vector<vector<int>> KAKURO2_Algo(vector<vector<int>> board,vector<vector<int>> hint){
  //전처리
    //hint: yAxis, xAxis, direction(0:h, 1:v), clue, bitmask_canInput, 남은 공간 (remain)
    //board: -1: 하얀색, 0: 검은색 or 힌트
  KAKURO2_preTreat(board,hint);
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
        board_hint[yAxis][xAxis]=KAKURO2_hintChk(board,hint,xAxis,yAxis);
      }
    }
  }
  // //debug
  // cout<<"::::::::::::::::::::::::::::::::::::::\n";
  // for(auto& row:board){
  //   for(auto& ele:row){
  //     cout<<ele<<" ";
  //   }cout<<"\n";
  // }
  // cout<<"::::::::::::::::::::::::::::::::::::::\n";
  // int iddd=0;
  // for(auto& ele:hint_remain_arr){
  //   cout<<iddd<<": ";
  //   for(auto& ele2:ele){
  //     cout<< ele2<<" ";
  //   }
  //   cout<<"\n";
  //   iddd++;
  // }
  // cout<<"::::::::::::::::::::::::::::::::::::::\n";
  // for(auto& row:board_hint){
  //   for(auto& ele:row){
  //     cout<<"("<<ele.first<<","<<ele.second<<")";
  //   }
  //   cout<<"\n";
  // }
  // cout<<"::::::::::::::::::::::::::::::::::::::\n";
  // for(auto& ele:hint){
  //   for(auto& ele2:ele){
  //     cout<< ele2<<" ";
  //   }cout<<"\n";
  // }
  // cout<<"::::::::::::::::::::::::::::::::::::::\n";
  //Algo
  KAKURO2_func(board,hint,hint_remain_arr,board_hint);
  //return
  return board;
}
void KAKURO2(){
  //KAKURO2
  /*설명 및 입력
  설명
    카쿠로는 흔히 십자말풀이 수학 버전이라고 불리는 논리 퍼즐이다. 
    카쿠로는 위와 같이 생긴 정사각형의 게임판을 가지고 하는 퍼즐로, 
      이 게임판의 각 칸은 흰 칸이거나, 검은 칸이거나, 힌트 칸이다. (힌트 칸은, 대각선으로 갈라져 있고 숫자가 씌여 있는 칸을 말한다) 
    모든 흰 칸에 적절히 숫자를 채워 넣어 규칙을 만족시키는 것이 이 게임의 목표이다.
    모든 흰 칸에는 1 부터 9 까지의 정수를 써넣어야 한다.
      이 때 한 줄을 이루는 연속된 흰 칸들에는 같은 수를 두 번 넣을 수 없다. 
    세로로 연속한 흰 칸들의 수를 모두 더하면, 그 칸들의 바로 위에 있는 힌트 칸의 왼쪽 아래에 씌인 숫자가 나와야 한다.
    가로로 연속한 흰 칸들의 수를 모두 더하면, 그 칸들의 바로 왼쪽에 있는 힌트 칸의 오른쪽 위에 씌인 숫자가 나와야 한다.
  입력
    The first line of input file has the number of test cases T.
    In the first line of each test case, the size of the game board N (<= 20) is given. 
    The next N lines will give a description of the board, from top to bottom. 
      These lines will have N numbers, where 0 denote black/hint cells, and 1 denote white cells. 
    In the next line, the number of hint Q is given. 
      The following Q lines give the hints on the board, each described with four integers: y, x, direction, and sum. 
      sum is the value of the clue (1 <= sum <= 45), and (y, x) is the 1-based coordinate of the hint cell. 
      direction is 0 if hint clue is a horizontal sum, 1 if the clue is a vertical sum.
    You can assume for all test cases, there will be a unique valid solution.
  출력
    For each test case, print out the solved Kakuro board in N lines each with N numbers. 
    Print 0 for black or hint cells, and print the filled number for white cells.
  제한조건
    20초, 64MB
  */
  /*힌트
    조합 풀이법을 사용하자
      완전탐색을 구현한 후 하나씩 최적화를 진행한다.
    완전탐색
      비어있는 칸부터 숫자를 하나씩 넣는다.
    최적화
      숫자를 채워넣을 때, 큰 숫자를 먼저 넣는것이 더 유리할듯
      확인해야 하는 원소는 동일하므로, 호출의 깊이를 얕게 만들도록 하자 .
      접근방법을 각 원소가 아닌 각 줄(가로 or 세로)에 대해서로 바꾼다. -> 
        보드의 크기가 N이라면, (N/2)*N*2가 각 줄의 최대 갯수이다.(N/2: 한 열(행)에 들어갈 수 있는 최대의 줄, N: 각 행(열)의 갯수, 2: 행+열)
          3차원 table:(row,col,direction)을 이용한다. -> 특정 원소를 포함하는 줄(line)에 접근하기 편하다(update가 편하다).
          priority queue를 이용한다. -> 남은 원소의 수가 적은 순서대로 정렬하기 편하다.
            특정 원소가 어떤 줄과 관련이 있는지 표현하는 N*N table을 통해, priority queue를 업데이트 한다.
        남은 원소의 갯수가 적은 줄을 먼저 처리한다.
      각 원소에 대해 접근하는 방법
        흰칸 -1, 검은칸 or 힌트 0
        좌상단 부터 시작하여 원소에 접근한다.
        흰칸을 찾으면, 흰칸에 해당하는 hint를 두개 찾고, hint조건에 맞도록 숫자를 선택하고, hint와 board를 업데이트한다.
  */
  /*전략
  전략1
    combination search
    시간:
      O(9^(N^2)) & optimize 
    크기:
      O(N^2)
    보완
      \
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<vector<int>> board,hint;
    KAKURO2_Input(board,hint);
    auto result=KAKURO2_Algo(board,hint);
    for(auto& row:result){
      for(auto& ele:row){
        cout<<ele<<" ";
      }cout<<"\n";
    }
  }
}

int main(void){
   clock_t start,end;
   start=clock();
  KAKURO2();
   end=clock();;
   cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}