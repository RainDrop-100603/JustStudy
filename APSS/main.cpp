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
void KAKURO2_Input(vector<string>& friendsName, vector<vector<string>>& foodsInfo){
  int foodNum,friendNum;
  cin>>friendNum>>foodNum;
  friendsName.resize(friendNum);
  for(auto& ele: friendsName){
    cin>>ele;
  }
  foodsInfo.resize(foodNum);
  for(auto& food:foodsInfo){
    int count;
    cin>>count;
    for(int i=0;i<count;i++){
      string tmp;
      cin>>tmp;
      food.push_back(tmp);
    }
  }
}
vector<pair<int,long long>> KAKURO2_food_opti(const vector<string>& friendsName, const vector<vector<string>>& foodsInfo){
  //음식 정보를 bitmask로 수정, pair(친구의 수, 친구 정보 bitmask)
  int friendsNum=friendsName.size();
  vector<pair<int,long long>> foods_bitmask;
  for(auto& food:foodsInfo){
    long long bitmask(0);
    for(auto& name: food){
      for(int i=0;i<friendsNum;i++){
        if(name==friendsName[i]){
          bitmask+=(1LL<<i);
          break;
        }
      }
    }
    foods_bitmask.push_back({food.size(),bitmask});
  }
  //정렬, 친구에대해 동일한 음식 제거, 내림차순정렬
  sort(foods_bitmask.begin(),foods_bitmask.end());
  foods_bitmask.erase(unique(foods_bitmask.begin(),foods_bitmask.end()),foods_bitmask.end());
  reverse(foods_bitmask.begin(),foods_bitmask.end());
  //포함관계 음식 제거
  vector<pair<int,long long>> result;
  for(auto& ele: foods_bitmask){
    bool canInput(true);
    for(auto& exist:result){
      if((exist.second|ele.second)==exist.second){
        canInput=false;
        break;
      }
    }
    if(canInput){
      result.push_back(ele);
    }
  }
  //반환
  return result;
}
void KAKURO2_func(const vector<pair<int,long long>>& foods_bitmask,int friendsNum, long long friends_bitmask, int& tmp_min, int prev_count, int food_idx){
  //모든 친구를 충족시킨경우
  if((1LL<<friendsNum)-1==friends_bitmask){
    tmp_min=min(prev_count,tmp_min);
    return;
  }
  //마지막 음식이지만, 모든 친구를 충족하지 못한경우
  if(food_idx==foods_bitmask.size()){
    return;
  }
  //tmp_min보다 커진경우
  if(prev_count>=tmp_min){
    return;
  }
  //음식을 추가하는 경우
  auto nowFood=foods_bitmask[food_idx];
  if((friends_bitmask|nowFood.second)!=friends_bitmask){
    KAKURO2_func(foods_bitmask,friendsNum,friends_bitmask|nowFood.second,tmp_min,prev_count+1,food_idx+1);
  }
  //음식을 추가하지않는 경우
  KAKURO2_func(foods_bitmask,friendsNum,friends_bitmask,tmp_min,prev_count,food_idx+1);
}
int KAKURO2_Algo(const vector<string>& friendsName, const vector<vector<string>>& foodsInfo){
  //음식 정보 최적화
  vector<pair<int,long long>> foods_bitmask=KAKURO2_food_opti(friendsName,foodsInfo);
  //Algo
  int tmp_min(51);
  KAKURO2_func(foods_bitmask,friendsName.size(),0,tmp_min,0,0);
  return tmp_min;
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
      확인해야 하는 원소는 동일하므로, 호출의 깊이를 얕게 만들도록 하자 .
      접근방법을 각 원소가 아닌 각 줄(가로 or 세로)에 대해서로 바꾼다.
        보드의 크기가 N이라면, (N/2)*N*2가 각 줄의 최대 갯수이다.(N/2: 한 열(행)에 들어갈 수 있는 최대의 줄, N: 각 행(열)의 갯수, 2: 행+열)
          3차원 table:(row,col,direction)을 이용한다. -> 특정 원소를 포함하는 줄(line)에 접근하기 편하다(update가 편하다).
          priority queue를 이용한다. -> 남은 원소의 수가 적은 순서대로 정렬하기 편하다.
        남은 원소의 갯수가 적은 줄을 먼저 처리한다.

      가지치기
        현재값과 최대값의 비교
  */
  /*전략
  전략1
    combination search
    시간:
      O(2^N) & optimize 
    크기:
      O(N)
    보완
      \
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<string> friendsName;
    vector<vector<string>> foodsInfo;
    KAKURO2_Input(friendsName,foodsInfo);
    auto result=KAKURO2_Algo(friendsName,foodsInfo);
    cout<<result<<"\n";
  }
}

int main(void){
  // clock_t start,end;
  // start=clock();
  KAKURO2();
  // end=clock();;
  // cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}