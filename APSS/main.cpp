//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// @*@* 정답에서 하나씩 빼는 DP, boundary 조건 확실히
void TICTACTOE_Input(vector<vector<string>>& board){
  for(int i=0;i<board.size();i++){
    string tmp;
    cin>>tmp;
    for(int j=0;j<board[0].size();j++){
      board[i][j]=tmp[j];
    }
  }
}
int TICTACTOE_isInValid(const string& shortStr,const string& longStr){
  if(shortStr.size()>longStr.size()){
    return -1*TICTACTOE_isInValid(longStr,shortStr);
  }
  for(int i=0;i<=longStr.size()-shortStr.size();i++){
    bool invalid(true);
    for(int j=0;j<shortStr.size();j++){
      if(shortStr[j]!=longStr[i+j]){
        invalid=false;
        break;
      }
    }
    if(invalid){
      return 1;
    }
  }
  return 0;
}
vector<string> TICTACTOE_strOptimize(const vector<string>& strArr){
  vector<string> strArr_opti;
  vector<int> valid_arr(strArr.size(),1);
  for(int i=0;i<strArr.size();i++){
    //최적화, A가 B를 invalid하게 만들었다면, B가 invalid하게 만드는 모든것은 A가 invalid하게 만든다(포함관계 생각하자)
    if(valid_arr[i]==0){
      continue;
    }
    //Algo
    const string& ele(strArr[i]);
    for(int j=i+1;j<strArr.size();j++){
      //기저
      if(valid_arr[j]==0){
        continue;
      }
      //Algo
      const string& ele2(strArr[j]);
      int inValid=TICTACTOE_isInValid(ele,ele2);  //both valid:0, ele invalid: 1, ele2 invalid: -1
      if(inValid==-1){
        valid_arr[j]=0;
      }
      if(inValid==1){
        valid_arr[i]=0;
        break;  //invalid되면 더이상 비교할 필요가 없다.
      }
    }
  }
  for(int i=0;i<valid_arr.size();i++){
    if(valid_arr[i]){
      strArr_opti.push_back(strArr[i]);
    }
  }
  return strArr_opti;
}
void TICTACTOE_DP_prepare(vector<vector<int>>& DP_strSaved,vector<string>& strArr_opti){
  int strNum(strArr_opti.size());
  //DP(0,front) 
  for(int front=0;front<strNum;front++){
    DP_strSaved[0][front]=0;
  }
  //DP(front,back)
  for(int front=0;front<strNum;front++){
    for(int back=0;back<strNum;back++){
      if(front==back){
        continue;
      }
      //겹치는 정도 확인
      int len=min(strArr_opti[front].size(),strArr_opti[back].size());
      int savedLen=0;
      const string& frontStr=strArr_opti[front];
      const string& backStr=strArr_opti[back];
      for(int i=1;i<len;i++){
        bool isSaved(true);
        //하나하나비교 
        for(int j=0;j<i;j++){
          if(frontStr[frontStr.size()-i+j]!=backStr[j]){
            isSaved=false;
            break;
          }
        }
        //전부 겹치면 saved
        if(isSaved==true){
          savedLen=i;
        }
      }
      DP_strSaved[1<<front][back]=savedLen;
    }
  }
}
int TICTACTOE_DP(vector<vector<int>>& dp_bitmask,int now_bitmask,int add_str){
  int strNum=dp_bitmask[0].size();
  int& result=dp_bitmask[now_bitmask][add_str];
  if(result!=-1){
    return result;
  }
  result=0;
  //정답 chk
  if(now_bitmask==(1<<strNum)-1){
    for(int i=0;i<strNum;i++){
      result=max(result,TICTACTOE_DP(dp_bitmask,now_bitmask-(1<<i),i));
    }
    return result;
  }
  //general
  for(int front=0;front<strNum;front++){
    if((now_bitmask&1<<front)!=0){
      result=max(result,TICTACTOE_DP(dp_bitmask,now_bitmask-(1<<front),front)+dp_bitmask[1<<front][add_str]);
    }
  }
  return result;
}
int TICTACTOE_isFinished(vector<vector<string>>& board, string turn){

}
int TICTACTOE_bijection(vector<vector<string>>& board){
  int result(0);
  
}
int TICTACTOE_result(vector<vector<string>>& board, vector<int>& cache_result,string turn_last){
  //기저
  int& result=cache_result[TICTACTOE_bijection(board)];
  if(result!=-2){
    return result;
  }
  //기저 2, 직전에 상대방이 둔 수로 게임이 끝났는가?
  string turn_now;
  if(turn_last=="O"){
    turn_now="X";
  }else{
    turn_now="O";
  }
  if(TICTACTOE_isFinished(board,turn_last)){
    result=-1;
    return result;
  }
  //Algo
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      if(board[i][j]=="."){
        board[i][j]=turn_now;
        result=max(result,TICTACTOE_result(board,cache_result,turn_now));
        board[i][j]==".";
      }
      if(result==1){
        return result;
      }
    }
  }
  //return, -2 는 더 둘 자리가 없고, 승부도 나지 않았음을 의미한다.
  if(result==-2){
    result=0;
    return result;
  }else if(result==-1||result==0){
    return result;
  }
  cout<<"Error occurs in result";
  return 10;  //makes error
}
string TICTACTOE_Algo(vector<vector<string>>& board){
  //누구의 turn인지 구하기
  int used_O(0), used_X(0);
  string turn_now, turn_last;
  for(auto& ele:board){
    for(auto& ele2: ele){
      if(ele2=="O"){
        used_O++;
      }else if(ele2=="X"){
        used_X++;
      }
    }
  }
  if(used_X > used_O){
    turn_now="O";
    turn_last="X";
  }else{
    turn_now="X";
    turn_last="O"
  }
  //result
  vector<int> cache_result(static_cast<int>(pow(3,9)),-2);
  int result_int=TICTACTOE_result(board,cache_result,turn_last);
  if(result_int==1){
    return turn_last;
  }else if(result_int==-1){
    return turn_now;
  }else if(result_int==0){
    return string("TIE");
  }
  return string("error in TICTACTOE_Algo");
}
void TICTACTOE(){
  //TICTACTOE
  /*설명 및 입력
  설명
    틱택토 게임. 현재 게임판의 상태가 주어질 때, 게임이 진행되었을 때 승자(패자) 혹은 무승부 여부를 구하여라
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C(<= 50)가 주어집니다.
    각 테스트 케이스는 세 줄에 각 세 글자로 게임판의 각 위치에 쓰인 글자가 주어집니다.
    글자가 없는 칸은 마침표(.)로 표현합니다.
  출력
    각 테스트 케이스마다 한 줄을 출력합니다.
    두 사람이 모두 최선을 다할 경우 비긴다면 TIE를, 아닌 경우 이기는 사람의 글자를 출력합니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    점대칭, 선대칭(좌우상하대각) 되어도 항상 같은 결과가 나온다 -> 최적화 가능 요소
    3진법으로 치환하면 승자여부 쉽계 계산 가능하다.  
  */
  /*전략
  전략1
      int isFinished(board, turn_last): 직전에 둔 사람(turn_last)로 인해 게임이 끝나면 1, 아니면 0 반호나
      int bijection(board): "."=0, "O"=1, "X"=2로 치환하여 반환 
      int bitmask(board, turn_last): 
        기저: cache chk
        기저2: isFinished로 확인
        재귀: 남은 부분에 O또는 X 넣고 재귀
    시간:

  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<vector<string>> board(3,vector<string>(3));
    TICTACTOE_Input(board);
    string result=TICTACTOE_Algo(board);
    cout<<result<<'\n';
  }
}

int main(void){
  TICTACTOE();
  return 0;
}